/*
 * Copyright (c) 2018-2020 Arm Limited.
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
//Ehsan
#include"arm_compute/graph/TypePrinter.h"
#ifndef My_print
#include "arm_compute/gl_vs.h"
#endif


#include "src/core/CL/kernels/CLGEMMReshapeRHSMatrixKernel.h"

#include "arm_compute/core/CL/CLHelpers.h"
#include "arm_compute/core/CL/CLKernelLibrary.h"
#include "arm_compute/core/CL/ICLTensor.h"
#include "arm_compute/core/CL/OpenCL.h"
#include "arm_compute/core/Helpers.h"
#include "arm_compute/core/TensorInfo.h"
#include "arm_compute/core/Utils.h"
#include "arm_compute/core/utils/misc/ShapeCalculator.h"
#include "src/core/AccessWindowStatic.h"
#include "src/core/CL/CLValidate.h"
#include "src/core/CL/gemm/CLGEMMHelpers.h"
#include "src/core/helpers/AutoConfiguration.h"
#include "src/core/helpers/WindowHelpers.h"
#include "support/StringSupport.h"

namespace arm_compute
{
using namespace arm_compute::misc::shape_calculator;

namespace
{
Status validate_arguments(const ITensorInfo *input, const ITensorInfo *output, const GEMMRHSMatrixInfo &rhs_info)
{
    ARM_COMPUTE_RETURN_ERROR_ON(rhs_info.n0 == 0);
    ARM_COMPUTE_RETURN_ERROR_ON(rhs_info.k0 == 0);
    ARM_COMPUTE_RETURN_ERROR_ON(rhs_info.h0 == 0);
    ARM_COMPUTE_RETURN_ERROR_ON_MSG(((rhs_info.n0 & (rhs_info.n0 - 1)) && rhs_info.n0 != 3), "Only 2,3,4,8,16 are supported for n0");
    ARM_COMPUTE_RETURN_ERROR_ON_MSG(((rhs_info.k0 & (rhs_info.k0 - 1)) && (rhs_info.k0 != 1) && (rhs_info.k0 != 3)), "Only 1,2,3,4,8,16 are supported for k0");
    ARM_COMPUTE_RETURN_ERROR_ON(rhs_info.n0 > 16);
    ARM_COMPUTE_RETURN_ERROR_ON(rhs_info.k0 > 16);
    ARM_COMPUTE_RETURN_ERROR_ON((rhs_info.k0 == 1) && (rhs_info.transpose));

    ARM_COMPUTE_RETURN_ERROR_ON_F16_UNSUPPORTED(input);
    ARM_COMPUTE_RETURN_ERROR_ON(input->data_type() == DataType::UNKNOWN);

    if(rhs_info.export_to_cl_image)
    {
        const TensorInfo tensor_reshaped_info(compute_rhs_reshaped_shape(*input, rhs_info), 1, input->data_type());
        ARM_COMPUTE_RETURN_ON_ERROR(cl_gemm::validate_image2d_support_on_rhs(tensor_reshaped_info, rhs_info));
    }

    if(output->total_size() != 0)
    {
        ARM_COMPUTE_RETURN_ERROR_ON_MISMATCHING_DIMENSIONS(output->tensor_shape(), compute_rhs_reshaped_shape(*input, rhs_info));
        ARM_COMPUTE_RETURN_ERROR_ON_MISMATCHING_DATA_TYPES(input, output);
        ARM_COMPUTE_RETURN_ERROR_ON_MISMATCHING_QUANTIZATION_INFO(input, output);
    }

    return Status{};
}

std::pair<Status, Window> validate_and_configure_window(ITensorInfo *input, ITensorInfo *output, const GEMMRHSMatrixInfo &rhs_info)
{
    const unsigned int num_elems_processed_per_iteration_x = rhs_info.n0;
    const unsigned int num_elems_processed_per_iteration_y = rhs_info.k0;
    bool               window_changed                      = false;

    // Output auto initialization if not yet initialized
    auto_init_if_empty(*output, input->clone()->set_tensor_shape(compute_rhs_reshaped_shape(*input, rhs_info)));

#if My_print > 0
    //Ehsan
    std::cout<<"test; input shape: "<<input->tensor_shape()<<std::endl;
#endif

    // Configure window
    Window win = calculate_max_window(*input, Steps(num_elems_processed_per_iteration_x, num_elems_processed_per_iteration_y));

#if My_print > 0
    //Ehsan
            std::cout<<"CLGEMMRESHAPERHSMatrixkernel, before collapse X:"<<win.x()
            	<<" Y:"<<win.y()
    			<<" Z:"<<win.z()
    			<<" 4:"<<win[3]
            	<<std::endl;
#endif

    AccessWindowRectangle input_access(input, 0, 0, num_elems_processed_per_iteration_x, num_elems_processed_per_iteration_y);
    AccessWindowStatic    output_access(output, 0, 0, output->dimension(0), output->dimension(1));

    window_changed = update_window_and_padding(win, input_access);
    output_access.set_valid_region(win, ValidRegion(Coordinates(0, 0), output->tensor_shape()));

    if(rhs_info.export_to_cl_image)
    {
        arm_compute::cl_gemm::update_padding_for_cl_image(output);
    }

    // Collapse along the Z direction
    // This collapse needs to be here in order to tune the Z dimension of LWS
    Window collapsed = win.collapse(win, Window::DimZ);

#if My_print > 0
    //Ehsan
    std::cout<<"CLGEMMRESHAPERHSMatrixkernel, after collapse X:"<<collapsed.x()
    	<<" Y:"<<collapsed.y()
		<<" Z:"<<collapsed.z()
		<<" 4:"<<collapsed[3]
    	<<std::endl;
#endif

    Status err = (window_changed) ? ARM_COMPUTE_CREATE_ERROR(ErrorCode::RUNTIME_ERROR, "Insufficient Padding!") : Status{};
    return std::make_pair(err, collapsed);
}
} // namespace

CLGEMMReshapeRHSMatrixKernel::CLGEMMReshapeRHSMatrixKernel()
    : _input(nullptr), _output(nullptr)
{
}

void CLGEMMReshapeRHSMatrixKernel::configure(const ICLTensor *input, ICLTensor *output, const GEMMRHSMatrixInfo &rhs_info)
{
    configure(CLKernelLibrary::get().get_compile_context(), input, output, rhs_info);
}

void CLGEMMReshapeRHSMatrixKernel::configure(const CLCompileContext &compile_context, const ICLTensor *input, ICLTensor *output, const GEMMRHSMatrixInfo &rhs_info)
{
    ARM_COMPUTE_ERROR_ON_NULLPTR(input, output);

    // Perform validate step
    ARM_COMPUTE_ERROR_THROW_ON(validate_arguments(input->info(), output->info(), rhs_info));

    _input  = input;
    _output = output;

    // Create build options
    CLBuildOptions build_opts;
    build_opts.add_option("-DN0=" + support::cpp11::to_string(rhs_info.n0));
    build_opts.add_option("-DK0=" + support::cpp11::to_string(rhs_info.k0));
    build_opts.add_option("-DH0=" + support::cpp11::to_string(rhs_info.h0));
    build_opts.add_option_if(rhs_info.transpose, "-DTRANSPOSE");
    build_opts.add_option_if(rhs_info.interleave, "-DINTERLEAVE");
    build_opts.add_option("-DSRC_HEIGHT=" + support::cpp11::to_string(input->info()->dimension(1)));
    build_opts.add_option("-DDATA_TYPE=" + get_cl_unsigned_type_from_element_size(input->info()->element_size()));

    std::string kernel_name("gemm_reshape_rhs_matrix_");
    kernel_name += rhs_info.transpose ? "t" : "nt";

    // Create kernel
    _kernel = create_kernel(compile_context, kernel_name, build_opts.options());

#if My_print > 0
    std::cout<<"CLGEMMReshapeRHSMatrixKernel::configure"
    		<<" input shape: "<<input->info()->tensor_shape()
			<<" output shape: "<<output->info()->tensor_shape()
			<<std::endl;
#endif
    // Configure kernel window
    auto win_config = validate_and_configure_window(input->info(), output->info(), rhs_info);
    ARM_COMPUTE_ERROR_THROW_ON(win_config.first);
    ICLKernel::configure_internal(win_config.second);
}

Status CLGEMMReshapeRHSMatrixKernel::validate(const ITensorInfo *input, const ITensorInfo *output, const GEMMRHSMatrixInfo &rhs_info)
{
    ARM_COMPUTE_RETURN_ON_ERROR(validate_arguments(input, output, rhs_info));
    ARM_COMPUTE_RETURN_ON_ERROR(validate_and_configure_window(input->clone().get(), output->clone().get(), rhs_info).first);

    return Status{};
}

void CLGEMMReshapeRHSMatrixKernel::run(const Window &window, cl::CommandQueue &queue)
{
    ARM_COMPUTE_ERROR_ON_UNCONFIGURED_KERNEL(this);
    ARM_COMPUTE_ERROR_ON_INVALID_SUBWINDOW(ICLKernel::window(), window);

    Window slice = window.first_slice_window_3D();

    do
    {
        unsigned int idx = 0;
        add_3D_tensor_argument(idx, _input, slice);
        add_3D_tensor_argument(idx, _output, slice);
        enqueue(queue, *this, slice, lws_hint());
    }
    while(window.slide_window_slice_3D(slice));
}
} // namespace arm_compute
