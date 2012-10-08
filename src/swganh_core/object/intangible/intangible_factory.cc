// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "intangible_factory.h"

#include <sstream>

#include <cppconn/exception.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/sqlstring.h>
#include "swganh/logger.h"

#include "swganh/database/database_manager.h"
#include "swganh_core/object/intangible/intangible.h"
#include "swganh_core/object/exception.h"
#include "swganh/simulation/simulation_service_interface.h"

using namespace std;
using namespace swganh::database;
using namespace swganh::object;
using namespace swganh::object;
using namespace swganh::simulation;

IntangibleFactory::IntangibleFactory(DatabaseManagerInterface* db_manager,
                             swganh::EventDispatcher* event_dispatcher)
    : ObjectFactory(db_manager, event_dispatcher)
{
}

uint32_t IntangibleFactory::PersistObject(const shared_ptr<Object>& object)
{
	// Persist Intangible
    uint32_t counter = 1;

	try 
    {
        auto conn = db_manager_->getConnection("galaxy");
        auto statement = shared_ptr<sql::PreparedStatement>
            (conn->prepareStatement("CALL sp_PersistIntangible(?,?,?);"));
        auto tangible = static_pointer_cast<Intangible>(object);
		statement->setString(counter++, tangible->GetStfNameFile());
		statement->setString(counter++, tangible->GetStfNameString());
		statement->setInt(counter++, tangible->GetGenericInt());
		statement->executeUpdate();
	}
	catch(sql::SQLException &e)
	{
		LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
	}
	return counter;
}

void IntangibleFactory::DeleteObjectFromStorage(const shared_ptr<Object>& object)
{
	ObjectFactory::DeleteObjectFromStorage(object);
}

shared_ptr<Object> IntangibleFactory::CreateObjectFromStorage(uint64_t object_id)
{
    auto intangible = make_shared<Intangible>();
    intangible->SetObjectId(object_id);
    try {
        auto conn = db_manager_->getConnection("galaxy");
        auto statement = shared_ptr<sql::PreparedStatement>(conn->prepareStatement("CALL sp_GetIntangible(?);"));
        
        auto result = shared_ptr<sql::ResultSet>(statement->executeQuery());

		CreateBaseObjectFromStorage(intangible, result);
        if (statement->getMoreResults())
        {
            result.reset(statement->getResultSet());
            while (result->next())
            {
				intangible->SetStfName(result->getString("stf_detail_file"), result->getString("stf_detail_string"));
                intangible->SetGenericInt(result->getInt("generic_int"));
            }
        }
    }
    catch(sql::SQLException &e)
    {
        LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
    }
    return intangible;
}

shared_ptr<Object> IntangibleFactory::CreateObjectFromTemplate(const string& template_name, bool db_persisted, bool db_initialized)
{
	if(db_persisted || db_initialized)
	{
		//@TODO: Create me with help from db
		return make_shared<Intangible>();
	}
	else
	{
		return make_shared<Intangible>();
	}
}
