/*
 * Copyright (C) 2017-2020, 2022 ARM Limited. All rights reserved.
 *
 * Copyright (C) 2008 The Android Open Source Project
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

#include <assert.h>

#if GRALLOC_ALLOCATOR_AIDL_VERSION > 0
#include <aidl/android/hardware/graphics/common/BufferUsage.h>
#endif

#define GRALLOC_USAGE_PRIVATE_MASK (0xffff0000f0000000U)

/*
 * Below usage types overlap, this is intentional.
 * The reason is that there are very few usage flags we have at our disposal.
 *
 * The overlapping is handled by processing the definitions
 * in a specific order.
 *
 * MALI_GRALLOC_USAGE_NO_AFBC is processed first.
 *
 * MALI_GRALLOC_USAGE_YUV_CONF are only for YUV formats and clients
 * using MALI_GRALLOC_USAGE_NO_AFBC must never allocate YUV formats.
 * The latter is strictly enforced and allocations will fail.
 *
 * MALI_GRALLOC_USAGE_AFBC_PADDING is only valid if MALI_GRALLOC_USAGE_NO_AFBC
 * is not present.
 */

#define GRALLOC_USAGE_PRIVATE_0 1ULL << 28
#define GRALLOC_USAGE_PRIVATE_1 1ULL << 29
#define GRALLOC_USAGE_PRIVATE_2 1ULL << 30
#define GRALLOC_USAGE_PRIVATE_3 1ULL << 31

#define GRALLOC_USAGE_PRIVATE_4 1ULL << 63
#define GRALLOC_USAGE_PRIVATE_5 1ULL << 62
#define GRALLOC_USAGE_PRIVATE_6 1ULL << 61
#define GRALLOC_USAGE_PRIVATE_7 1ULL << 60
#define GRALLOC_USAGE_PRIVATE_8 1ULL << 59
#define GRALLOC_USAGE_PRIVATE_9 1ULL << 58
#define GRALLOC_USAGE_PRIVATE_10 1ULL << 57

#define GRALLOC_USAGE_PRIVATE_11 1ULL << 56
#define GRALLOC_USAGE_PRIVATE_12 1ULL << 55
#define GRALLOC_USAGE_PRIVATE_13 1ULL << 54
#define GRALLOC_USAGE_PRIVATE_14 1ULL << 53
#define GRALLOC_USAGE_PRIVATE_15 1ULL << 52
#define GRALLOC_USAGE_PRIVATE_16 1ULL << 51
#define GRALLOC_USAGE_PRIVATE_17 1ULL << 50
#define GRALLOC_USAGE_PRIVATE_18 1ULL << 49
#define GRALLOC_USAGE_PRIVATE_19 1ULL << 48

#define RK_GRALLOC_USAGE_ALLOC_HEIGHT_ALIGN_MASK (GRALLOC_USAGE_PRIVATE_4 | GRALLOC_USAGE_PRIVATE_5)
/* 表征 "当前调用 alloc() 的 client 要求 buffer 的 alloc_height 是 8 对齐. */
#define RK_GRALLOC_USAGE_ALLOC_HEIGHT_ALIGN_8 (GRALLOC_USAGE_PRIVATE_4)
/* 16 对齐. */
#define RK_GRALLOC_USAGE_ALLOC_HEIGHT_ALIGN_16 (GRALLOC_USAGE_PRIVATE_5)
/* 64 对齐. */
#define RK_GRALLOC_USAGE_ALLOC_HEIGHT_ALIGN_64 (GRALLOC_USAGE_PRIVATE_4 | GRALLOC_USAGE_PRIVATE_5)

typedef enum
{
	/* 表征 client 要求 buffer (的 plane_0) 的 byte_stride 是 16 对齐.
	 * 仅 配合 HAL_PIXEL_FORMAT_YCrCb_NV12 等特定 rk_video_formats 使用.
	 *
	 * 对 HAL_PIXEL_FORMAT_YCrCb_NV12, plane_0 的 byte_stride 就是 pixel_stride.
	 */
	RK_GRALLOC_USAGE_STRIDE_ALIGN_16 = GRALLOC_USAGE_PRIVATE_10,
	/* 表征 client 要求 buffer (的 plane_0) 的 byte_stride 是 128 对齐.
	 * 仅 配合 HAL_PIXEL_FORMAT_YCrCb_NV12 等特定 rk_video_formats 使用.
	 */
	RK_GRALLOC_USAGE_STRIDE_ALIGN_128 = GRALLOC_USAGE_PRIVATE_9,
	/* 表征 client 要求 buffer (的 plane_0) 的 byte_stride 是 256 的奇数倍.
	 * 仅 配合 HAL_PIXEL_FORMAT_YCrCb_NV12 等特定 rk_video_formats 使用.
	 */
	RK_GRALLOC_USAGE_STRIDE_ALIGN_256_ODD_TIMES = GRALLOC_USAGE_PRIVATE_8,
	/* 表征 client 要求 buffer (的 plane_0) 的 byte_stride 是 64 对齐.
	 * 仅 配合 HAL_PIXEL_FORMAT_YCrCb_NV12 等特定 rk_video_formats 使用.
	 */
	RK_GRALLOC_USAGE_STRIDE_ALIGN_64 = GRALLOC_USAGE_PRIVATE_7,

	/* 表征 "当前 调用 alloc() 的 client 通过 width 指定了其预期的 buffer stride",
	 * 即要求 gralloc 遵循 rk_implicit_alloc_semantic (即 满足 implicit_requirement_for_rk_gralloc_allocate).
	 */
	RK_GRALLOC_USAGE_SPECIFY_STRIDE = GRALLOC_USAGE_PRIVATE_2,

	/* 表征 "调用 alloc() 的 client 要求分配 底层 pages 是物理连续的 buffer".
	 * 目前的实现从 ion_cma_heap 分配.
	 */
	RK_GRALLOC_USAGE_PHY_CONTIG_BUFFER = GRALLOC_USAGE_PRIVATE_3,

	/* 表征 "调用 alloc() 的 client 要求分配的 buffer 的所有物理 page 的地址都在 4G 以内".
	*/
	RK_GRALLOC_USAGE_WITHIN_4G = GRALLOC_USAGE_PRIVATE_11,

	/* See comment for Gralloc 1.0, above. */
	MALI_GRALLOC_USAGE_FRONTBUFFER = GRALLOC_USAGE_PRIVATE_0,

	MALI_GRALLOC_USAGE_FORCE_BACKBUFFER = GRALLOC_USAGE_PRIVATE_13,

	MALI_GRALLOC_USAGE_NO_AFBC = GRALLOC_USAGE_PRIVATE_1,

	MALI_GRALLOC_USAGE_AFBC_PADDING = GRALLOC_USAGE_PRIVATE_14,

	/* YUV-only. */
	MALI_GRALLOC_USAGE_YUV_COLOR_SPACE_DEFAULT = 0,
	MALI_GRALLOC_USAGE_YUV_COLOR_SPACE_BT601 = GRALLOC_USAGE_PRIVATE_18,
	MALI_GRALLOC_USAGE_YUV_COLOR_SPACE_BT709 = GRALLOC_USAGE_PRIVATE_19,
	MALI_GRALLOC_USAGE_YUV_COLOR_SPACE_BT2020 = (GRALLOC_USAGE_PRIVATE_18 | GRALLOC_USAGE_PRIVATE_19),
	MALI_GRALLOC_USAGE_YUV_COLOR_SPACE_MASK = MALI_GRALLOC_USAGE_YUV_COLOR_SPACE_BT2020,

	MALI_GRALLOC_USAGE_RANGE_DEFAULT = 0,
	MALI_GRALLOC_USAGE_RANGE_NARROW = GRALLOC_USAGE_PRIVATE_16,
	MALI_GRALLOC_USAGE_RANGE_WIDE = GRALLOC_USAGE_PRIVATE_17,
	MALI_GRALLOC_USAGE_RANGE_MASK = (GRALLOC_USAGE_PRIVATE_16 | GRALLOC_USAGE_PRIVATE_17),
	/* AFRC coding unit sizes.
	 * The Y and RGB coding unit sizes are encoded in vendor usage low bits to make them accessible
	 * to the Vulkan swapchain implementation.
	 */
	MALI_GRALLOC_USAGE_AFRC_RGBA_LUMA_CODING_SIZE_DEFAULT = 0,
	MALI_GRALLOC_USAGE_AFRC_RGBA_LUMA_CODING_SIZE_SENTINEL = GRALLOC_USAGE_PRIVATE_2,
	MALI_GRALLOC_USAGE_AFRC_RGBA_LUMA_CODING_SIZE_16 = MALI_GRALLOC_USAGE_AFRC_RGBA_LUMA_CODING_SIZE_SENTINEL | GRALLOC_USAGE_PRIVATE_0,
	MALI_GRALLOC_USAGE_AFRC_RGBA_LUMA_CODING_SIZE_24 = MALI_GRALLOC_USAGE_AFRC_RGBA_LUMA_CODING_SIZE_SENTINEL | GRALLOC_USAGE_PRIVATE_1,
	MALI_GRALLOC_USAGE_AFRC_RGBA_LUMA_CODING_SIZE_32 = MALI_GRALLOC_USAGE_AFRC_RGBA_LUMA_CODING_SIZE_SENTINEL,
	MALI_GRALLOC_USAGE_AFRC_RGBA_LUMA_CODING_SIZE_MASK = GRALLOC_USAGE_PRIVATE_2 | GRALLOC_USAGE_PRIVATE_1 | GRALLOC_USAGE_PRIVATE_0,

	MALI_GRALLOC_USAGE_AFRC_CHROMA_CODING_SIZE_DEFAULT = 0,
	MALI_GRALLOC_USAGE_AFRC_CHROMA_CODING_SIZE_16 = GRALLOC_USAGE_PRIVATE_11,
	MALI_GRALLOC_USAGE_AFRC_CHROMA_CODING_SIZE_24 = GRALLOC_USAGE_PRIVATE_12,
	MALI_GRALLOC_USAGE_AFRC_CHROMA_CODING_SIZE_32 = GRALLOC_USAGE_PRIVATE_11 | GRALLOC_USAGE_PRIVATE_12,
	MALI_GRALLOC_USAGE_AFRC_CHROMA_CODING_SIZE_MASK = MALI_GRALLOC_USAGE_AFRC_CHROMA_CODING_SIZE_32,
} mali_gralloc_usage_type;

#define GRALLOC_USAGE_SW_WRITE_RARELY static_cast<uint64_t>(2 << 4)
#define GRALLOC_USAGE_SW_WRITE_OFTEN static_cast<uint64_t>(3 << 4)
#define GRALLOC_USAGE_SW_READ_RARELY static_cast<uint64_t>(2)
#define GRALLOC_USAGE_SW_READ_OFTEN static_cast<uint64_t>(3)
#define GRALLOC_USAGE_RENDERSCRIPT static_cast<uint64_t>(1 << 20)
#define GRALLOC_USAGE_HW_FB static_cast<uint64_t>(1 << 12)

/* Bit 10 must be zero as per Gralloc 2.x interface specification. Used, however, for backward compatibility */
#define GRALLOC_USAGE_HW_2D static_cast<uint64_t>(0x00000400)

#define GRALLOC_USAGE_SW_WRITE_MASK static_cast<uint64_t>(0xf << 4)
#define GRALLOC_USAGE_SW_READ_MASK static_cast<uint64_t>(0xf)
#define GRALLOC_USAGE_PROTECTED static_cast<uint64_t>(1 << 14)
#define GRALLOC_USAGE_CURSOR static_cast<uint64_t>(1 << 15)
#define GRALLOC_USAGE_HW_RENDER static_cast<uint64_t>(1 << 9)
#define GRALLOC_USAGE_HW_CAMERA_WRITE static_cast<uint64_t>(1 << 17)
#define GRALLOC_USAGE_HW_CAMERA_READ static_cast<uint64_t>(1 << 18)
#define GRALLOC_USAGE_HW_TEXTURE static_cast<uint64_t>(1 << 8)
#define GRALLOC_USAGE_HW_VIDEO_ENCODER static_cast<uint64_t>(1 << 16)
#define GRALLOC_USAGE_HW_COMPOSER static_cast<uint64_t>(1 << 11)
#define GRALLOC_USAGE_EXTERNAL_DISP static_cast<uint64_t>(0x00002000)

#define GRALLOC_USAGE_SENSOR_DIRECT_DATA static_cast<uint64_t>(1 << 23)
#define GRALLOC_USAGE_GPU_DATA_BUFFER static_cast<uint64_t>(1 << 24)

/* Originally (Gralloc 0.x), Android did not provide an explicit DECODER usage. This was rectified in Android N-MR1/7.1
 * when Gralloc 1.0 defined GRALLOC1_PRODUCER_USAGE_VIDEO_DECODER.
 */
#define GRALLOC_USAGE_DECODER static_cast<uint64_t>(1 << 22)

/* This usage should be used when using the AIDL allocator, otherwise use MALI_GRALLOC_USAGE_FRONTBUFFER */
#define GRALLOC_USAGE_FRONTBUFFER static_cast<uint64_t>(1ULL << 32)

#if !GRALLOC_HOST_BUILD

#include <android/hardware/graphics/common/1.2/types.h>
/* BufferUsage is not defined in 1.2/types.h as there are no changes from previous version in Android 12 and before*/
namespace hidl_common = android::hardware::graphics::common::V1_1;

static_assert(GRALLOC_USAGE_SW_WRITE_RARELY == static_cast<uint64_t>(hidl_common::BufferUsage::CPU_WRITE_RARELY));
static_assert(GRALLOC_USAGE_SW_READ_MASK == static_cast<uint64_t>(hidl_common::BufferUsage::CPU_READ_MASK));
static_assert(GRALLOC_USAGE_PROTECTED == static_cast<uint64_t>(hidl_common::BufferUsage::PROTECTED));
static_assert(GRALLOC_USAGE_CURSOR == static_cast<uint64_t>(hidl_common::BufferUsage::COMPOSER_CURSOR));
static_assert(GRALLOC_USAGE_HW_RENDER == static_cast<uint64_t>(hidl_common::BufferUsage::GPU_RENDER_TARGET));
static_assert(GRALLOC_USAGE_HW_CAMERA_WRITE == static_cast<uint64_t>(hidl_common::BufferUsage::CAMERA_OUTPUT));
static_assert(GRALLOC_USAGE_HW_CAMERA_READ == static_cast<uint64_t>(hidl_common::BufferUsage::CAMERA_INPUT));
static_assert(GRALLOC_USAGE_HW_TEXTURE == static_cast<uint64_t>(hidl_common::BufferUsage::GPU_TEXTURE));
static_assert(GRALLOC_USAGE_HW_VIDEO_ENCODER == static_cast<uint64_t>(hidl_common::BufferUsage::VIDEO_ENCODER));
static_assert(GRALLOC_USAGE_HW_COMPOSER == static_cast<uint64_t>(hidl_common::BufferUsage::COMPOSER_OVERLAY));
static_assert(GRALLOC_USAGE_SENSOR_DIRECT_DATA == static_cast<uint64_t>(hidl_common::BufferUsage::SENSOR_DIRECT_DATA));
static_assert(GRALLOC_USAGE_GPU_DATA_BUFFER == static_cast<uint64_t>(hidl_common::BufferUsage::GPU_DATA_BUFFER));
static_assert(GRALLOC_USAGE_DECODER == static_cast<uint64_t>(hidl_common::BufferUsage::VIDEO_DECODER));
#if GRALLOC_ALLOCATOR_AIDL_VERSION > 0
static_assert(GRALLOC_USAGE_FRONTBUFFER ==
              static_cast<uint64_t>(aidl::android::hardware::graphics::common::BufferUsage::FRONT_BUFFER));
#endif /* GRALLOC_ALLOCATOR_AIDL_VERSION > 0 */

#endif /* !GRALLOC_HOST_BUILD */

static const uint64_t VALID_USAGE =
    GRALLOC_USAGE_SW_READ_MASK | /* 0x0FU */
    GRALLOC_USAGE_SW_WRITE_MASK | /* 0xF0U */
    GRALLOC_USAGE_HW_TEXTURE | /* 1U << 8 */
    GRALLOC_USAGE_HW_RENDER | /* 1U << 9 */
    GRALLOC_USAGE_HW_2D | /* 1U << 10 */
    GRALLOC_USAGE_HW_COMPOSER | /* 1U << 11 */
    GRALLOC_USAGE_HW_FB | /* 1U << 12 */
    GRALLOC_USAGE_EXTERNAL_DISP | /* 1U << 13 */
    GRALLOC_USAGE_PROTECTED | /* 1U << 14 */
    GRALLOC_USAGE_CURSOR | /* 1U << 15 */
    GRALLOC_USAGE_HW_VIDEO_ENCODER | /* 1U << 16 */
    GRALLOC_USAGE_HW_CAMERA_WRITE | /* 1U << 17 */
    GRALLOC_USAGE_HW_CAMERA_READ | /* 1U << 18 */
    GRALLOC_USAGE_RENDERSCRIPT | /* 1U << 20 */
    GRALLOC_USAGE_DECODER | /* 1U << 22 */

    /* Producer and consumer usage are combined, but on Gralloc version 1 there is no way to differentiate these as they
     * are mapped to the same value (1U << 23). */
    GRALLOC_USAGE_SENSOR_DIRECT_DATA | /* 1U << 23 */
    GRALLOC_USAGE_GPU_DATA_BUFFER | /* 1U << 24 */

    GRALLOC_USAGE_FRONTBUFFER | /* 1L << 32 */

    GRALLOC_USAGE_PRIVATE_19 | /* 1U << 48 */
    GRALLOC_USAGE_PRIVATE_18 | /* 1U << 49 */
    GRALLOC_USAGE_PRIVATE_17 | /* 1U << 50 */
    GRALLOC_USAGE_PRIVATE_16 | /* 1U << 51 */
    GRALLOC_USAGE_PRIVATE_15 | /* 1U << 52 */
    GRALLOC_USAGE_PRIVATE_14 | /* 1U << 53 */
    GRALLOC_USAGE_PRIVATE_13 | /* 1U << 54 */
    GRALLOC_USAGE_PRIVATE_12 | /* 1U << 55 */
    GRALLOC_USAGE_PRIVATE_11 | /* 1U << 56 */
    GRALLOC_USAGE_PRIVATE_0 | /* 1U << 28 */
    GRALLOC_USAGE_PRIVATE_1 | /* 1U << 29 */
    GRALLOC_USAGE_PRIVATE_2 | /* 1U << 30 */
    GRALLOC_USAGE_PRIVATE_3; /* 1U << 31 */

/*
 * Determines whether frontbuffer usage is enabled.
 *
 * @param usage   gralloc usage bits.
 *
 * @return true, if frontbuffer usage is enabled
 *         false, otherwise
 */
static inline bool gralloc_usage_is_frontbuffer(const uint64_t usage)
{
	/* AFRC_RGBA_LUMA_CODING_SIZE_16 shares usage bits with FRONTBUFFER when using the HIDL allocator. */
	return (usage & GRALLOC_USAGE_FRONTBUFFER) || ((usage & MALI_GRALLOC_USAGE_FRONTBUFFER) &&
	       !(usage & MALI_GRALLOC_USAGE_AFRC_RGBA_LUMA_CODING_SIZE_SENTINEL));
}

/*
 * Determines whether no AFBC usage flag is enabled.
 *
 * @param usage   gralloc usage bits.
 *
 * @return true, if no AFBC usage flag is enabled
 *         false, otherwise
 */
static inline bool gralloc_usage_is_no_afbc(const uint64_t usage)
{
	/* AFRC_RGBA_LUMA_CODING_SIZE_24 shares usage bits with NO_AFBC.
	 * We assume that when AFRC is requested that AFBC is also enabled.
	 */
	return (usage & MALI_GRALLOC_USAGE_NO_AFBC) == MALI_GRALLOC_USAGE_NO_AFBC &&
	       !(usage & MALI_GRALLOC_USAGE_AFRC_RGBA_LUMA_CODING_SIZE_SENTINEL);
}
