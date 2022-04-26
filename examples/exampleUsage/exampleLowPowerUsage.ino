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

#include <Wire.h>

#include <Arduino.h>
#include <SensirionI2CSgp40.h>
#include <SensirionI2CSht4x.h>
#include <VOCGasIndexAlgorithm.h>

SensirionI2CSht4x sht4x;
SensirionI2CSgp40 sgp40;

VOCGasIndexAlgorithm voc_algorithm = VOCGasIndexAlgorithm();
// define the sampling interval in seconds (1sec for 20% power, 10sec for 2% power)
float sampling_interval = 1.0

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }

    Wire.begin();

    sht4x.begin(Wire);
    sgp40.begin(Wire);

    delay(1000);  // needed on some Arduino boards in order to have Serial ready

    int32_t index_offset;
    int32_t learning_time_offset_hours;
    int32_t learning_time_gain_hours;
    int32_t gating_max_duration_minutes;
    int32_t std_initial;
    int32_t gain_factor;
    voc_algorithm.get_tuning_parameters(
        index_offset, learning_time_offset_hours, learning_time_gain_hours,
        gating_max_duration_minutes, std_initial, gain_factor);
    
    voc_algorithm.set_sampling_interval(sampling_interval)

    Serial.println("\nVOC Gas Index Algorithm parameters");
    Serial.print("Index offset:\t");
    Serial.println(index_offset);
    Serial.print("Learing time offset hours:\t");
    Serial.println(learning_time_offset_hours);
    Serial.print("Learing time gain hours:\t");
    Serial.println(learning_time_gain_hours);
    Serial.print("Gating max duration minutes:\t");
    Serial.println(gating_max_duration_minutes);
    Serial.print("Std inital:\t");
    Serial.println(std_initial);
    Serial.print("Gain factor:\t");
    Serial.println(gain_factor);
}

void sgp40MeasureRawSignalLowPower(compensationRh, compensationT){
    uint16_t error;
    char errorMessage[256];
    uint16_t srawVoc = 0;
    // Request a first measurement to heat up the plate (ignoring the result)
    error = sgp40.measureRawSignals(compensationRh, compensationT, srawVoc);

    // Delaying 170 msec to let the plate heat up.
    // Keeping in mind that the measure command already include a 30ms delay
    delay(140)

    // Request the measurement values
    error = sgp40.measureRawSignals(compensationRh, compensationT, srawVoc);
                                    
    // Turn heater off
    errorHeater = sgp40.turnHeaterOff(compensationRh, compensationT, srawVoc);

    // Process raw signals by Gas Index Algorithm to get the VOC index values
    if (error) {
        Serial.print("SGP40 - Error trying to execute measureRawSignals(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    else if (errorHeater){
        Serial.print("SGP40 - Error trying to execute turnHeaterOff(): ");
        errorToString(errorHeater, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        int32_t voc_index = voc_algorithm.process(srawVoc);
        Serial.print("VOC Index: ");
        Serial.print(voc_index);
    }
}

void loop() {
    uint16_t error;
    char errorMessage[256];
    float humidity = 0;     // %RH
    float temperature = 0;  // degreeC
    
    uint16_t srawNox = 0;
    uint16_t defaultCompensationRh = 0x8000;  // in ticks as defined by SGP41
    uint16_t defaultCompensationT = 0x6666;   // in ticks as defined by SGP41
    uint16_t compensationRh = 0;              // in ticks as defined by SGP41
    uint16_t compensationT = 0;               // in ticks as defined by SGP41

    // 1. Sleep: We need the delay to match the desired sampling interval
    // In low power mode, the SGP40 takes 200ms to acquire values.
    // SHT4X also includes a delay of 10ms
    delay(int(sampling_interval)*1000 - 200 - 10);

    // 2. Measure temperature and humidity for SGP internal compensation
    error = sht4x.measureHighPrecision(temperature, humidity);
    if (error) {
        Serial.print(
            "SHT4x - Error trying to execute measureHighPrecision(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
        Serial.println("Fallback to use default values for humidity and "
                       "temperature compensation for SGP41");
        compensationRh = defaultCompensationRh;
        compensationT = defaultCompensationT;
    } else {
        Serial.print("T:");
        Serial.print(temperature);
        Serial.print("\t");
        Serial.print("RH:");
        Serial.println(humidity);

        // convert temperature and humidity to ticks as defined by SGP41
        // interface
        // NOTE: in case you read RH and T raw signals check out the
        // ticks specification in the datasheet, as they can be different for
        // different sensors
        compensationT = static_cast<uint16_t>((temperature + 45) * 65535 / 175);
        compensationRh = static_cast<uint16_t>(humidity * 65535 / 100);
    }

    // 3. Measure SGP40 signals using low power mode
    sgp40MeasureRawSignalLowPower(compensationRh, compensationT)
}
