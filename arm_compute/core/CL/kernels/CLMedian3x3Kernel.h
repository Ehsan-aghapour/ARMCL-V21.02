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
#ifndef ARM_COMPUTE_CLMEDIAN3X3KERNEL_H
#define ARM_COMPUTE_CLMEDIAN3X3KERNEL_H

#include "arm_compute/core/CL/ICLSimple2DKernel.h"

namespace arm_compute
{
class ICLTensor;

/** Interface for the median 3x3 filter kernel.
 *
 */
class CLMedian3x3Kernel : public ICLSimple2DKernel
{
public:
    /** Initialise the kernel's input and output.
     *
     * @param[in]  input            An input tensor. Data types supported: U8
     * @param[out] output           The output tensor. Data types supported: U8.
     * @param[in]  border_undefined True if the border mode is undefined. False if it's replicate or constant.
     */
    void configure(const ICLTensor *input, ICLTensor *output, bool border_undefined);
    /** Initialise the kernel's input and output.
     *
     * @param[in]  compile_context  The compile context to be used.
     * @param[in]  input            An input tensor. Data types supported: U8
     * @param[out] output           The output tensor. Data types supported: U8.
     * @param[in]  border_undefined True if the border mode is undefined. False if it's replicate or constant.
     */
    void configure(const CLCompileContext &compile_context, const ICLTensor *input, ICLTensor *output, bool border_undefined);

    // Inherited methods overridden:
    BorderSize border_size() const override;
};
} // namespace arm_compute
#endif /*ARM_COMPUTE_CLMEDIAN3X3KERNEL_H */
