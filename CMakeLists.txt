cmake_minimum_required(VERSION 3.24)
project(MHE1)

set(CMAKE_CXX_STANDARD 17)

add_executable(MHE1 main.cpp puzzle/puzzle.h algs/random_sampling.h puzzle/services.h algs/hill_climbing.h algs/random_hill_climbing.h algs/tabu.h)
