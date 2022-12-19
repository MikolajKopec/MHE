from light_up.puzzle import Puzzle
from gens import genetic_alg,one_point_crossover

board_to_solve = Puzzle(6,[
                          2,-3,-3,-3,-3,-3,
                         -3,-3,-3,-3,-3,-3,
                         -3,-3,-3,-3,-3,-3,
                         -3,-3,-3,5,-3,-3,
                         -3,-3,-3,-3,-3,-3,
                         -3,-3,-3,-3,-3,-3
                         ])
puzzle = Puzzle(6,[
                          2,-4,-3,-3,-3,-3,
                         -4,-3,-3,-3,-3,-3,
                         -3,-3,-4,-3,-3,-3,
                         -3,-3,-3,-4,-3,-3,
                         -3,-3,-3,-3,-4,-3,
                         -3,-3,-3,-3,-3,-4
                         ])

genetic_alg(board_to_solve,10,0.4)
# one_point_crossover([0,0,0,0,0,0],[1,1,1,1,1,1])


# print(1/31)