//
// Created by mikol on 05.12.2022.
//
#include <map>
#include <any>
#include "../puzzle/services.h"

#include "random_hill_climbing.h"

std::map<std::string,std::any> random_hill_climbing(light_up board_to_solve,int iterations){
    std::map<std::string,std::any> result;
    std::vector<int> rating;
    light_up current_puzzle = generate_random_puzzle(board_to_solve.size);
    int i=0;
    int res = current_puzzle.evaluate_puzzle(board_to_solve);
    rating.push_back(current_puzzle.rating);
//    std::cout<<current_puzzle<<current_puzzle.rating<<std::endl;
    if(rating.back() == 0){
        result["iterations"] = 1;
        result["puzzle"] = current_puzzle;
        result["rating"] = rating;
        return result;
    }
    do{
        i++;
        current_puzzle = current_puzzle.find_best_neighbor(board_to_solve);
        current_puzzle.rating = current_puzzle.evaluate_puzzle(board_to_solve);
        rating.push_back(current_puzzle.rating);
        if(rating.back() == 0){
            break;
        }
//        std::cout<<current_puzzle.rating<<std::endl;
    }while(i < iterations );
//    std::cout<<current_puzzle<<std::endl;
//    std::cout<<current_puzzle.rating<<std::endl;
    result["iterations"] = i;
    result["puzzle"] = current_puzzle;
    result["rating"] = rating;
    return result;
}
