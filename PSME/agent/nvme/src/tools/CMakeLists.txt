# <license_header>
#
# Copyright (c) 2017-2018 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# </license_header>

add_subdirectory(drive_discovery)

set(SOURCES
    udev.cpp
    endpoint_reader.cpp
    endpoint_creator.cpp
    nvme_transport.cpp
    periodic_task.cpp
    tools.cpp
    databases.cpp
    default_transaction_handler.cpp
    transaction_handler_factory.cpp
    default_database_factory.cpp
)

add_library(nvme-tools-objs OBJECT ${SOURCES})
add_library(nvme-tools-db-objs OBJECT nvme_database.cpp)
add_library(nvme-tools-dir-objs OBJECT unix_dir.cpp)
add_library(nvme-tools-context-objs OBJECT nvme_context.cpp)
