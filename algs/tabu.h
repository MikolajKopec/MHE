#include "../puzzle/puzzle.h"


//
// Created by mikol on 04.12.2022.
//

#ifndef MHE1_TABU_H
#define MHE1_TABU_H
light_up generate_unused_neighbor(light_up basic_board,std::vector<light_up> used_neighbors){
    light_up best_neighbor = used_neighbors.back();
    light_up current_neighbor = best_neighbor;
    int i = 0;
    for(auto field : current_neighbor.board){
        if(field == -2 || field == -3){
            current_neighbor.board[i] = -4;
        }else if(field == -4){
            current_neighbor.board[i] = -3;
        }
        for(auto used_neighbor : used_neighbors ){
            if(check_if_puzzles_is_this_same(used_neighbor,current_neighbor)) {
//                std::cout<<"Sasiad odwiedzony";
                continue;
            }else{
                best_neighbor.evaluate_puzzle(basic_board);
                current_neighbor.evaluate_puzzle(basic_board);
                if(best_neighbor.rating>=current_neighbor.rating){
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
light_up tabu(light_up basic_board,int iterations){
    light_up result = generate_random_puzzle(basic_board.size);
    result.evaluate_puzzle(basic_board);
    std::vector<light_up> used_neighbors = {result};
    light_up current_neighbor;
    do{
        if(used_neighbors.back().rating==0){
            break;
        }
        current_neighbor = generate_unused_neighbor(basic_board,used_neighbors);
        if(check_if_puzzles_is_this_same(current_neighbor,used_neighbors.back())){
            std::cout<<"im stuck"<<std::endl;
            std::cout<<current_neighbor;
            return current_neighbor;
            }
        used_neighbors.push_back(current_neighbor);
        iterations--;
    } while (iterations !=0);
    std::cout<<"poprawnie"<<std::endl;
    std::cout<<used_neighbors.back();
    std::cout<<used_neighbors.back().rating<<std::endl;
    return used_neighbors.back();
}

#endif //MHE1_TABU_H
