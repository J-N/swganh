// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "swganh_core/object/tangible/tangible_factory.h"
#include <sstream>

#include <cppconn/exception.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/sqlstring.h>
#include "swganh/logger.h"

#include "swganh/database/database_manager.h"
#include "swganh_core/object/tangible/tangible.h"
#include "swganh_core/object/exception.h"
#include "swganh/simulation/simulation_service_interface.h"

using namespace std;
using namespace swganh::database;
using namespace swganh::object;
using namespace swganh::object;
using namespace swganh::simulation;

 TangibleFactory::TangibleFactory(swganh::database::DatabaseManagerInterface* db_manager,
            swganh::EventDispatcher* event_dispatcher)
    : ObjectFactory(db_manager, event_dispatcher)
{	
}

 void TangibleFactory::RegisterEventHandlers()
 {
	event_dispatcher_->Subscribe("Tangible::Customization", std::bind(&TangibleFactory::PersistHandler, this, std::placeholders::_1));
	event_dispatcher_->Subscribe("Tangible::ComponentCustomization", std::bind(&TangibleFactory::PersistHandler, this, std::placeholders::_1));
	event_dispatcher_->Subscribe("Tangible::OptionsMask", std::bind(&TangibleFactory::PersistHandler, this, std::placeholders::_1));
	event_dispatcher_->Subscribe("Tangible::IncapTimer", std::bind(&TangibleFactory::PersistHandler, this, std::placeholders::_1));
	event_dispatcher_->Subscribe("Tangible::ConditionDamage", std::bind(&TangibleFactory::PersistHandler, this, std::placeholders::_1));
	event_dispatcher_->Subscribe("Tangible::UpdateAttribute", std::bind(&TangibleFactory::PersistHandler, this, std::placeholders::_1));
	event_dispatcher_->Subscribe("Tangible::MaxCondition", std::bind(&TangibleFactory::PersistHandler, this, std::placeholders::_1));
	event_dispatcher_->Subscribe("Tangible::Static", std::bind(&TangibleFactory::PersistHandler, this, std::placeholders::_1));
	event_dispatcher_->Subscribe("Tangible::Defenders", std::bind(&TangibleFactory::PersistHandler, this, std::placeholders::_1));
 }

 
void TangibleFactory::PersistChangedObjects()
{
	std::set<shared_ptr<Object>> persisted;
	{
		boost::lock_guard<boost::mutex> lg(persisted_objects_mutex_);
		persisted = move(persisted_objects_);
	}
	for (auto& object : persisted)
	{
		PersistObject(object);
	}
}

uint32_t TangibleFactory::PersistObject(const shared_ptr<Object>& object)
{
	uint32_t counter = 1;
    try 
    {
        auto conn = db_manager_->getConnection("galaxy");
        auto statement = shared_ptr<sql::PreparedStatement>
            (conn->prepareStatement("CALL sp_PersistTangible(?,?,?,?,?,?,?);"));
        // cast to tangible
        auto tangible = static_pointer_cast<Tangible>(object);
		statement->setUInt64(counter++, tangible->GetObjectId());
        statement->setString(counter++, tangible->GetCustomization());
        statement->setInt(counter++, tangible->GetOptionsMask());
        statement->setInt(counter++, tangible->GetIncapTimer());
        statement->setInt(counter++, tangible->GetCondition());
        statement->setInt(counter++, tangible->GetMaxCondition());
        statement->setBoolean(counter++, tangible->IsStatic());
        statement->executeUpdate();
		
    }
    catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
	return counter;
}

void TangibleFactory::DeleteObjectFromStorage(const shared_ptr<Object>& object)
{
	ObjectFactory::DeleteObjectFromStorage(object);
}
void TangibleFactory::CreateTangible(const shared_ptr<Tangible>& tangible, const std::shared_ptr<sql::Statement>& statement)
{
    try {
        auto result = shared_ptr<sql::ResultSet>(statement->getResultSet());
        CreateBaseObjectFromStorage(tangible, result);
        if (statement->getMoreResults())
        {
            result.reset(statement->getResultSet());
            while (result->next())
            {
                tangible->SetCustomization(result->getString("customization"));
                tangible->SetOptionsMask(result->getUInt("options_bitmask"));
                tangible->SetIncapTimer(result->getUInt("incap_timer"));
                tangible->SetConditionDamage(result->getUInt("condition_damage"));
                tangible->SetMaxCondition(result->getUInt("max_condition"));
                tangible->SetStatic(result->getBoolean("is_static"));
            }
        }
    }
    catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
}
shared_ptr<Object> TangibleFactory::CreateObjectFromStorage(uint64_t object_id)
{
    auto tangible = make_shared<Tangible>();
    tangible->SetObjectId(object_id);
    try {
        auto conn = db_manager_->getConnection("galaxy");
        auto statement = shared_ptr<sql::Statement>(conn->createStatement());
        
        stringstream ss;
        ss << "CALL sp_GetTangible(" << object_id << ");";   

        statement->execute(ss.str());
        CreateTangible(tangible, statement);  
    }
    catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
    return tangible;
}

shared_ptr<Object> TangibleFactory::CreateObjectFromTemplate(const string& template_name, bool db_persisted, bool db_initialized)
{
	if(db_persisted || db_initialized)
	{
		//@TODO: Create me with help from db
		return make_shared<Tangible>();
	}
	else
	{
		return make_shared<Tangible>();
	}

}
