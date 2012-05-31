// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#ifndef PUB14_CORE_COMMAND_INITIALIZATION_H_
#define PUB14_CORE_COMMAND_INITIALIZATION_H_

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>

#include "anh/logger.h"

#include "anh/plugin/bindings.h"
#include "anh/plugin/plugin_manager.h"

#include "swganh/app/swganh_kernel.h"

#include "command_factory.h"
#include "command_filter.h"
#include "command_properties_manager.h"
#include "command_queue.h"
#include "command_queue_manager.h"
#include "command_service.h"
#include "command_validator.h"

#include "version.h"

namespace pub14_core {
namespace command {

inline void Initialize(swganh::app::SwganhKernel* kernel) 
{    
    anh::plugin::ObjectRegistration registration;
    registration.version.major = VERSION_MAJOR;
    registration.version.minor = VERSION_MINOR;
    
    { // Command::CommandFactory
        registration.CreateObject = [kernel] (anh::plugin::ObjectParams* params) -> void * {
            return new CommandFactory(kernel);
        };

        registration.DestroyObject = [] (void * object) {
            if (object) {
                delete static_cast<CommandFactory*>(object);
            }
        };

        kernel->GetPluginManager()->RegisterObject("Command::CommandFactory", &registration);
    }

    { // Command::CommandQueue
        registration.CreateObject = [kernel] (anh::plugin::ObjectParams* params) -> void * {
            return new CommandQueue(kernel);
        };

        registration.DestroyObject = [] (void * object) {
            if (object) {
                delete static_cast<CommandQueue*>(object);
            }
        };

        kernel->GetPluginManager()->RegisterObject("Command::CommandQueue", &registration);
    }

    { // Command::CommandQueueManager
        registration.CreateObject = [] (anh::plugin::ObjectParams* params) -> void * {
            return new CommandQueueManager();
        };

        registration.DestroyObject = [] (void * object) {
            if (object) {
                delete static_cast<CommandQueueManager*>(object);
            }
        };

        kernel->GetPluginManager()->RegisterObject("Command::CommandQueueManager", &registration);
    }

    { // Command::CommandPropertiesManager
        registration.CreateObject = [kernel] (anh::plugin::ObjectParams* params) -> void * {
            return new CommandPropertiesManager(kernel->GetTreArchive());
        };

        registration.DestroyObject = [] (void * object) {
            if (object) {
                delete static_cast<CommandPropertiesManager*>(object);
            }
        };

        kernel->GetPluginManager()->RegisterObject("Command::CommandPropertiesManager", &registration);
    }

    { // Command::CommandService
        registration.CreateObject = [kernel] (anh::plugin::ObjectParams* params) -> void * {
            auto command_service = new CommandService(kernel);
            
            // add filters
            command_service->AddCommandEnqueueFilter(std::bind(&CommandFilters::TargetCheckFilter, std::placeholders::_1));
            command_service->AddCommandEnqueueFilter(std::bind(&CommandFilters::PostureCheckFilter, std::placeholders::_1));
            command_service->AddCommandEnqueueFilter(std::bind(&CommandFilters::StateCheckFilter, std::placeholders::_1));
            command_service->AddCommandEnqueueFilter(std::bind(&CommandFilters::AbilityCheckFilter, std::placeholders::_1));
            command_service->AddCommandEnqueueFilter(std::bind(&CommandFilters::CombatTargetCheckFilter, std::placeholders::_1));
            command_service->AddCommandProcessFilter(std::bind(&CommandFilters::TargetCheckFilter, std::placeholders::_1));
            command_service->AddCommandProcessFilter(std::bind(&CommandFilters::PostureCheckFilter, std::placeholders::_1));
            command_service->AddCommandProcessFilter(std::bind(&CommandFilters::StateCheckFilter, std::placeholders::_1));
            command_service->AddCommandProcessFilter(std::bind(&CommandFilters::AbilityCheckFilter, std::placeholders::_1));
            command_service->AddCommandProcessFilter(std::bind(&CommandFilters::CombatTargetCheckFilter, std::placeholders::_1));

            return command_service;
        };

        registration.DestroyObject = [] (void * object) {
            if (object) {
                delete static_cast<CommandService*>(object);
            }
        };

        kernel->GetPluginManager()->RegisterObject("Command::CommandService", &registration);
    }

    { // Command::CommandValidator
        registration.CreateObject = [] (anh::plugin::ObjectParams* params) -> void * {
            return new CommandValidator();
        };

        registration.DestroyObject = [] (void * object) {
            if (object) {
                delete static_cast<CommandValidator*>(object);
            }
        };

        kernel->GetPluginManager()->RegisterObject("Command::CommandValidator", &registration);
    }
}

}}  // namespace pub14_core::command

#endif  // PUB14_CORE_COMMAND_INITIALIZATION_H_