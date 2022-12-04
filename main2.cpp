#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <random>
#include <fstream>
#include "json.hpp"
#include <cstdlib>


bool is_used(std::vector<light_up> used, light_up puzzle){
    for(auto x : used){
        for(int i=0;i<puzzle.board.size();i++){
            if(x.board[i] != puzzle.board[i]){
                return false;
            }
        }
        return true;
    }
}


//void find_not_used_neighbor(std::vector<light_up> used, light_up act){
//    for(int i =0;i<used.size();i++){
//        if(compare_puzzles(used[i],act)){
//            return act.find_best_neighbor()
//        }
//    }
//
//    return;
//}
std::vector<light_up> generate_neighbors_unused(std::vector<light_up> puzzle){
    std::vector<light_up> neighbors;
    int unused_neighbor_h = puzzle[0].board.size();
    for(int i =0;i<puzzle.back().board.size();i++){
        light_up helper = puzzle.back();
        if(helper.board[i] == -4 || helper.board[i] ==-2){
            if(helper.board[i]==-4){
                helper.board[i] = -2;
            }else if(helper.board[i] == -2){
                helper.board[i] = -4;
            }
            if(!is_used(puzzle,helper)){
                neighbors.push_back(helper);
            }else{
                unused_neighbor_h--;
                std::cout<<"sasiad uzyty, pozostalo:"<<unused_neighbor_h<<std::endl;
                continue;
            }
        }else{
//            std::cout<<helper.board[i]<<std::endl;
        }
//        std::cout<<"sasiedzi wybrani"<<std::endl;
    }
//    std::cout<<"----------\n";
//    for(auto x : neighbors){
//        std::cout<<x;
//    }
//    std::cout<<"----------\n";
    return neighbors;
}
light_up tabu(light_up board_to_solve,int iterations){
    std::vector<light_up> used_samples;
    std::vector<light_up> neighbors;
    light_up selected_neighbor;
    light_up first = generate_random_puzzle();
    first.change_to_light_up();
    first.evaluate_puzzle(board_to_solve);
    int actual_best = first.rating;
    used_samples.push_back(first);
    for(int i=0; i<iterations;i++){
        neighbors = generate_neighbors_unused(used_samples);
        std::cout<<"neighbors.size() == "<<neighbors.size()<<std::endl;
        if(neighbors.size()==0){
            std::cout<<"im stuck"<<std::endl;
            break;
        }
        actual_best = neighbors[0].rating;
        for(auto neighbor : neighbors){
            neighbor.change_to_light_up();
            neighbor.evaluate_puzzle(board_to_solve);
            if(neighbor.rating>=actual_best){
                selected_neighbor = neighbor;
                actual_best = selected_neighbor.rating;
                std::cout<<"rating: "<<actual_best<<std::endl;
            }
        }
//      std::cout<<used_samples.back();
        used_samples.push_back(selected_neighbor);
        if(used_samples.back().rating==0){
            break;
        }
    }
    std::cout<<used_samples.back();
    return first;
}

int main(int argc, char **argv) {
    using namespace std;
    map <string,function<light_up(light_up,int) >> my_functions;
    my_functions["full_audit"] = find_resolve_full_audit;
    my_functions["random_sample"] = find_resolve_random_sample;
    my_functions["hill_climb"] = hill_climbing;
    my_functions["r_hill_climb"] = random_hill_climbing;
    my_functions["tabu"] = tabu;
    try{
        vector<string> selected_function(argv,argv+2);
        vector<string> number_of_iterations(argv+2,argv+3);
        vector<string> file_path(argv+3,argv+4);
        ifstream file(file_path[0]);
        nlohmann::json data = nlohmann::json::parse(file);
        std::vector<int> intVector(number_of_iterations.size());
        std::transform(number_of_iterations.begin(), number_of_iterations.end(), intVector.begin(), [](const std::string& val)
        {
            return std::stod(val);
        });
        int puzzle_size = int(data["size"]);
        vector<int> puzzle_board;
        for(int x : data["puzzle"]){
            puzzle_board.push_back(x);
        }
        light_up puzzle_from_file = {puzzle_size,puzzle_board};
        auto s_function = my_functions.at(selected_function[1]);
        s_function(puzzle_from_file,intVector[0]);
        return 0;
    }
    catch(std::out_of_range aor){
        cout<<"Wrong aruguments"<<endl;
        return 0;
    }
    catch(std::logic_error le){
        cout<<"Wrong aruguments"<<endl;
        return 0;
    }

    // -4 = bulb
    // -3 = nieoświetlone
    // -2 = oświetlone
    //  0,1,2,3,4 = czarne z liczba
    // 5 = czarny bez liczby
    light_up puzzle {
            7,
            {
                    -3,-3,5,-3,-3,-3,-3,
                    -3,1,-3,-3,-3,2,-3,
                    -3,-3,-3,-3,-3,-3,5,
                    -3,-3,-3,1,-3,-3,-3,
                    2,-3,-3,-3,-3,-3,-3,
                    -3,4,-3,-3,-3,2,-3,
                    -3,-3,-3,-3,5,-3,-3
            }};
    light_up puzzle_resolve {
            7,
            {
                    -2,-4,5,-2,-2,-4,-2,
                    -2,1,-2,-4,-2,2,-4,
                    -4,-2,-2,-2,-2,-2,5,
                    -2,-2,-2,1,-4,-2,-2,
                    2,-4,-2,-2,-2,-2,-2,
                    -4,4,-4,-2,-2,2,-4,
                    -2,-4,-2,-2,5,-4,-2
            }
    };
    light_up puzzle_resolve_without_light {
            7,
            {
                    -3,-4,5,-3,-3,-4,-3,
                    -3,1,-3,-4,-3,2,-4,
                    -4,-3,-3,-3,-3,-3,5,
                    -3,-3,-3,1,-4,-3,-3,
                    2,-4,-3,-3,-3,-3,-3,
                    -4,4,-4,-3,-3,2,-4,
                    -3,-4,-3,-3,5,-4,-3
            }
    };
    light_up test = {4,{
            2,-3,-3,-3,
            -3,-3,-3,-3,
            -3,-3,-3,2,
            5,-3,-3,-3,
            -3,-3,-3,-3
    }};

    light_up resolve_test = {4,{
            -3,-4,-3,-3,
            -4,-3,-3,-3,
            -3,-3,-4,-3,
            -3,-3,-3,-4
    }};
    // change_to_light_up(resolve_test);
    // evaluate_puzzle(test,resolve_test);
    // cout<<test;

    // arr[1] = -4;
    // arr[4] = -4;
    // arr[10] = -4;
    // arr[15] = -4;
    // std::vector<int> v(arr, arr + sizeof arr / sizeof arr[0]);
    // light_up test_111 = {4,v};
    // change_to_light_up(test_111);
    // evaluate_puzzle(test,test_111);
    // cout<<test_111;

    // find_resolve_full_audit(test);
    // find_resolve_random_sample(test);
    // hill_climbing(test);
    // random_hill_climbing(test);
    // return 0;
}