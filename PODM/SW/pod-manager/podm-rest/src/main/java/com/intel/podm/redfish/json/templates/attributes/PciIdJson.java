/*
 * Copyright (c) 2016-2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.intel.podm.redfish.json.templates.attributes;

import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;

@JsonPropertyOrder({"durableName", "durableNameFormat"})
@SuppressWarnings({"checkstyle:VisibilityModifier"})
public class PciIdJson {
    @JsonProperty("VendorId")
    public String vendorId;

    @JsonProperty("DeviceId")
    public String deviceId;

    @JsonProperty("SubsystemId")
    public String subsystemId;

    @JsonProperty("SubsystemVendorId")
    public String subystemVendorId;

    public PciIdJson(String vendorId, String deviceId, String subsystemId, String subystemVendorId) {
        this.vendorId = vendorId;
        this.deviceId = deviceId;
        this.subsystemId = subsystemId;
        this.subystemVendorId = subystemVendorId;
    }
}