/*
 * Copyright (c) 2017-2018 Intel Corporation
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

package com.intel.podm.business.redfish.services;

import com.intel.podm.business.BusinessApiException;
import com.intel.podm.business.dto.EthernetSwitchAclDto;
import com.intel.podm.business.redfish.ServiceTraverser;
import com.intel.podm.business.services.context.Context;
import com.intel.podm.business.services.redfish.RemovalService;
import com.intel.podm.common.synchronization.TaskCoordinator;

import javax.enterprise.context.RequestScoped;
import javax.inject.Inject;
import javax.inject.Named;
import java.util.concurrent.TimeoutException;

@RequestScoped
@Named("EthernetSwitchAclRemovalService")
public class EthernetSwitchAclRemovalServiceImpl implements RemovalService<EthernetSwitchAclDto> {
    @Inject
    private TaskCoordinator taskCoordinator;

    @Inject
    private ServiceTraverser traverser;

    @Inject
    private EthernetSwitchAclActionService actionsService;


    @Override
    public void perform(Context target) throws BusinessApiException, TimeoutException {
        taskCoordinator.run(traverser.traverseServiceUuid(target), () -> actionsService.deleteAcl(target));
    }
}
