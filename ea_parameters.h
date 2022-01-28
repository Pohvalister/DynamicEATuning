#ifndef ONEPLUSLL_EA_PARAMETERS_H
#define ONEPLUSLL_EA_PARAMETERS_H

#include <cstdint>

struct VariableParameters{
public:
    uint64_t iterations;
};

struct OnePlusLL_param : public VariableParameters{
    int mutation_phase_population_size; //L1
    int crossover_phase_population_size; //L2
    double mutation_coefficient; //k
    double crossover_probability; //c
};

#endif //ONEPLUSLL_EA_PARAMETERS_H
