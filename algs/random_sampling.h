#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <random>
#include <fstream>
#include <cstdlib>

#ifndef MHE1_RANDOM_SAMPLING_H
#define MHE1_RANDOM_SAMPLING_H




light_up find_resolve_random_sample(light_up board_to_solve,int iterations){
    std::vector<light_up> used_samples;
    int i = 0;
    bool res = false;
    do{
        used_samples.push_back(generate_random_puzzle(board_to_solve.size));
        res = used_samples[i].evaluate_puzzle(board_to_solve);
//        std::cout<<"res rating"<<used_samples[i].rating<<std::endl;
        i=i+1;
    }while (res != 0);
    std::cout<<used_samples.back();
    std::cout<<"Proba numer: "<<i<<std::endl;
    return used_samples[i-1];
}

#endif //MHE1_RANDOM_SAMPLING_H
