/*
 * Copyright (c) 2016-2021 Arm Limited.
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
#ifndef ARM_COMPUTE_NEGAUSSIAN3x3KERNEL_H
#define ARM_COMPUTE_NEGAUSSIAN3x3KERNEL_H

#include "src/core/NEON/INESimpleKernel.h"

namespace arm_compute
{
class ITensor;

/** Neon kernel to perform a Gaussian 3x3 filter */
class NEGaussian3x3Kernel : public INESimpleKernel
{
public:
    const char *name() const override
    {
        return "NEGaussian3x3Kernel";
    }
    /** Constructor */
    NEGaussian3x3Kernel() = default;
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    NEGaussian3x3Kernel(const NEGaussian3x3Kernel &) = delete;
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    NEGaussian3x3Kernel &operator=(const NEGaussian3x3Kernel &) = delete;
    /** Allow instances of this class to be moved */
    NEGaussian3x3Kernel(NEGaussian3x3Kernel &&) = default;
    /** Allow instances of this class to be moved */
    NEGaussian3x3Kernel &operator=(NEGaussian3x3Kernel &&) = default;
    /** Default destructor */
    ~NEGaussian3x3Kernel() = default;
    /** Set the source, destination and border mode of the kernel
     *
     * @param[in]  input            Source tensor. Data type supported: U8
     * @param[out] output           Destination tensor. Data type supported: same as @p input
     * @param[in]  border_undefined True if the border mode is undefined. False if it's replicate or constant.
     */
    void configure(const ITensor *input, ITensor *output, bool border_undefined);

    // Inherited methods overridden:
    void run(const Window &window, const ThreadInfo &info) override;
    BorderSize border_size() const override;
};
} // namespace arm_compute
#endif /*ARM_COMPUTE_NEGAUSSIAN3x3KERNEL_H */
