/*
 * Copyright (c) 2016-2020 Arm Limited.
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
#include "arm_compute/runtime/NEON/functions/NEWarpPerspective.h"

#include "arm_compute/core/Error.h"
#include "arm_compute/core/Validate.h"
#include "src/core/NEON/kernels/NEFillBorderKernel.h"
#include "src/core/NEON/kernels/NEWarpKernel.h"

#include <utility>

namespace arm_compute
{
void NEWarpPerspective::configure(ITensor *input, ITensor *output, const std::array<float, 9> &matrix, InterpolationPolicy policy, BorderMode border_mode, uint8_t constant_border_value)
{
    ARM_COMPUTE_ERROR_ON_DATA_TYPE_CHANNEL_NOT_IN(input, 1, DataType::U8);
    ARM_COMPUTE_ERROR_ON_DATA_TYPE_CHANNEL_NOT_IN(output, 1, DataType::U8);

    switch(policy)
    {
        case InterpolationPolicy::NEAREST_NEIGHBOR:
        {
            auto k = std::make_unique<NEWarpPerspectiveKernel<InterpolationPolicy::NEAREST_NEIGHBOR>>();
            k->configure(input, output, matrix, border_mode, constant_border_value);
            _kernel = std::move(k);
            break;
        }
        case InterpolationPolicy::BILINEAR:
        {
            auto k = std::make_unique<NEWarpPerspectiveKernel<InterpolationPolicy::BILINEAR>>();
            k->configure(input, output, matrix, border_mode, constant_border_value);
            _kernel = std::move(k);
            break;
        }
        case InterpolationPolicy::AREA:
        default:
            ARM_COMPUTE_ERROR("Interpolation type not supported");
    }

    auto b = std::make_unique<NEFillBorderKernel>();
    b->configure(input, _kernel->border_size(), border_mode, constant_border_value);
    _border_handler = std::move(b);
}
} // namespace arm_compute
