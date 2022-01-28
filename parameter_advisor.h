#ifndef ONEPLUSLL_PARAMETER_ADVISOR_H
#define ONEPLUSLL_PARAMETER_ADVISOR_H
#include <vector>

template<typename Parameters>
class ParameterAdvisor{
    ParameterAdvisor(Parameters params) = 0;
    Parameters get_advice(std::set<std::pair<double, std::vector<bool>>>) = 0;
};


template<typename Parameters>
class OneFifth : public ParameterAdvisor<Parameters>{
    OneFifth(Parameters params) {
        m_advice = params;
        m_advice.iterations = ITERATIONS_FOR_TEST;
    }

    Parameters get_advice(std::set<std::pair<double, std::vector<bool>>> newRuns) {
        if (newRuns.size() < 2){
            m_advice.mutation_phase_population_size *= MUTATION_LAMBDA_INCREASE;
            m_advice.crossover_phase_population_size *= CROSSOVER_LAMBDA_INCREASE;
        }
        return m_advice;
    }

private:
    const int ITERATIONS_FOR_TEST = 10;
    const int MUTATION_LAMBDA_INCREASE = 2;
    const int CROSSOVER_LAMBDA_INCREASE = 2;

    Parameters m_advice;
};

template<typename Parameters, std::size_t ProblemSize>
class ABtune : public ParameterAdvisor<Parameters>{
    ABtune(Parameters params){
        m_advice = params;
        m_advice.iterations = ITERATIONS_AMOUNT;
        m_advice.mutation_phase_population_size = STARTING_LAMBDA;
        m_advice.crossover_phase_population_size = STARTING_LAMBDA;
    }

    Parameters get_advice(std::set<std::pair<double, std::vector<bool>>> newRuns){
        if (!newRuns.empty())
            lambda = (lambda * A_VALUE < ProblemSize ? lambda * A_VALUE : ProblemSize);
        else
            lambda = (lambda * B_VALUE > 1 ? lambda * B_VALUE : 1);

        m_advice.mutation_phase_population_size = lambda;
        m_advice.crossover_phase_population_size = lambda;
    }

private:
    const int ITERATIONS_AMOUNT = 1;
    const double STARTING_LAMBDA = 1.0;
    const double A_VALUE = pow(1.5,0.25);
    const double B_VALUE = 2.0/3.0;

    Parameters m_advice;
    double lambda = STARTING_LAMBDA;
};

#endif //ONEPLUSLL_PARAMETER_ADVISOR_H
