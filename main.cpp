#include <iostream>
#include "parray.hpp"
#include "datapar.hpp"

#include "inst.h"

int main() {
    std::function<double(bool[10])>  f = [](bool a[10]){
        return 1.5;
    };

    ONEPlLL<10> algo(f,10,std::set<bool[10]>());

    return 0;
}
