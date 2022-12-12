//
// Created by mikol on 11.12.2022.
//

#ifndef MHE1_SIMULATED_ANNEALING_H
#define MHE1_SIMULATED_ANNEALING_H
#include "../puzzle/puzzle.h"
#include <map>
#include <any>

std::map<std::string,std::any> simulated_annealing(light_up board_to_solve, int iterations);
#endif //MHE1_SIMULATED_ANNEALING_H
