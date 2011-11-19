
#ifndef SWGANH_OBJECT_RESOURCE_CONTAINER_RESOURCE_CONTAINER_FACTORY_H_
#define SWGANH_OBJECT_RESOURCE_CONTAINER_RESOURCE_CONTAINER_FACTORY_H_

#include "swganh/object/object_factory_interface.h"

namespace swganh {
namespace object {
namespace resource_container {

    class ResourceContainerFactory : public swganh::object::ObjectFactoryInterface
    {
    public:
        void LoadTemplates();

        bool HasTemplate(const std::string& template_name);

        void PersistObject(const std::shared_ptr<swganh::object::Object>& object);

        void DeleteObjectFromStorage(const std::shared_ptr<swganh::object::Object>& object);

        std::shared_ptr<swganh::object::Object> CreateObjectFromStorage(uint64_t object_id);

        std::shared_ptr<swganh::object::Object> CreateObjectFromTemplate(const std::string& template_name);
    };

}}}  // namespace swganh::object::resource_container

#endif  // SWGANH_OBJECT_RESOURCE_CONTAINER_RESOURCE_CONTAINER_FACTORY_H_
