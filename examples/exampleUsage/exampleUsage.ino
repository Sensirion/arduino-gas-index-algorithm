/*
 * I2C-Generator: 0.2.0
 * Yaml Version: 0.1.0
 * Template Version: local build
 */
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

#include "SensirionGasIndexAlgorithm.h"
#include <Arduino.h>
#include <SensirionI2CSgp41.h>
#include <SensirionI2CSht4x.h>
#include <Wire.h>

SensirionI2CSgp41 sgp41;
SensirionI2CSht4x sht4x;
SensirionGasIndexAlgorithm voc_algorithm = SensirionGasIndexAlgorithm(0);

// time in seconds needed for NOx conditioning
uint16_t conditioning_s = 10;

void setup() {

    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }

    Wire.begin();

    uint16_t error;
    char errorMessage[256];

    sgp41.begin(Wire);
    sht4x.begin(Wire);
}

void loop() {
    uint16_t error;
    char errorMessage[256];
    uint16_t srawRhTicks = 0;    // in ticks as defined by SHT4x
    uint16_t srawTempTicks = 0;  // in ticks as defined by SHT4x
    uint16_t srawVoc = 0;
    uint16_t srawNox = 0;
    uint16_t defaultRh = 0x8000;   // in ticks as defined by SGP41
    uint16_t defaultT = 0x6666;    // in ticks as defined by SGP41
    uint16_t compensation_RH = 0;  // in ticks as defined by SGP41
    uint16_t compensation_T = 0;   // in ticks as defined by SGP41

    delay(1000);

    error = sht4x.measureHighPrecisionTicks(srawTempTicks, srawRhTicks);
    if (error) {
        Serial.print(
            "SHT4x - Error trying to execute measureHighPrecision(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
        Serial.println("Fallback to use default values for humidity and "
                       "temperature compensation for SGP41");
        compensation_RH = defaultRh;
        compensation_T = defaultT;
    } else {
        float temperature =
            static_cast<float>(srawTempTicks * 175.0 / 65535.0 - 45.0);
        float humidity = static_cast<float>(srawRhTicks * 125.0 / 65535.0 - 6);
        Serial.print("Temperature:");
        Serial.print(temperature);
        Serial.print("\t");
        Serial.print("Humidity:");
        Serial.println(humidity);

        // convert temperature and humidity from ticks returned by SHT4x to
        // ticks as defined by SGP41 interface temperature ticks are identical
        // on SHT4x and SGP41
        compensation_T = srawTempTicks;
        compensation_RH = (srawRhTicks * 125 / 65535 - 6) * 65535 / 100;
    }

    if (conditioning_s > 0) {
        // During NOx conditioning (10s) SRAW NOx will remain 0
        error = sgp41.conditioning(compensation_RH, compensation_T, srawVoc);
        conditioning_s--;
    } else {
        error =
            sgp41.measureRaw(compensation_RH, compensation_T, srawVoc, srawNox);
    }

    if (error) {
        Serial.print("SGP41 - Error trying to execute measureRaw(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        Serial.print("SRAW_VOC:");
        Serial.print(srawVoc);
        Serial.print("\t");
        Serial.print("SRAW_NOx:");
        Serial.println(srawNox);
        int32_t voc_index = voc_algorithm.process(srawVoc);
        Serial.print("VOC Index:");
        Serial.println(voc_index);
    }
}
