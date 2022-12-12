#include "services.h"
#include <random>


bool check_if_puzzles_is_this_same(light_up puzzle1,light_up puzzle2){
    for(int i = 0; i<puzzle1.board.size();i++){
        if(puzzle1.board[i]!=puzzle2.board[i]){
            return false;
        }
    }
    return true;
}

light_up generate_random_puzzle(int size){
    std::random_device rd;
    std::mt19937 mt_generator(rd());
    int board_size =size*size;
    std::vector<int> arr (board_size);
    light_up random_puzzle{size,arr};
    std::uniform_int_distribution<int> dist(3,4);
    for(int i = 0;i<board_size;i++){
        random_puzzle.board[i] = -1 * dist(mt_generator);
    }
    return random_puzzle;
}