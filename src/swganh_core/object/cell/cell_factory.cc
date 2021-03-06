// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "cell_factory.h"

#include "cell.h"
#include <cppconn/exception.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/sqlstring.h>
#include "swganh/logger.h"

#include "swganh/database/database_manager.h"

using namespace std;
using namespace swganh::object;

CellFactory::CellFactory(swganh::app::SwganhKernel* kernel)
			: IntangibleFactory(kernel)
{
}

void CellFactory::RegisterEventHandlers()
{
	GetEventDispatcher()->Subscribe("Cell::Cell", std::bind(&CellFactory::PersistHandler, this, std::placeholders::_1));
}


void CellFactory::PersistChangedObjects()
{
	std::set<shared_ptr<Object>> persisted;
	{
		boost::lock_guard<boost::mutex> lg(persisted_objects_mutex_);
		persisted = move(persisted_objects_);
	}
	for (auto& object : persisted)
	{
		if(object->IsDatabasePersisted())
			PersistObject(object);
	}
}

uint32_t CellFactory::PersistObject(const shared_ptr<Object>& object, bool persist_inherited)
{
	// Persist Intangible and Base Object First
    uint32_t counter = 1;
	if (persist_inherited)
		IntangibleFactory::PersistObject(object, persist_inherited);
	try 
    {
		auto conn = GetDatabaseManager()->getConnection("galaxy");
		auto statement = shared_ptr<sql::PreparedStatement>
			(conn->prepareStatement("CALL sp_PersistCell(?);"));
		
		auto cell = static_pointer_cast<Cell>(object);
		statement->setInt(counter++, cell->GetCell());
		statement->executeUpdate();
	}
	catch(sql::SQLException &e)
	{
		LOG(error) << "SQLException at " << __FILE__ << " (" << __LINE__ << ": " << __FUNCTION__ << ")";
        LOG(error) << "MySQL Error: (" << e.getErrorCode() << ": " << e.getSQLState() << ") " << e.what();
	}
	return counter;
}

void CellFactory::DeleteObjectFromStorage(const shared_ptr<Object>& object)
{
	ObjectFactory::DeleteObjectFromStorage(object);
}

shared_ptr<Object> CellFactory::CreateObjectFromStorage(uint64_t object_id)
{
	//TODO: Use the db to fetch me
    return make_shared<Cell>();
}

shared_ptr<Object> CellFactory::CreateObject()
{
	return make_shared<Cell>();
}
