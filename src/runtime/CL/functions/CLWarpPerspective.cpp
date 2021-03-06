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
#include "arm_compute/runtime/CL/functions/CLWarpPerspective.h"

#include "arm_compute/core/PixelValue.h"
#include "src/core/CL/kernels/CLFillBorderKernel.h"
#include "src/core/CL/kernels/CLWarpPerspectiveKernel.h"

#include <utility>

using namespace arm_compute;

void CLWarpPerspective::configure(ICLTensor *input, ICLTensor *output, const std::array<float, 9> &matrix, InterpolationPolicy policy, BorderMode border_mode, uint8_t constant_border_value)
{
    configure(CLKernelLibrary::get().get_compile_context(), input, output, matrix, policy, border_mode, constant_border_value);
}

void CLWarpPerspective::configure(const CLCompileContext &compile_context, ICLTensor *input, ICLTensor *output, const std::array<float, 9> &matrix, InterpolationPolicy policy, BorderMode border_mode,
                                  uint8_t constant_border_value)
{
    auto k = std::make_unique<CLWarpPerspectiveKernel>();
    k->configure(compile_context, input, output, matrix, policy);
    _kernel = std::move(k);
    _border_handler->configure(compile_context, input, _kernel->border_size(), border_mode, PixelValue(constant_border_value));
}
