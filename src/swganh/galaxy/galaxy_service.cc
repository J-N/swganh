/*
 This file is part of SWGANH. For more information, visit http://swganh.com
 
 Copyright (c) 2006 - 2011 The SWG:ANH Team

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "swganh/galaxy/galaxy_service.h"

#include "anh/app/kernel_interface.h"
#include "anh/plugin/plugin_manager.h"

#include "swganh/app/swganh_kernel.h"
#include "swganh/galaxy/providers/mysql_galaxy_provider.h"

using namespace anh;
using namespace app;
using namespace service;
using namespace swganh::app;
using namespace swganh::galaxy;
using namespace std;

GalaxyService::GalaxyService(anh::app::KernelInterface* kernel)
    : BaseService(kernel)
{
	galaxy_provider_ = kernel->GetPluginManager()->CreateObject<providers::GalaxyProviderInterface>("GalaxyService::GalaxyProvider");
    if (!galaxy_provider_) 
    {
        galaxy_provider_ = make_shared<providers::MysqlGalaxyProvider>(kernel->GetDatabaseManager());
    }
}

ServiceDescription GalaxyService::GetServiceDescription()
{
	ServiceDescription service_description(        
		"ANH Galaxy Service",
        "galaxy",
        "0.1",
        "127.0.0.1", 
        0,
        0, 
        0);
	return service_description;
}

uint32_t GalaxyService::GetPopulation()
{
	return galaxy_provider_->GetPopulation();
}