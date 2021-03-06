/*
 * Copyright (c) 2017-2020 Arm Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "arm_compute/core/GLES_COMPUTE/GCHelpers.h"
#include "arm_compute/core/Types.h"
#include "arm_compute/runtime/GLES_COMPUTE/GCTensor.h"
#include "arm_compute/runtime/GLES_COMPUTE/GCTensorAllocator.h"
#include "arm_compute/runtime/GLES_COMPUTE/functions/GCTranspose.h"
#include "tests/GLES_COMPUTE/GCAccessor.h"
#include "tests/PaddingCalculator.h"
#include "tests/datasets/ShapeDatasets.h"
#include "tests/framework/Asserts.h"
#include "tests/framework/Macros.h"
#include "tests/framework/datasets/Datasets.h"
#include "tests/validation/Validation.h"
#include "tests/validation/fixtures/TransposeFixture.h"

namespace arm_compute
{
namespace test
{
namespace validation
{
TEST_SUITE(GC)
TEST_SUITE(Transpose)

template <typename T>
using GCTransposeFixture = TransposeValidationFixture<GCTensor, GCAccessor, GCTranspose, T>;

TEST_SUITE(FP16)
FIXTURE_DATA_TEST_CASE(RunSmall, GCTransposeFixture<half>, framework::DatasetMode::NIGHTLY, combine(datasets::Small2DShapes(), framework::dataset::make("DataType", DataType::F16)))
{
    // Validate output
    validate(GCAccessor(_target), _reference);
}
FIXTURE_DATA_TEST_CASE(RunLarge, GCTransposeFixture<half>, framework::DatasetMode::NIGHTLY, combine(datasets::Large2DShapes(), framework::dataset::make("DataType", DataType::F16)))
{
    // Validate output
    validate(GCAccessor(_target), _reference);
}
TEST_SUITE_END()

TEST_SUITE(FP32)
FIXTURE_DATA_TEST_CASE(RunSmall, GCTransposeFixture<float>, framework::DatasetMode::NIGHTLY, combine(datasets::Small2DShapes(), framework::dataset::make("DataType", DataType::F32)))
{
    // Validate output
    validate(GCAccessor(_target), _reference);
}
FIXTURE_DATA_TEST_CASE(RunLarge, GCTransposeFixture<float>, framework::DatasetMode::NIGHTLY, combine(datasets::Large2DShapes(), framework::dataset::make("DataType", DataType::F32)))
{
    // Validate output
    validate(GCAccessor(_target), _reference);
}
TEST_SUITE_END()

TEST_SUITE_END()
TEST_SUITE_END()
} // namespace validation
} // namespace test
} // namespace arm_compute
