/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <glog/logging.h>

#include "interface/common/resdb_state_accessor.h"
#include "platform/config/resdb_config_utils.h"

using namespace resdb;

int main(int argc, char** argv) {
  if (argc < 2) {
    printf("<config path>\n");
    return 0;
  }
  std::string config_file = argv[1];

  ResDBConfig config = GenerateResDBConfig(config_file);

  ResDBStateAccessor client(config);
  auto states = client.GetReplicaStates();
  if (!states.ok()) {
    LOG(ERROR) << "get replica state fail";
    exit(1);
  }
  for (auto& state : *states) {
    LOG(ERROR) << state.DebugString();
  }
}
