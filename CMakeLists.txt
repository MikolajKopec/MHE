cmake_minimum_required(VERSION 3.24)
project(MHE1)

set(CMAKE_CXX_STANDARD 17)

add_executable(MHE1 main.cpp puzzle/puzzle.h algs/random_sampling.h puzzle/services.h algs/hill_climbing.h algs/random_hill_climbing.h algs/tabu.h puzzle/puzzle.cpp puzzle/services.cpp algs/full_audit.cpp algs/hill_climbing.cpp algs/random_hill_climbing.cpp algs/random_sampling.cpp algs/tabu.cpp algs/simulated_annealing.h algs/simulated_annealing.cpp)
