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
#ifndef ARM_COMPUTE_CLKERNELS_H
#define ARM_COMPUTE_CLKERNELS_H

/* Header regrouping all the CL kernels */
#include "src/core/CL/kernels/CLAbsoluteDifferenceKernel.h"
#include "src/core/CL/kernels/CLAccumulateKernel.h"
#include "src/core/CL/kernels/CLArgMinMaxLayerKernel.h"
#include "src/core/CL/kernels/CLBatchNormalizationLayerKernel.h"
#include "src/core/CL/kernels/CLBatchToSpaceLayerKernel.h"
#include "src/core/CL/kernels/CLBitwiseKernel.h"
#include "src/core/CL/kernels/CLBoundingBoxTransformKernel.h"
#include "src/core/CL/kernels/CLBox3x3Kernel.h"
#include "src/core/CL/kernels/CLCannyEdgeKernel.h"
#include "src/core/CL/kernels/CLChannelCombineKernel.h"
#include "src/core/CL/kernels/CLChannelExtractKernel.h"
#include "src/core/CL/kernels/CLChannelShuffleLayerKernel.h"
#include "src/core/CL/kernels/CLCol2ImKernel.h"
#include "src/core/CL/kernels/CLColorConvertKernel.h"
#include "src/core/CL/kernels/CLComparisonKernel.h"
#include "src/core/CL/kernels/CLConvertFullyConnectedWeightsKernel.h"
#include "src/core/CL/kernels/CLConvolutionKernel.h"
#include "src/core/CL/kernels/CLDeconvolutionLayerUpsampleKernel.h"
#include "src/core/CL/kernels/CLDeconvolutionReshapeOutputKernel.h"
#include "src/core/CL/kernels/CLDepthConvertLayerKernel.h"
#include "src/core/CL/kernels/CLDepthToSpaceLayerKernel.h"
#include "src/core/CL/kernels/CLDepthwiseConvolutionLayer3x3NCHWKernel.h"
#include "src/core/CL/kernels/CLDepthwiseConvolutionLayer3x3NHWCKernel.h"
#include "src/core/CL/kernels/CLDepthwiseConvolutionLayerNativeKernel.h"
#include "src/core/CL/kernels/CLDepthwiseConvolutionLayerReshapeWeightsKernel.h"
#include "src/core/CL/kernels/CLDequantizationLayerKernel.h"
#include "src/core/CL/kernels/CLDerivativeKernel.h"
#include "src/core/CL/kernels/CLDilateKernel.h"
#include "src/core/CL/kernels/CLDirectConvolutionLayerKernel.h"
#include "src/core/CL/kernels/CLErodeKernel.h"
#include "src/core/CL/kernels/CLFFTDigitReverseKernel.h"
#include "src/core/CL/kernels/CLFFTRadixStageKernel.h"
#include "src/core/CL/kernels/CLFFTScaleKernel.h"
#include "src/core/CL/kernels/CLFastCornersKernel.h"
#include "src/core/CL/kernels/CLFillBorderKernel.h"
#include "src/core/CL/kernels/CLFuseBatchNormalizationKernel.h"
#include "src/core/CL/kernels/CLGEMMLowpMatrixMultiplyNativeKernel.h"
#include "src/core/CL/kernels/CLGEMMLowpMatrixMultiplyReshapedKernel.h"
#include "src/core/CL/kernels/CLGEMMLowpMatrixMultiplyReshapedOnlyRHSKernel.h"
#include "src/core/CL/kernels/CLGEMMLowpOffsetContributionKernel.h"
#include "src/core/CL/kernels/CLGEMMLowpOffsetContributionOutputStageKernel.h"
#include "src/core/CL/kernels/CLGEMMLowpQuantizeDownInt32ScaleByFixedPointKernel.h"
#include "src/core/CL/kernels/CLGEMMLowpQuantizeDownInt32ScaleByFloatKernel.h"
#include "src/core/CL/kernels/CLGEMMLowpQuantizeDownInt32ScaleKernel.h"
#include "src/core/CL/kernels/CLGEMMLowpReductionKernel.h"
#include "src/core/CL/kernels/CLGEMMMatrixMultiplyKernel.h"
#include "src/core/CL/kernels/CLGEMMMatrixMultiplyNativeKernel.h"
#include "src/core/CL/kernels/CLGEMMMatrixMultiplyReshapedKernel.h"
#include "src/core/CL/kernels/CLGEMMMatrixMultiplyReshapedOnlyRHSKernel.h"
#include "src/core/CL/kernels/CLGEMMReshapeLHSMatrixKernel.h"
#include "src/core/CL/kernels/CLGEMMReshapeRHSMatrixKernel.h"
#include "src/core/CL/kernels/CLGatherKernel.h"
#include "src/core/CL/kernels/CLGaussian3x3Kernel.h"
#include "src/core/CL/kernels/CLGaussian5x5Kernel.h"
#include "src/core/CL/kernels/CLGaussianPyramidKernel.h"
#include "src/core/CL/kernels/CLGenerateProposalsLayerKernel.h"
#include "src/core/CL/kernels/CLHOGDescriptorKernel.h"
#include "src/core/CL/kernels/CLHOGDetectorKernel.h"
#include "src/core/CL/kernels/CLHarrisCornersKernel.h"
#include "src/core/CL/kernels/CLHistogramKernel.h"
#include "src/core/CL/kernels/CLIm2ColKernel.h"
#include "src/core/CL/kernels/CLInstanceNormalizationLayerKernel.h"
#include "src/core/CL/kernels/CLIntegralImageKernel.h"
#include "src/core/CL/kernels/CLL2NormalizeLayerKernel.h"
#include "src/core/CL/kernels/CLLKTrackerKernel.h"
#include "src/core/CL/kernels/CLMagnitudePhaseKernel.h"
#include "src/core/CL/kernels/CLMaxUnpoolingLayerKernel.h"
#include "src/core/CL/kernels/CLMeanStdDevKernel.h"
#include "src/core/CL/kernels/CLMeanStdDevNormalizationKernel.h"
#include "src/core/CL/kernels/CLMedian3x3Kernel.h"
#include "src/core/CL/kernels/CLMinMaxLayerKernel.h"
#include "src/core/CL/kernels/CLMinMaxLocationKernel.h"
#include "src/core/CL/kernels/CLNonLinearFilterKernel.h"
#include "src/core/CL/kernels/CLNonMaximaSuppression3x3Kernel.h"
#include "src/core/CL/kernels/CLNormalizationLayerKernel.h"
#include "src/core/CL/kernels/CLNormalizePlanarYUVLayerKernel.h"
#include "src/core/CL/kernels/CLPadLayerKernel.h"
#include "src/core/CL/kernels/CLPixelWiseMultiplicationKernel.h"
#include "src/core/CL/kernels/CLPriorBoxLayerKernel.h"
#include "src/core/CL/kernels/CLQLSTMLayerNormalizationKernel.h"
#include "src/core/CL/kernels/CLQuantizationLayerKernel.h"
#include "src/core/CL/kernels/CLROIAlignLayerKernel.h"
#include "src/core/CL/kernels/CLROIPoolingLayerKernel.h"
#include "src/core/CL/kernels/CLRangeKernel.h"
#include "src/core/CL/kernels/CLReductionOperationKernel.h"
#include "src/core/CL/kernels/CLRemapKernel.h"
#include "src/core/CL/kernels/CLReorgLayerKernel.h"
#include "src/core/CL/kernels/CLReverseKernel.h"
#include "src/core/CL/kernels/CLScaleKernel.h"
#include "src/core/CL/kernels/CLScharr3x3Kernel.h"
#include "src/core/CL/kernels/CLSelectKernel.h"
#include "src/core/CL/kernels/CLSobel3x3Kernel.h"
#include "src/core/CL/kernels/CLSobel5x5Kernel.h"
#include "src/core/CL/kernels/CLSobel7x7Kernel.h"
#include "src/core/CL/kernels/CLSoftmaxLayerKernel.h"
#include "src/core/CL/kernels/CLSpaceToBatchLayerKernel.h"
#include "src/core/CL/kernels/CLSpaceToDepthLayerKernel.h"
#include "src/core/CL/kernels/CLStackLayerKernel.h"
#include "src/core/CL/kernels/CLStridedSliceKernel.h"
#include "src/core/CL/kernels/CLTableLookupKernel.h"
#include "src/core/CL/kernels/CLThresholdKernel.h"
#include "src/core/CL/kernels/CLTileKernel.h"
#include "src/core/CL/kernels/CLTransposeKernel.h"
#include "src/core/CL/kernels/CLWarpAffineKernel.h"
#include "src/core/CL/kernels/CLWarpPerspectiveKernel.h"
#include "src/core/CL/kernels/CLWeightsReshapeKernel.h"
#include "src/core/CL/kernels/CLWinogradFilterTransformKernel.h"
#include "src/core/CL/kernels/CLWinogradInputTransformKernel.h"
#include "src/core/CL/kernels/CLWinogradOutputTransformKernel.h"
#include "src/core/CL/kernels/ICLDepthwiseConvolutionLayer3x3Kernel.h"

#endif /* ARM_COMPUTE_CLKERNELS_H */
