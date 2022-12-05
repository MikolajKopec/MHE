//
// Created by mikol on 05.12.2022.
//

#include <string>
#include <any>
#include <map>
#include "../puzzle/puzzle.h"
#include "hill_climbing.h"
std::map<std::string,std::any> hill_climbing(light_up board_to_solve,int iterations){
    std::map<std::string,std::any> result;
    std::vector<int> arr (board_to_solve.board.size());
    std::fill_n(arr.begin(),board_to_solve.board.size(),-3);
    std::vector<int> rating;
    light_up current_puzzle = {board_to_solve.size,arr};
    int i=0;
    int res = current_puzzle.evaluate_puzzle(board_to_solve);
//    std::cout<<current_puzzle<<current_puzzle.rating<<std::endl;
    if(res == 0){
        result["puzzle"] = current_puzzle;
        result["iterations"] = 1;
        result["rating"] = rating;
        return result;
    }
    do{
        current_puzzle = current_puzzle.find_best_neighbor(board_to_solve);
        current_puzzle.evaluate_puzzle(board_to_solve);
        rating.push_back(current_puzzle.rating);
        if(current_puzzle.rating==0){
            break;
        }
//        std::cout<<current_puzzle.rating<<std::endl;
        i++;
    }while(i != iterations);
//    std::cout<<current_puzzle<<std::endl;
    result["iterations"] = i+2;
    result["puzzle"] = current_puzzle;
    result["rating"] = rating;
    result["evaluate"] = i+2;
    return result;
}