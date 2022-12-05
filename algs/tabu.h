#include "../puzzle/puzzle.h"


//
// Created by mikol on 04.12.2022.
//

#ifndef MHE1_TABU_H
#define MHE1_TABU_H
light_up generate_unused_neighbor(light_up basic_board,std::vector<light_up> used_neighbors);
std::map<std::string,std::any> tabu(light_up basic_board,int iterations);

#endif //MHE1_TABU_H
