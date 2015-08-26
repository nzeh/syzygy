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

#include "syzygy/bard/events/heap_destroy_event.h"

#include "syzygy/bard/backdrops/heap_backdrop.h"
#include "syzygy/trace/common/clock.h"

namespace bard {
namespace events {

HeapDestroyEvent::HeapDestroyEvent(HANDLE trace_heap, BOOL trace_succeeded)
    : trace_heap_(trace_heap), trace_succeeded_(trace_succeeded) {
}

bool HeapDestroyEvent::Save(const EventInterface* const event,
                            core::OutArchive* out_archive) {
  DCHECK_NE(static_cast<EventInterface*>(nullptr), event);
  DCHECK_NE(static_cast<core::OutArchive*>(nullptr), out_archive);

  const HeapDestroyEvent* derived_event =
      reinterpret_cast<const HeapDestroyEvent*>(event);

  return out_archive->Save(
             reinterpret_cast<uintptr_t>(derived_event->trace_heap_)) &&
         out_archive->Save(derived_event->trace_succeeded_);
}

scoped_ptr<HeapDestroyEvent> HeapDestroyEvent::Load(
    core::InArchive* in_archive) {
  DCHECK_NE(static_cast<core::InArchive*>(nullptr), in_archive);

  uintptr_t trace_heap;
  BOOL trace_succeeded;
  if (in_archive->Load(&trace_heap) &&
      in_archive->Load(&trace_succeeded)) {
    return scoped_ptr<HeapDestroyEvent>(
        new HeapDestroyEvent(reinterpret_cast<HANDLE>(trace_heap),
                             trace_succeeded));
  }
  return nullptr;
}

bool HeapDestroyEvent::Play(void* backdrop) {
  DCHECK_NE(static_cast<void*>(nullptr), backdrop);

  using bard::backdrops::HeapBackdrop;
  HeapBackdrop* heap_backdrop = reinterpret_cast<HeapBackdrop*>(backdrop);

  HANDLE live_heap = INVALID_HANDLE_VALUE;

  if (!heap_backdrop->heap_map().GetLiveFromTrace(trace_heap_, &live_heap))
    return false;

  uint64_t t0 = ::trace::common::GetTsc();
  BOOL live_succeeded = heap_backdrop->HeapDestroy(live_heap);
  uint64_t t1 = ::trace::common::GetTsc();

  if (live_succeeded != trace_succeeded_) {
    LOG(ERROR) << "HeapDestroy " << (live_succeeded ? "succeeded" : "failed")
               << " when it was supposed to "
               << (trace_succeeded_ ? "succeed" : "fail") << ".";
    return false;
  }

  if (live_succeeded &&
      !heap_backdrop->heap_map().RemoveMapping(trace_heap_, live_heap)) {
    return false;
  }

  heap_backdrop->UpdateStats(type(), t1 - t0);

  return true;
}

}  // namespace events
}  // namespace bard
