#include <map>
#include <any>
#include "tabu.h"
#include "../puzzle/services.h"

//
// Created by mikol on 05.12.2022.
//

light_up generate_unused_neighbor(light_up basic_board,std::vector<light_up> used_neighbors){
    light_up best_neighbor = used_neighbors.back();
    light_up current_neighbor = best_neighbor;
    int actual_best = 1000;
    int i = 0;
    for(auto field : current_neighbor.board){
        if(field == -2 || field == -3){
            current_neighbor.board.at(i) = -4;
        }else if(field == -4){
            current_neighbor.board.at(i) = -3;
        }
        for(auto used_neighbor : used_neighbors ){
            if(check_if_puzzles_is_this_same(used_neighbor,current_neighbor)) {
//                std::cout<<"Sasiad odwiedzony";
                continue;
            }else{
                best_neighbor.evaluate_puzzle(basic_board);
                current_neighbor.evaluate_puzzle(basic_board);
                if(current_neighbor.rating<=actual_best){
                    actual_best = current_neighbor.rating;
                    // std::cout<<"rating: "<<best_neighbor.rating<<std::endl;
                    best_neighbor = current_neighbor;
                }
            }
        }

        if(current_neighbor.board[i] == -2 || field == -3){
            current_neighbor.board[i] = -4;
        }else if(current_neighbor.board[i] == -4){
            current_neighbor.board[i] = -3;
        }

        i++;
    }
    return best_neighbor;
}
std::map<std::string,std::any> tabu(light_up basic_board,int iterations){
    std::map<std::string,std::any> result;
    light_up starter = generate_random_puzzle(basic_board.size);
    starter.evaluate_puzzle(basic_board);
    std::vector<light_up> used_neighbors = {starter};
    std::vector<int> rating = {starter.rating};
    int i = 0;
    light_up current_neighbor;
    do{
        if(used_neighbors.back().rating==0){
            break;
        }
        current_neighbor = generate_unused_neighbor(basic_board,used_neighbors);
        if(check_if_puzzles_is_this_same(current_neighbor,used_neighbors.back())){
            std::cout<<"im stuck"<<std::endl;
//            std::cout<<current_neighbor;
            result["puzzle"] = current_neighbor;
            result["iterations"] = i;
            result["rating"] = rating;
            return result;
        }
        used_neighbors.push_back(current_neighbor);
        rating.push_back(current_neighbor.rating);
        i++;
    } while (i != iterations);
//    std::cout<<"poprawnie"<<std::endl;
//    std::cout<<used_neighbors.back();
//    std::cout<<used_neighbors.back().rating<<std::endl;
    result["puzzle"] = used_neighbors.back();
    result["iterations"] = i;
    result["rating"] = rating;
    return result;
}