#include "../puzzle/services.h"
#include "simulated_annealing.h"
#include <map>
#include <any>

//
// Created by mikol on 11.12.2022.
//



std::map<std::string,std::any> simulated_annealing(light_up board_to_solve,int iterations){
    std::map<std::string,std::any> result;
    light_up best_puzzle = generate_random_puzzle(board_to_solve.size);
    light_up helper;
    best_puzzle.evaluate_puzzle(board_to_solve);
    for(int i=0;i<iterations;i++){
        helper = best_puzzle;
        best_puzzle = find_random_neighbor(board_to_solve,best_puzzle);
        best_puzzle.evaluate_puzzle(board_to_solve);
        std::cout<<i;
        if(best_puzzle.rating<helper.rating){
            continue;
        }

    }
    result["puzzle"] = best_puzzle;
    return result;
}
