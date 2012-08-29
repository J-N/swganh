// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#ifndef SWGANH_OBJECT_BUILDING_BUILDING_MESSAGE_BUILDER_H_
#define SWGANH_OBJECT_BUILDING_BUILDING_MESSAGE_BUILDER_H_

#include "swganh/object/tangible/tangible_message_builder.h"

namespace swganh {
namespace object {
namespace building {

    class Building;
    class BuildingMessageBuilder : public swganh::object::tangible::TangibleMessageBuilder
    {
    public:
        BuildingMessageBuilder(anh::EventDispatcher* dispatcher) :
            TangibleMessageBuilder(dispatcher)
        {
            RegisterEventHandlers();
        }
        virtual void RegisterEventHandlers();
        virtual void SendBaselines(const std::shared_ptr<Building>& tangible, const std::shared_ptr<anh::observer::ObserverInterface>& controller);
        
        // baselines
        static swganh::messages::BaselinesMessage BuildBaseline3(const std::shared_ptr<Building>& building);
        static swganh::messages::BaselinesMessage BuildBaseline6(const std::shared_ptr<Building>& building);
    private:
        typedef anh::ValueEvent<std::shared_ptr<Building>> BuildingEvent;
    };

}}}  // swganh::object::tangible

#endif  // SWGANH_OBJECT_TANGIBLE_TANGIBLE_MESSAGE_BUILDER_H_