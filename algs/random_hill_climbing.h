//
// Created by mikol on 04.12.2022.
//

#ifndef MHE1_RANDOM_HILL_CLIMBING_H
#define MHE1_RANDOM_HILL_CLIMBING_H

light_up random_hill_climbing(light_up board_to_solve,int iterations){
    light_up current_puzzle = generate_random_puzzle(board_to_solve.size);
    int res = current_puzzle.evaluate_puzzle(board_to_solve);
    std::cout<<current_puzzle<<current_puzzle.rating<<std::endl;
    if(res == 0){
        return current_puzzle;
    }
    do{
        current_puzzle = current_puzzle.find_best_neighbor(board_to_solve);
        std::cout<<current_puzzle.rating<<std::endl;
        iterations--;
    }while(iterations != 0);
    std::cout<<current_puzzle<<std::endl;
    std::cout<<current_puzzle.rating<<std::endl;
    return current_puzzle;
}

#endif //MHE1_RANDOM_HILL_CLIMBING_H
