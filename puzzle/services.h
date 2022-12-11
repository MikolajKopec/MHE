#include <random>
#include <vector>
#include "puzzle.h"


#ifndef MHE1_SERVICES_H
#define MHE1_SERVICES_H
light_up generate_random_puzzle(int size);
bool check_if_puzzles_is_this_same(light_up puzzle1,light_up puzzle2);
light_up find_random_neighbor(light_up &basic_board,light_up puzzle);

#endif //MHE1_SERVICES_H
