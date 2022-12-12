
#include "simulated_annealing.h"
#include <map>
#include <any>
#include "../puzzle/services.h"
#include <random>
#include <vector>

//
// Created by mikol on 11.12.2022.
//


light_up find_random_neighbor(light_up &basic_board,light_up puzzle){
    std::random_device rd;
    std::mt19937 mt_generator(rd());
    std::uniform_int_distribution<int> dist(0,basic_board.size);
    int field_number = 0;
    bool neighbor = false;
    light_up random_neighbor = {puzzle.size,puzzle.board};
    do{
        field_number = dist(mt_generator);
        random_neighbor = {puzzle.size,puzzle.board};
        if(random_neighbor.board[field_number]>=0){
            continue;
        }
        neighbor = true;
        if(random_neighbor.board[field_number] == -2){
            random_neighbor.board[field_number] = -4;
        }else if(random_neighbor.board[field_number] == -4){
            random_neighbor.board[field_number] = -2;
        }
    } while (!neighbor);

    return random_neighbor;
}
std::map<std::string,std::any> simulated_annealing(light_up board_to_solve,int iterations){


    std::random_device rd;
    std::mt19937 mt_generator(rd());
    std::map<std::string,std::any> result;
    light_up best_puzzle = generate_random_puzzle(board_to_solve.size);
    light_up helper;
    std::vector<int> rating;
    best_puzzle.evaluate_puzzle(board_to_solve);
    rating.push_back(best_puzzle.rating);
    for(int i=0;i<iterations;i++){
        result["iterations"] = i+1;
        if(best_puzzle.rating==0){
            result["puzzle"] = best_puzzle;
            result["rating"] = best_puzzle.rating;
            result["iteration"] = i+1;
            break;
        }
        helper = best_puzzle;
        best_puzzle = find_random_neighbor(board_to_solve,best_puzzle);
        best_puzzle.evaluate_puzzle(board_to_solve);
//        std::cout<<i;
        if(best_puzzle.rating<=helper.rating){
            rating.push_back(best_puzzle.rating);
            continue;
        }
        std::uniform_real_distribution<double> dist(0.0,1.0);
        int u = dist(mt_generator);
        double expResult = exp( -1 * (abs(double(best_puzzle.rating) - double(helper.rating))) / (1/(double(i)+1)) );
        if(u<expResult){
            rating.push_back(best_puzzle.rating);
            continue;
        }else{
            rating.push_back(helper.rating);
            best_puzzle = helper;
        }
    }
    result["puzzle"] = best_puzzle;
    result["rating"] = rating;
    return result;
}
