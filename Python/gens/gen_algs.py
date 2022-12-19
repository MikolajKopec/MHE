import random
from light_up.puzzle import Puzzle

def create_chromosome(size):
    result = []
    for _ in range(size):
        x = random.randint(0,1)
        result.append(x)
    return result

def decode_chromosome(chromosome):
    return [-4 if each==1 else -3 for each in chromosome] 

def fitness(board_to_solve,population):
    fitness_result = []
    for chromosome in population:
        phenotype = decode_chromosome(chromosome)
        puzzle = Puzzle(board_to_solve.size,phenotype)
        puzzle.evaluate(board_to_solve)
        fitness_result.append(1/(puzzle.rating+1))
    return fitness_result

def one_point_crossover(chromosome1,chromosome2):
    cross_point = random.randint(0,len(chromosome1)-1)
    for i in range(cross_point,len(chromosome1)):
        chromosome1[i],chromosome2[i] = chromosome2[i],chromosome1[i]
    return [chromosome1,chromosome2]

def prob_mutation(chromosome,probability):
    probability = probability * 100
    for i in range(len(chromosome)):
        value = random.randint(0,100)
        # print(value)
        # print(probability)
        if value<probability:
            chromosome[i] = 0 if chromosome[i] == 1 else 1
    return chromosome

def roulette(res_for_pop):
    roulette_wheel = 0
    # print(f"populacja {res_for_pop}")
    for each in res_for_pop:
        roulette_wheel = roulette_wheel + each
    # print(f"wheel: {roulette_wheel}")
    point = random.uniform(0,roulette_wheel)
    # print(f"Wybrany punkt na kole: {point}")
    h = 0
    for i in range(len(res_for_pop)):
        h = h + res_for_pop[i]
        if(h>point):
            # print(f"selected index {i}")
            return i
        
def genetic_alg(board_to_solve,iterations,mutation_prob):
    best_score = [0]
    preavious_pop = []
    for _ in range(1000):
        preavious_pop.append(create_chromosome(board_to_solve.size*board_to_solve.size))
    # print(preavious_pop)
    # x = Puzzle(board_to_solve.size,decode_chromosome(preavious_pop[0]))
    # y = Puzzle(board_to_solve.size,decode_chromosome(preavious_pop[1]))
    # x.evaluate(board_to_solve)
    # y.evaluate(board_to_solve)
    # print(x)
    # print(y)
    # print(f"x = {x.rating} y = {y.rating}")
    act_fitnes = fitness(board_to_solve,preavious_pop)
    # print(act_fitnes)
    for i in range(iterations):
        new_pop = []
        for _ in range(len(preavious_pop)):
            new_pop.append(preavious_pop[roulette(act_fitnes)])

        # print(new_pop)
        for x in range(1,len(new_pop),2):
            pop_of_two =  one_point_crossover(new_pop[i],new_pop[i-1])
            new_pop[i] = prob_mutation(pop_of_two[0],mutation_prob)
            new_pop[i-1] = prob_mutation(pop_of_two[1],mutation_prob)
        # print(new_pop)
        act_fitnes = fitness(board_to_solve,new_pop)
        preavious_pop = new_pop
        
        for i,each in enumerate(act_fitnes):
            if each>best_score[-1]:
                best_score.append(each)
                best_chromosome = preavious_pop[i]
    print(best_score)
    x = Puzzle(board_to_solve.size,decode_chromosome(preavious_pop[i]))
    x.evaluate(board_to_solve)
    print(x)
    print(x.rating)