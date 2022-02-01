#ifndef ONEPLUSLL_ONEMAX_H
#define ONEPLUSLL_ONEMAX_H
#include <vector>

#include "task_interface.h"

class OneMax : Task<int, std::vector<bool>> {
public:
    int evaluate(const std::vector<bool>& species){
        int sum = 0;
        for (bool byte : species)
            sum += (byte ? 1 : 0);
        if(best_val < sum){
            best_val = sum;
            best_species = species;
        }
        return sum;
    }
    bool processing_finished() override{
        return best_val == best_species.size();
    }
private:
    int best_val;
    std::vector<bool> best_species;
};


#endif //ONEPLUSLL_ONEMAX_H
