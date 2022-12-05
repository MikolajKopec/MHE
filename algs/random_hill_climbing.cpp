//
// Created by mikol on 05.12.2022.
//

#include <map>
#include <any>
#include "../puzzle/puzzle.h"
#include "random_hill_climbing.h"
#include "../puzzle/services.h"

std::map<std::string,std::any> random_hill_climbing(light_up board_to_solve,int iterations){
    std::map<std::string,std::any> result;
    std::vector<int> rating;
    light_up current_puzzle = generate_random_puzzle(board_to_solve.size);
    int i=0;
    int res = current_puzzle.evaluate_puzzle(board_to_solve);
    rating.push_back(current_puzzle.rating);
//    std::cout<<current_puzzle<<current_puzzle.rating<<std::endl;
    if(res == 0){
        result["iterations"] = 1;
        result["puzzle"] = current_puzzle;
        result["rating"] = rating;
        return result;
    }
    do{
        current_puzzle = current_puzzle.find_best_neighbor(board_to_solve);
        rating.push_back(current_puzzle.rating);
        if(current_puzzle.rating ==0){
            break;
        }
//        std::cout<<current_puzzle.rating<<std::endl;
        i++;
    }while(i != iterations );
//    std::cout<<current_puzzle<<std::endl;
//    std::cout<<current_puzzle.rating<<std::endl;
    result["iterations"] = i;
    result["puzzle"] = current_puzzle;
    result["rating"] = rating;
    return result;
}
