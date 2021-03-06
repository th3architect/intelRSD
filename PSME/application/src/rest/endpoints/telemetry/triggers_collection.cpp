/*!
 * @brief Triggers collection endpoint
 *
 * @header{License}
 * @copyright Copyright (c) 2017-2018 Intel Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @header{Filesystem}
 * @file triggers_collection.cpp
 */

#include "psme/rest/endpoints/telemetry/triggers_collection.hpp"



using namespace psme::rest::constants;
using namespace psme::rest::endpoint;

namespace {
json::Value make_prototype() {
    json::Value r(json::Value::Type::OBJECT);

    r[Common::ODATA_CONTEXT] = "/redfish/v1/$metadata#TriggersCollection.TriggersCollection";
    r[Common::ODATA_ID] = json::Value::Type::NIL;
    r[Common::ODATA_TYPE] = "#MetricDefinitionCollection.MetricDefinitionCollection";
    r[Common::NAME] = "Metric Definition Collection";
    r[Common::DESCRIPTION] = "Metric Definition Collection";
    r[Collection::ODATA_COUNT] = 0;
    r[Collection::MEMBERS] = json::Value::Type::ARRAY;

    return r;
}
}

TriggersCollection::TriggersCollection(const std::string& path) : EndpointBase(path) {}


TriggersCollection::~TriggersCollection() {}


void TriggersCollection::get(const server::Request& request, server::Response& response) {
    auto json = ::make_prototype();

    json[Common::ODATA_ID] = PathBuilder(request).build();

    // TODO: fill count and members

    set_response(response, json);
}


void TriggersCollection::post(const server::Request&, server::Response&) {
}
