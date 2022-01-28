#ifndef ONEPLUSLL_INST_H
#define ONEPLUSLL_INST_H
#include <cstddef>

#include "one_plus_l_l.h"
#include "parameter_advisor.h"
#include "ea_parameters.h"

template<std::size_t ProblemSize>
using ONEPlLL =  OnePlusLambdaLambdaGA<ProblemSize, OneFifth<OnePlusLL_param>> ;

template <std::size_t ProblemSize>
using species = bool[ProblemSize];


#endif //ONEPLUSLL_INST_H
