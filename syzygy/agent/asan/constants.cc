// Copyright 2014 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "syzygy/agent/asan/constants.h"

#include <windows.h>

namespace agent {
namespace asan {

namespace {

size_t page_size = 0;
size_t allocation_granularity = 0;

void InitializeConstants() {
  if (page_size == 0) {
    SYSTEM_INFO system_info = {};
    ::GetSystemInfo(&system_info);
    page_size = system_info.dwPageSize;
    allocation_granularity = system_info.dwAllocationGranularity;
  }
}

}  // namespace

size_t GetPageSize() {
  InitializeConstants();
  return page_size;
}

size_t GetAllocationGranularity() {
  InitializeConstants();
  return allocation_granularity;
}

}  // namespace asan
}  // namespace agent
