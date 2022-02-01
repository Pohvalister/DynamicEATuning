#ifndef ONEPLUSLAMBDALAMBDAGA_H
#define ONEPLUSLAMBDALAMBDAGA_H
#include <cstddef>
#include <set>
#include <functional>
#include <random>
#include "parray.hpp"
#include "datapar.hpp"

#include "ea_parameters.h"
#include "solver_interface.h"
#include "tasks/task_interface.h"
#include "advisers/adviser_interface.h"

using namespace pasl::pctl;

struct OnePlusLL_param : public VariableParameters{
    int mutation_phase_population_size; //L1
    int crossover_phase_population_size; //L2
    double mutation_coefficient; //k
    double crossover_probability; //c
};

template<std::size_t ProblemSize>
class OnePlusLambdaLambdaGA : public EA<ProblemSize, Advisor>
{
public:
    using species = bool[ProblemSize];

    OnePlusLambdaLambdaGA(const std::function<double(species)>& f, const std::set<species>& sample);
    OnePlusLambdaLambdaGA(const std::function<double(species)>& f);

    std::pair<double, std::vector<bool>> run_search();
private:
    bool iterate(parray<bool>& parent); // bool - have found new species (written in parent)

    bool keep_iterating();

private:
    OnePlusLL_param m_param;
    Advisor m_advisor;
    std::vector<bool> m_best_species;
    double m_best_score;

    const std::function<double(bool[ProblemSize])> m_func;
};



template<std::size_t ProblemSize, typename Advisor>
OnePlusLambdaLambdaGA<ProblemSize, Advisor>::OnePlusLambdaLambdaGA(const std::function<double(species)>& f,
                                                          int populationSize,
                                                          const std::set<bool[ProblemSize]>& sample)
        : m_func(f)
{
    m_param.mutation_phase_population_size = populationSize;
}

template<std::size_t ProblemSize, typename Advisor>
bool OnePlusLambdaLambdaGA<ProblemSize, Advisor>::iterate(std::vector<bool>& parent, double& parent_result){

    int mutation_generation_size = m_param.mutation_phase_population_size;
    int crossover_generation_size = m_param.crossover_phase_population_size;
    double mutatuion_prob = (double)m_param.mutation_phase_population_size/(double)(ProblemSize);
    int l = std::rand()%ProblemSize;
    double crossover_prob = 1.0/m_param.crossover_phase_population_size;

    parray<std::vector<bool>> generation(mutation_generation_size);
    parray<int> results(mutation_generation_size);

    parallel_for(0,generation.size(),[&](int gen_pointer){
        generation[gen_pointer] = parent;
        parallel_for(0,parent.size(),[&](int pointer){
            if (rand()%ProblemSize < mutatuion_prob)
                generation[gen_pointer][pointer] = !generation[gen_pointer][pointer];
        });

        results[gen_pointer] = 0;//m_func(species);
    });

    int pointerToBest = reduce(0, results.size(), 0, [&](int pointer1, int pointer2){
        return (results[pointer1] < results[pointer2] ? pointer1 : pointer2);
    });

    std::vector<bool> bestNewGen = generation[pointerToBest];

    generation.resize(crossover_generation_size);
    parallel_for(0, generation.size(), [&](int gen_pointer){
       generation[gen_pointer] = parent;
        parallel_for(0, parent.size(), [&](int byte_pointer){
            if (rand()%ProblemSize < crossover_prob)
                generation[gen_pointer][byte_pointer]  = bestNewGen[byte_pointer];
        });
    });

    pointerToBest = reduce(0, results.size(), 0, [&](int pointer1, int pointer2){
        return (results[pointer1] < results[pointer2] ? pointer1 : pointer2);
    });

    bestNewGen = generation[pointerToBest];

    if (results[pointerToBest] > parent_result){
        parent_result = results[pointerToBest];
        parent = bestNewGen;
        return true;
    }
    return false;
}

template<std::size_t ProblemSize, typename Advisor>
std::pair<double, std::vector<bool>> OnePlusLambdaLambdaGA<ProblemSize, Advisor>::run_search() {
    std::set<std::pair<std::vector<bool>, int>> data;
    std::set<std::pair<std::vector<bool>, int>> new_data;

    while (keep_iterating()){
        fork2([&] {
            for (std::size_t i = 0; i <m_param.iterations; i++){
                if (iterate(m_best_species, m_best_score))
                    new_data.insert(std::make_pair(m_best_species, m_best_score));
            }
        }, {
            m_advisor.get_advice(data);
            data.clear();
        });
        std::swap(data, new_data);
    }

    return std::make_pair(m_best_score, m_best_species);
}

#endif //ONEPLUSLAMBDALAMBDAGA_H