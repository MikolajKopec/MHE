cmake_minimum_required(VERSION 3.23.2)
project(MHE1)

set(CMAKE_CXX_STANDARD 17)

add_executable(MHE1 main.cpp puzzle/puzzle.cpp puzzle/services.cpp algs/full_audit.cpp algs/hill_climbing.cpp algs/random_hill_climbing.cpp algs/random_sampling.cpp algs/tabu.cpp  algs/simulated_annealing.cpp genetic/genetic.cpp)
