/*!
 * @brief Implementation of DeleteZone command.
 *
 * @header{License}
 * @copyright Copyright (c) 2017-2018 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @header{Files}
 * @file delete_zone.cpp
 */

#include "nvme_agent_commands.hpp"
#include "agent-framework/module/common_components.hpp"
#include "tools/tools.hpp"
#include "loader/config.hpp"
#include "tools/databases.hpp"

using namespace agent::nvme;
using namespace agent_framework::model;
using namespace agent_framework::module;
using namespace agent::nvme::tools;
using namespace agent::nvme::loader;

namespace {

bool is_initiator_in_zone(const Uuid& zone) {
    auto endpoints = get_m2m_manager<Zone, Endpoint>().get_children(zone);
    auto& manager = get_manager<Endpoint>();
    const auto& it = find_if(endpoints.begin(), endpoints.end(),
                             [&manager](const Uuid& uuid) {return is_initiator(manager.get_entry(uuid));});
    return it != endpoints.end();
}

void disconnect_endpoints_in_zone(const Uuid& zone) {
    if(is_initiator_in_zone(zone)) {
        disconnect_all_targets(zone);
    }
    else {
        log_debug("nvme-agent", "No initiator in zone, no need to disconnect");
    }
}

void delete_zone(DeleteZone::ContextPtr ctx, const DeleteZone::Request& req, DeleteZone::Response&) {
    const Uuid& zone{req.get_zone()};
    // check if zone exists
    get_manager<Zone>().get_entry(zone);

    if (NvmeConfig::get_instance()->get_is_target()) {
        if (is_initiator_in_zone(zone)) {
            // remove initiator filter from target endpoints
            clear_initiator_filter(ctx, zone);
        }
        // remove zone database
        ZoneDatabase zone_db{zone};
        zone_db.remove();
        // delete entry from fabric database
        FabricDatabase fabric_db{get_manager<Fabric>().get_keys().front()};
        fabric_db.del(zone);
    }
    else {
        // disconnect endpoints if needed
        disconnect_endpoints_in_zone(zone);
    }

    get_m2m_manager<Zone, Endpoint>().remove_parent(zone);
    get_manager<Zone>().remove_entry(zone);
    log_debug("nvme-agent", "Removed zone with UUID '" + zone + "'");
}
}

REGISTER_NVME_COMMAND(DeleteZone, ::delete_zone);
