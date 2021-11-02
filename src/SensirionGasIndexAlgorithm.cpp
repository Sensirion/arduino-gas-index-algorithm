#include "SensirionGasIndexAlgorithm.h"
#include <stdlib.h>

SensirionGasIndexAlgorithm::SensirionGasIndexAlgorithm(int32_t algorithm_type) {
    params = (GasIndexAlgorithmParams*)malloc(sizeof(GasIndexAlgorithmParams));
    GasIndexAlgorithm_init(params, algorithm_type);
}

int32_t SensirionGasIndexAlgorithm::process(int32_t sraw) {
    int32_t index_value = 0;
    GasIndexAlgorithm_process(params, sraw, &index_value);
    return index_value;
}