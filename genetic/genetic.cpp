//
// Created by mikol on 19.12.2022.
//
#include <vector>
#include <iostream>
#include <functional>
#include <random>
#include <any>
#include <map>
#include "genetic.h"
std::ostream &operator<<(std::ostream &o,const chromosome_t &chromosome){
    for(auto x : chromosome){
        o<<x;
    }
    o<<std::endl;
}

chromosome_t create_chromosome(int size){
    std::random_device rd;
    std::mt19937 mt_generator(rd());

    std::uniform_int_distribution<int> dist(0,1);
    double random = 0;
    chromosome_t result;
    for(int i=0; i<size;i++){
        random = dist(mt_generator);
        result.push_back(random);
    }
    chromosome_t chrom = result;
    return chrom;
}

phenotype_t decode_f(chromosome_t chromosome){
    phenotype_t result;
    for(int field : chromosome){
        if(field==1){
            result.push_back(-4);
        }else if(field == 0){
            result.push_back(-3);
        }
    }
    return result;
}
std::vector<double> fitnnes_function(light_up board_to_solve,population_t pop){
    std::vector<double> fitness_result;
    for(chromosome_t chromosome : pop){
        phenotype_t phenotype =decode_f(chromosome);
        light_up puzzle = {int(sqrt(chromosome.size())),phenotype};
        puzzle.evaluate_puzzle(board_to_solve);
//        std::cout<<"Ocena rozwizania to "<<puzzle.rating<<"\n";
//        std::cout<<chromosome;
        fitness_result.push_back(1/double(puzzle.rating+1));
//        std::cout<<puzzle.rating<<std::endl;
    }
    return fitness_result;
}

population_t one_point_crossover(chromosome_t chromosome1 ,chromosome_t chromosome2) {
    std::random_device rd;
    std::mt19937 mt_generator(rd());

    std::uniform_int_distribution<int> dist(0, chromosome1.size());
    int slice_point = dist(mt_generator);
//    std::cout<<slice_point<<std::endl;
    for (int i = slice_point; i < chromosome1.size(); i++) {
        std::swap(chromosome1[i], chromosome2[i]);
    }
    return {chromosome1, chromosome2};
}

chromosome_t prob_mutation(chromosome_t chromosome1,int probability){
    std::random_device rd;
    std::mt19937 mt_generator(rd());
    std::uniform_int_distribution<int> distribution(1, 100);
    for(int i=0; i < chromosome1.size(); i++){
        int value=distribution(mt_generator);
        if(value < probability){
                if(chromosome1[i] == 0){
                    chromosome1[i]= 1;
                }else{
                    chromosome1[i] = 0;
                }

        }
    }
    return chromosome1;
}

int roulette(std::vector<double> res_for_pop){
    std::random_device rd;
    std::mt19937 mt_generator(rd());
    double roulette_wheel = 0;
//    int max_in_pop = 0;
//    for(auto x : res_for_pop){
//        if(x>max_in_pop){
//            max_in_pop=x;
//        }
//    }
    for(auto x : res_for_pop){
        roulette_wheel = roulette_wheel + x;
    }
    std::uniform_real_distribution<double> dist(0.0,roulette_wheel);
    double val = dist(mt_generator);
    double h = 0;
//    std::cout<<val<<std::endl;
//    std::cout<<roulette_wheel<<std::endl;
    for(int i=0;i<res_for_pop.size();i++){
//        h = h+abs(max_in_pop - res_for_pop[i]);
        h = h+res_for_pop[i];
//        std::cout<<h<<std::endl;
        if(h>val){
            return i;
        }


    }
}


std::map<std::string,std::any> genetic_alg(light_up board_to_solve,int iterations,double mutation_prob){
    std::map<std::string,std::any> result;
    std::vector<int> rating;
    int number=0;
    population_t preavious_pop;
    for(int i=0;i<1000;i++){
        preavious_pop.push_back(create_chromosome(pow(board_to_solve.size,2)));
    }


    std::vector<double> actual_pop_fitness = fitnnes_function(board_to_solve, preavious_pop);

    population_t new_pop;
    for(int i=0;i<iterations;i++){
        for(int i=0;i<preavious_pop.size();i++){
            new_pop.push_back(preavious_pop[roulette(actual_pop_fitness)]);
        }

        for(int i=1;i<new_pop.size();i=i+2){
                population_t pop_of_two = {new_pop[i],new_pop[i-1]};

                pop_of_two = one_point_crossover(pop_of_two[0],pop_of_two[1]);

                pop_of_two[0] = prob_mutation(pop_of_two[0],mutation_prob);
                pop_of_two[1] = prob_mutation(pop_of_two[1],mutation_prob);
                new_pop[i] = pop_of_two[0];
                new_pop[i-1] = pop_of_two[1];
        }
        actual_pop_fitness = fitnnes_function(board_to_solve, new_pop);

        double best_score = 0;
        for(int i =0;i<actual_pop_fitness.size();i++){
            if(actual_pop_fitness[i]>best_score){
                best_score = actual_pop_fitness[i];
                result["puzzle"] = new_pop[i];
            }
        }

        rating.push_back(best_score);
        preavious_pop = new_pop;
        new_pop.clear();
        number++;
        std::cout<<"best score in generation"<<best_score<<std::endl;
        if(best_score==1){
            break;
        }
    }
    std::vector<double> result_fitness = fitnnes_function(board_to_solve,new_pop);


    result["iterations"] = number;
    result["rating"] = rating;
    return result;
}

