#ifndef ONEPLUSLL_PARAMETER_ADVISOR_H
#define ONEPLUSLL_PARAMETER_ADVISOR_H
#include <vector>

class ParameterAdvisor{
    virtual void add_iteration() = 0;
    virtual std::vector<int> get_advise() = 0;
};

#endif //ONEPLUSLL_PARAMETER_ADVISOR_H
