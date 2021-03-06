// Copyright 2011 Google Inc. All Rights Reserved.
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
// Internal implementation details for msf_stream.h. Not meant to be included
// directly.

#ifndef SYZYGY_MSF_MSF_STREAM_IMPL_H_
#define SYZYGY_MSF_MSF_STREAM_IMPL_H_

#include <vector>

#include "base/logging.h"
#include "syzygy/msf/msf_decl.h"

namespace msf {
namespace detail {

namespace {

const size_t kInvalidLength = 0xFFFFFFFF;

}  // namespace

template <MsfFileType T>
MsfStreamImpl<T>::MsfStreamImpl(size_t length)
    : length_(length == kInvalidLength ? 0 : length) {
}

template <MsfFileType T>
MsfStreamImpl<T>::~MsfStreamImpl() {
}

}  // namespace detail
}  // namespace msf

#endif  // SYZYGY_MSF_MSF_STREAM_IMPL_H_
