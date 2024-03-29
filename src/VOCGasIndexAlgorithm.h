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

#ifndef VOCGASINDEXALGORITHM_H
#define VOCGASINDEXALGORITHM_H

#include "SensirionGasIndexAlgorithm.h"

class VOCGasIndexAlgorithm : public SensirionGasIndexAlgorithm {
  public:
    VOCGasIndexAlgorithm();
    /**
     * @brief Construct a new VOCGasIndexAlgorithm object
     *
     * @param sampling_interval Sampling interval of SRAW_VOC values.
     * Algorithm is tested with a sampling interval of 1s (default) and 10s.
     */
    explicit VOCGasIndexAlgorithm(float sampling_interval);

    /**
     * Get current algorithm states. Retrieved values can be used in
     * set_states() to resume operation after a short
     * interruption, skipping initial learning phase.
     * NOTE: This feature can only be used after at least 3 hours of continuous
     * operation.
     * @param state0    State0 to be stored (output variable)
     * @param state1    State1 to be stored (output variable)
     */
    void get_states(float& state0, float& state1);

    /**
     * Set previously retrieved algorithm states to resume operation after a
     * short interruption, skipping initial learning phase. This feature should
     * not be used after interruptions of more than 10 minutes. Call this once
     * after creating a new instance of GasIndexAlgorithm or calling reset() and
     * the optional set_tuning_parameters(), if desired. Otherwise, the
     * algorithm will start with initial learning phase.
     * @param state0    State0 to be restored
     * @param state1    State1 to be restored
     */
    void set_states(float state0, float state1);
};

#endif /* VOCGASINDEXALGORITHM_H */