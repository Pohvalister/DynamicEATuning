#ifndef ONEPLUSLL_ADVISOR_H
#define ONEPLUSLL_ADVISOR_H
#include <vector>
#include <set>

#include "../solvers/ea_parameters.h"

template<typename Parameters>
class ParameterAdvisor{
    virtual Parameters get_advice(const std::set<std::pair<double, std::vector<bool>>>&) = 0;
};

#endif //ONEPLUSLL_ADVISOR_H
