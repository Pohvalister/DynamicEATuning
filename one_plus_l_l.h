#ifndef ONEPLUSLAMBDALAMBDAGA_H
#define ONEPLUSLAMBDALAMBDAGA_H
#include <cstddef>
#include <set>
#include <functional>
#include <random>

template<std::size_t ProblemSize>
class OnePlusLambdaLambdaGA
{
public:
    using species = bool[ProblemSize];

    OnePlusLambdaLambdaGA(const std::function<double(species)>& f, int populationSize, const std::set<species>& sample);
    OnePlusLambdaLambdaGA(const std::function<double(species)>& f, int populationSize);

public:
    void iterate();

private:
    std::set<bool[ProblemSize]> generation;
    const std::function<double(bool[ProblemSize])> func;
    int lambda;
};

template<std::size_t ProblemSize>
OnePlusLambdaLambdaGA<ProblemSize>::OnePlusLambdaLambdaGA(const std::function<double(species)>& f,
                                                          int populationSize,
                                                          const std::set<bool[ProblemSize]>& sample)
        : func(f)
        , generation(sample)
        , lambda(populationSize)
{}

template<std::size_t ProblemSize>
void OnePlusLambdaLambdaGA<ProblemSize>::iterate(){
    std::set<species> nextGen;
    double mutatuion_prob = (double)lambda/(double)(ProblemSize);
    int l = std::rand()%ProblemSize;
    double crossover_prob = 1.0/lambda;

    for (int i = 0; i < lambda; i++){
        for (int j = 0; j < ProblemSize; j++){

        }
    }
}

#endif //ONEPLUSLAMBDALAMBDAGA_H