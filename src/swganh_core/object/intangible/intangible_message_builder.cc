// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "intangible_message_builder.h"

#include <cstdint>

#include "swganh_core/object/object.h"
#include "swganh_core/object/intangible/intangible.h"

using namespace std;
using namespace swganh::messages;
using namespace swganh::object;

void IntangibleMessageBuilder::RegisterEventHandlers()
{
    // TODO: Register Event Handlers for Intangible
}

boost::optional<BaselinesMessage> IntangibleMessageBuilder::BuildBaseline3(const std::shared_ptr<Intangible>& intangible)
{
	auto message = CreateBaselinesMessage(intangible, intangible->Object::VIEW_3, 5);
	message.data.append((*ObjectMessageBuilder::BuildBaseline3(intangible)).data);
	message.data.write(intangible->GetGenericInt()); 
	return BaselinesMessage(std::move(message));
}

boost::optional<BaselinesMessage> IntangibleMessageBuilder::BuildBaseline6(const shared_ptr<Intangible>& intangible)
{
	auto message = CreateBaselinesMessage(intangible, intangible->Object::VIEW_6, 1);
	message.data.append((*ObjectMessageBuilder::BuildBaseline6(intangible)).data);
    return BaselinesMessage(std::move(message));
}
