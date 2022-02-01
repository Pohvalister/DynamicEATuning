#ifndef ONEPLUSLL_PROBLEM_INTERFACE_H
#define ONEPLUSLL_PROBLEM_INTERFACE_H

template <typename In, typename Out>
class Task{
public:
    virtual Out evaluate(const In&) = 0;
    virtual bool processing_finished() = 0;
};
#endif //ONEPLUSLL_PROBLEM_INTERFACE_H
