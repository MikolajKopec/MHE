//
// Created by mikol on 05.12.2022.
//


#include <map>
#include <string>
#include <any>
#include "../puzzle/puzzle.h"
#include "../puzzle/services.h"

std::map<std::string,std::any> find_resolve_random_sample(light_up board_to_solve, int iterations){
    std::map<std::string,std::any> result;
    std::vector<light_up> used_samples;
    std::vector<int> rating;
    int i = 0;
    bool res = false;
    do{
        used_samples.push_back(generate_random_puzzle(board_to_solve.size));
        res = used_samples[i].evaluate_puzzle(board_to_solve);
        rating.push_back(used_samples[i].rating);
//        std::cout<<"res rating"<<used_samples[i].rating<<std::endl;
        i=i+1;
    }while (res != 0);
//    std::cout<<used_samples.back();
//    std::cout<<"Proba numer: "<<i<<std::endl;
    result["puzzle"] = used_samples[i-1];
    result["iterations"] = i;
    result["rating"] = rating;
    return result;
}
