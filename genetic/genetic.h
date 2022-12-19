//
// Created by mikol on 19.12.2022.
//

#ifndef MHE1_GENETIC_H
#define MHE1_GENETIC_H

#include "../puzzle/puzzle.h"

using chromosome_t = std::vector<int>;
using phenotype_t = std::vector<int>;


chromosome_t create_chromosome(int size);
using population_t = std::vector<chromosome_t>;
population_t one_point_crossover(chromosome_t chromosome1 ,chromosome_t chromosome2);
chromosome_t prob_mutation(chromosome_t chromosome1,int probability);
int roulette(std::vector<int> res_for_pop);
chromosome_t create_chromosome(int size,chromosome_t body);
phenotype_t decode_f(chromosome_t chromosome);
std::vector<double> fitnnes_function(light_up board_to_solve,population_t pop);
std::map<std::string,std::any> genetic_alg(light_up board_to_solve,int iterations,double mutation_prob);

#endif //MHE1_GENETIC_H
