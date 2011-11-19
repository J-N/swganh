
#include "swganh/object/building/building_factory.h"

#include "swganh/object/building/building.h"

using namespace std;
using namespace swganh::object;
using namespace swganh::object::building;

void BuildingFactory::LoadTemplates()
{}

bool BuildingFactory::HasTemplate(const string& template_name)
{
    return false;
}

void BuildingFactory::PersistObject(const shared_ptr<Object>& object)
{}

void BuildingFactory::DeleteObjectFromStorage(const shared_ptr<Object>& object)
{}

shared_ptr<Object> BuildingFactory::CreateObjectFromStorage(uint64_t object_id)
{
    return make_shared<Building>();
}

shared_ptr<Object> BuildingFactory::CreateObjectFromTemplate(const string& template_name)
{
    return make_shared<Building>();
}
