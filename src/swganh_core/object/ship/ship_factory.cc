// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "ship_factory.h"
#include "ship.h"

using namespace std;
using namespace swganh::object;
using namespace swganh::object;

uint32_t ShipFactory::PersistObject(const shared_ptr<Object>& object, bool persist_inherited)
{
	uint32_t counter = 1;

	return counter;
}

void ShipFactory::DeleteObjectFromStorage(const shared_ptr<Object>& object)
{
	ObjectFactory::DeleteObjectFromStorage(object);
}

shared_ptr<Object> ShipFactory::CreateObjectFromStorage(uint64_t object_id)
{
    return make_shared<Ship>();
}

shared_ptr<Object> ShipFactory::CreateObject()
{
    return make_shared<Ship>();
}
