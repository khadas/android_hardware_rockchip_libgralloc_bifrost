/*
 * Copyright (C) 2022 Arm Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <cstdint>

namespace arm::mapper::common
{

/* This size is the upper bound to store a complete SMPTE 2094-40 bitstream. */
constexpr uint32_t smpte2094_40_size = 1268;

/*
 * This size is intended as an upper bound to a store a complete SMPTE 2094-10 bitstream.
 * The value has been calculated based on reasonable expectations; however, it may need to be
 * increased for exceptional use-cases.
 */
constexpr uint32_t smpte2094_10_size = 4829;

}
