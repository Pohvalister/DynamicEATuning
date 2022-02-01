#ifndef ONEPLUSLL_SOLVER_INTERFACE_H
#define ONEPLUSLL_SOLVER_INTERFACE_H

#include "advisers/advisor_interface.h"

template<std::size_t ProblemSize>
class EASolver{
public:
    virtual void run_search() = 0;

protected:
    virtual void iterate() = 0;
};

#endif //ONEPLUSLL_SOLVER_INTERFACE_H
