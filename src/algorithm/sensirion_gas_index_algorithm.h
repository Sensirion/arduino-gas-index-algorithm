/*
 * Copyright (c) 2021, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef GASINDEXALGORITHM_H_
#define GASINDEXALGORITHM_H_

#include <stdint.h>

typedef int32_t fix16_t;

#define F16(x) \
    ((fix16_t)(((x) >= 0) ? ((x)*65536.0 + 0.5) : ((x)*65536.0 - 0.5)))

#ifndef __cplusplus

#if __STDC_VERSION__ >= 199901L
#include <stdbool.h>
#else

#ifndef bool
#define bool int
#define true 1
#define false 0
#endif  // bool

#endif  // __STDC_VERSION__

#endif  // __cplusplus

// Should be set by the building toolchain
#ifndef LIBRARY_VERSION_NAME
#define LIBRARY_VERSION_NAME "3.0.0-g651c55f"
#endif

#define GasIndexAlgorithm_ALGORITHM_TYPE_VOC (0)
#define GasIndexAlgorithm_ALGORITHM_TYPE_NOX (1)
#define GasIndexAlgorithm_SAMPLING_INTERVAL (1.)
#define GasIndexAlgorithm_INITIAL_BLACKOUT (45.)
#define GasIndexAlgorithm_VOC_INDEX_GAIN (230.)
#define GasIndexAlgorithm_NOX_INDEX_GAIN (-230.)
#define GasIndexAlgorithm_SRAW_STD_INITIAL (50.)
#define GasIndexAlgorithm_SRAW_STD_BONUS_VOC (220.)
#define GasIndexAlgorithm_SRAW_STD_BONUS_NOX (450.)
#define GasIndexAlgorithm_TAU_MEAN_HOURS (12.)
#define GasIndexAlgorithm_TAU_VARIANCE_HOURS (12.)
#define GasIndexAlgorithm_TAU_INITIAL_MEAN (20.)
#define GasIndexAlgorithm_INIT_DURATION_MEAN ((3600. * 0.75))
#define GasIndexAlgorithm_INIT_TRANSITION_MEAN (0.01)
#define GasIndexAlgorithm_TAU_INITIAL_VARIANCE (2500.)
#define GasIndexAlgorithm_INIT_DURATION_VARIANCE ((3600. * 1.45))
#define GasIndexAlgorithm_INIT_TRANSITION_VARIANCE (0.01)
#define GasIndexAlgorithm_GATING_THRESHOLD (340.)
#define GasIndexAlgorithm_GATING_THRESHOLD_INITIAL (510.)
#define GasIndexAlgorithm_GATING_THRESHOLD_TRANSITION (0.09)
#define GasIndexAlgorithm_GATING_VOC_MAX_DURATION_MINUTES ((60. * 3.))
#define GasIndexAlgorithm_GATING_NOX_MAX_DURATION_MINUTES ((60. * 3.))
#define GasIndexAlgorithm_GATING_MAX_RATIO (0.3)
#define GasIndexAlgorithm_SIGMOID_L (500.)
#define GasIndexAlgorithm_SIGMOID_K_VOC (-0.0065)
#define GasIndexAlgorithm_SIGMOID_X0_VOC (213.)
#define GasIndexAlgorithm_SIGMOID_K_NOX (-0.008)
#define GasIndexAlgorithm_SIGMOID_X0_NOX (750.)
#define GasIndexAlgorithm_VOC_INDEX_OFFSET_DEFAULT (100.)
#define GasIndexAlgorithm_NOX_INDEX_OFFSET (1.)
#define GasIndexAlgorithm_LP_TAU_FAST (20.0)
#define GasIndexAlgorithm_LP_TAU_SLOW (500.0)
#define GasIndexAlgorithm_LP_ALPHA (-0.2)
#define GasIndexAlgorithm_VOC_SRAW_MINIMUM (20000)
#define GasIndexAlgorithm_NOX_SRAW_MINIMUM (10000)
#define GasIndexAlgorithm_PERSISTENCE_UPTIME_GAMMA ((3. * 3600.))
#define GasIndexAlgorithm_MEAN_VARIANCE_ESTIMATOR__GAMMA_SCALING (64.)
#define GasIndexAlgorithm_MEAN_VARIANCE_ESTIMATOR__ADDITIONAL_GAMMA_MEAN_SCALING \
    (8.)
#define GasIndexAlgorithm_MEAN_VARIANCE_ESTIMATOR__FIX16_MAX (32767.)

typedef struct {
    int32_t mAlgorithm_Type;
    fix16_t mIndex_Offset;
    fix16_t mIndex_Gain;
    int32_t mSraw_Minimum;
    fix16_t mGating_Max_Duration_Minutes;
    fix16_t mSraw_Std_Bonus;
    fix16_t mTau_Mean_Hours;
    fix16_t mTau_Variance_Hours;
    fix16_t mSraw_Std_Initial;
    fix16_t mUptime;
    fix16_t mSraw;
    fix16_t mGas_Index;
    fix16_t m_Mean_Variance_Estimator__Gating_Max_Duration_Minutes;
    bool m_Mean_Variance_Estimator___Initialized;
    fix16_t m_Mean_Variance_Estimator___Mean;
    fix16_t m_Mean_Variance_Estimator___Sraw_Offset;
    fix16_t m_Mean_Variance_Estimator___Std;
    fix16_t m_Mean_Variance_Estimator___Gamma_Mean;
    fix16_t m_Mean_Variance_Estimator___Gamma_Variance;
    fix16_t m_Mean_Variance_Estimator___Gamma_Initial_Mean;
    fix16_t m_Mean_Variance_Estimator___Gamma_Initial_Variance;
    fix16_t m_Mean_Variance_Estimator__Gamma_Mean;
    fix16_t m_Mean_Variance_Estimator__Gamma_Variance;
    fix16_t m_Mean_Variance_Estimator___Uptime_Gamma;
    fix16_t m_Mean_Variance_Estimator___Uptime_Gating;
    fix16_t m_Mean_Variance_Estimator___Gating_Duration_Minutes;
    fix16_t m_Mean_Variance_Estimator___Sigmoid__L;
    fix16_t m_Mean_Variance_Estimator___Sigmoid__K;
    fix16_t m_Mean_Variance_Estimator___Sigmoid__X0;
    fix16_t m_Mox_Model__Sraw_Std;
    fix16_t m_Mox_Model__Sraw_Std_Bonus;
    fix16_t m_Mox_Model__Sraw_Mean;
    fix16_t m_Mox_Model__Index_Gain;
    fix16_t m_Sigmoid_Scaled__Offset;
    fix16_t m_Adaptive_Lowpass__A1;
    fix16_t m_Adaptive_Lowpass__A2;
    bool m_Adaptive_Lowpass___Initialized;
    fix16_t m_Adaptive_Lowpass___X1;
    fix16_t m_Adaptive_Lowpass___X2;
    fix16_t m_Adaptive_Lowpass___X3;
} GasIndexAlgorithmParams;

void GasIndexAlgorithm_init(GasIndexAlgorithmParams* params,
                            int32_t algorithm_type);
void GasIndexAlgorithm_get_states(GasIndexAlgorithmParams* params,
                                  int32_t* state0, int32_t* state1);
void GasIndexAlgorithm_set_states(GasIndexAlgorithmParams* params,
                                  int32_t state0, int32_t state1);
void GasIndexAlgorithm_get_tuning_parameters(
    GasIndexAlgorithmParams* params, int32_t* index_offset,
    int32_t* learning_time_offset_hours, int32_t* learning_time_gain_hours,
    int32_t* gating_max_duration_minutes, int32_t* std_initial);
void GasIndexAlgorithm_set_tuning_parameters(
    GasIndexAlgorithmParams* params, int32_t index_offset,
    int32_t learning_time_offset_hours, int32_t learning_time_gain_hours,
    int32_t gating_max_duration_minutes, int32_t std_initial);
void GasIndexAlgorithm_process(GasIndexAlgorithmParams* params, int32_t sraw,
                               int32_t* gas_index);

#endif /* GASINDEXALGORITHM_H_ */
