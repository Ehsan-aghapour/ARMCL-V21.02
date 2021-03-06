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
#ifndef ARM_COMPUTE_NEHOGGRADIENT_H
#define ARM_COMPUTE_NEHOGGRADIENT_H

#include "arm_compute/core/Types.h"
#include "arm_compute/runtime/IFunction.h"
#include "arm_compute/runtime/IMemoryManager.h"
#include "arm_compute/runtime/MemoryGroup.h"
#include "arm_compute/runtime/NEON/functions/NEDerivative.h"
#include "arm_compute/runtime/Tensor.h"

#include <cstdint>
#include <memory>

namespace arm_compute
{
class ITensor;
class ICPPKernel;

/** Basic function to calculate the gradient for HOG. This function calls the following Neon kernels:
 *
 * -# @ref NEDerivative
 * -# NEMagnitudePhaseKernel
 *
 * @deprecated This function is deprecated and is intended to be removed in 21.05 release
 *
 */
class NEHOGGradient : public IFunction
{
public:
    /** Default constructor */
    NEHOGGradient(std::shared_ptr<IMemoryManager> memory_manager = nullptr);
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    NEHOGGradient(const NEHOGGradient &) = delete;
    /** Prevent instances of this class from being copied (As this class contains pointers) */
    NEHOGGradient &operator=(const NEHOGGradient &) = delete;
    /** Prevent instances of this class from being moved (As this class contains non movable objects) */
    NEHOGGradient(NEHOGGradient &&) = delete;
    /** Prevent instances of this class from being moved (As this class contains non movable objects) */
    NEHOGGradient &operator=(NEHOGGradient &&) = delete;
    /** Default destructor */
    ~NEHOGGradient();
    /** Initialise the function's source, destinations, phase type and border mode
     *
     * @param[in, out] input                 Input tensor. Data type supported: U8.
     *                                       (Written to only for @p border_mode != UNDEFINED)
     * @param[out]     output_magnitude      Output tensor (magnitude). Data type supported: U16.
     * @param[out]     output_phase          Output tensor.(phase). Format supported: U8
     * @param[in]      phase_type            Type of @ref PhaseType
     * @param[in]      border_mode           Border mode to use
     * @param[in]      constant_border_value (Optional) Constant value to use for borders if border_mode is set to CONSTANT.
     */
    void configure(ITensor *input, ITensor *output_magnitude, ITensor *output_phase, PhaseType phase_type, BorderMode border_mode, uint8_t constant_border_value = 0);

    // Inherited method overridden:
    void run() override;

private:
    MemoryGroup                 _memory_group;
    NEDerivative                _derivative;
    std::unique_ptr<ICPPKernel> _mag_phase;
    Tensor                      _gx;
    Tensor                      _gy;
};
}
#endif /*ARM_COMPUTE_NEHOGGRADIENT_H */
