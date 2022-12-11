#include "services.h"


std::random_device rd;
std::mt19937 mt_generator(rd());

light_up generate_random_puzzle(int size){
    int board_size =size*size;
    std::vector<int> arr (board_size);
    light_up random_puzzle{size,arr};
    std::uniform_int_distribution<int> dist(3,4);
    for(int i = 0;i<board_size;i++){
        random_puzzle.board[i] = -1 * dist(mt_generator);
    }
    return random_puzzle;
}
bool check_if_puzzles_is_this_same(light_up puzzle1,light_up puzzle2){
    for(int i = 0; i<puzzle1.board.size();i++){
        if(puzzle1.board[i]!=puzzle2.board[i]){
            return false;
        }
    }
    return true;
}
light_up find_random_neighbor(light_up &basic_board,light_up puzzle){
    std::uniform_int_distribution<int> dist(0,basic_board.size);
    int field_number = dist(mt_generator);
    bool neigbor_correct = false;
    light_up random_neighbor;
    do{
        random_neighbor = {puzzle.size,puzzle.board};
        if(random_neighbor.board[field_number]>=0){
            continue;
        }
        neigbor_correct = true;
        if(random_neighbor.board[field_number] == -2){
            random_neighbor.board[field_number] = -4;
        }else if(random_neighbor.board[field_number] == -4){
            random_neighbor.board[field_number] = -2;
        }
    } while (!neigbor_correct);

    return random_neighbor;
}