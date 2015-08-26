// Copyright 2015 Google Inc. All Rights Reserved.
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
//
// Declares an event to represent a GetProcessHeap function call.
#ifndef SYZYGY_BARD_EVENTS_GET_PROCESS_HEAP_EVENT_H_
#define SYZYGY_BARD_EVENTS_GET_PROCESS_HEAP_EVENT_H_

#include <windows.h>

#include "base/memory/scoped_ptr.h"
#include "syzygy/bard/event.h"
#include "syzygy/core/serialization.h"

namespace bard {
namespace events {

// An event that wraps a call to GetProcessHeap, to be played against a
// HeapBackdrop.
class GetProcessHeapEvent : public EventInterface {
 public:
  explicit GetProcessHeapEvent(HANDLE trace_heap);

  // @name EventInterface implementation.
  // @{
  EventType type() const override { return kGetProcessHeapEvent; }
  bool Play(void* backdrop) override;
  // @}

  // @name Serialization methods.
  // @{
  static bool Save(const EventInterface* const event,
                   core::OutArchive* out_archive);
  static scoped_ptr<GetProcessHeapEvent> Load(core::InArchive* in_archive);
  // @}

  // @name Accessors.
  // @{
  HANDLE trace_heap() const { return trace_heap_; }
  // @}

 private:
  // Recorded return value.
  HANDLE trace_heap_;

  DISALLOW_COPY_AND_ASSIGN(GetProcessHeapEvent);
};

}  // namespace events
}  // namespace bard

#endif  // SYZYGY_BARD_EVENTS_GET_PROCESS_HEAP_EVENT_H_
