
#include <fstream>
#include "json.hpp"
#include "./algs/full_audit.h"
#include "./algs/random_sampling.h"
#include "./algs/hill_climbing.h"
#include "./algs/random_hill_climbing.h"
#include "./algs/tabu.h"
#include "./algs/simulated_annealing.h"

extern int evaluate_number;

bool check_arg(std::string x){
    if(x=="y"){
        return true;
    }
    return false;
}

int main(int argc, char **argv) {
    using namespace std;
    map <string,function<std::map<std::string,std::any>(light_up,int) >> my_functions;
    my_functions["full_audit"] = find_resolve_full_audit;
    my_functions["random_sample"] = find_resolve_random_sample;
    my_functions["hill_climb"] = hill_climbing;
    my_functions["r_hill_climb"] = random_hill_climbing;
    my_functions["tabu"] = tabu;
    my_functions["simulated_annealing"] = simulated_annealing;
    try {
        string selected_function = argv[1];
        int number_of_iterations = atoi(argv[2]);
        string file_path = argv[3];
        bool show_time = check_arg(argv[4]);
        bool show_curve = check_arg(argv[5]);
        bool show_resolve = check_arg(argv[6]);
        bool show_resolve_rating = check_arg(argv[7]);
        bool show_iterations_count = check_arg(argv[8]);
        bool show_evaluate_count = check_arg(argv[9]);
        ifstream file(file_path);
        nlohmann::json data = nlohmann::json::parse(file);
//
        int puzzle_size = int(data["size"]);
        vector<int> puzzle_board;
        for (int x: data["puzzle"]) {
            puzzle_board.push_back(x);
        }
        light_up puzzle_from_file = {puzzle_size, puzzle_board};
//        cout << "puzzle" << puzzle_from_file;
//        puzzle_from_file.board[4]= -4;
//        puzzle_from_file.board[6]= -4;
//        puzzle_from_file.board[21]= -4;
//        puzzle_from_file.evaluate_puzzle(puzzle_from_file);
//        cout << "puzzle" << puzzle_from_file;
        bool all = false;
//    }
        if(selected_function == "all"){
            all = true;
        }
        if(all){
            for(auto x_function :my_functions){
                std::chrono::time_point<std::chrono::system_clock> start, end;
                start = std::chrono::system_clock::now();
                cout<<"Algorytm: "<<x_function.first<<endl;
                auto s_function = my_functions.at(x_function.first);
                std::map<std::string,std::any> resolve = s_function(puzzle_from_file,number_of_iterations);
                end = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;
                if(show_resolve){
                    cout<<std::any_cast<light_up>(resolve["puzzle"]);
                }
                if(show_time){
                    cout<<"Czas dzialania: "<<elapsed_seconds.count()<<"s"<<endl;
                }
                if(show_evaluate_count){
                    cout<<"Evaluate count: "<<std::any_cast<int>(evaluate_number)<<endl;
                }
                if(show_resolve_rating){
                    cout<<"resolve rating: "<<std::any_cast<light_up>(resolve["puzzle"]).rating<<endl;
                }
                if(show_iterations_count){
                    cout<<"Iterations count: "<<std::any_cast<int>(resolve["iterations"])<<endl;
                }
//                if(show_curve == 'y'){
//                    for(auto x : std::any_cast<std::vector<int>>(resolve["rating"])){
//                        cout<<x<<" ";
//                    }
//                    cout<<"\n";
//                    cout<<"Iterations count: "<<std::any_cast<int>(resolve["iterations"])<<endl;
//                }
            }
        }else{

        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        auto s_function = my_functions.at(selected_function);
        std::map<std::string,std::any> resolve = s_function(puzzle_from_file,number_of_iterations);
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        if(show_resolve){
            cout<<std::any_cast<light_up>(resolve["puzzle"]);
        }
        if(show_time){
            cout<<"Czas dzialania: "<<elapsed_seconds.count()<<"s"<<endl;
        }
        if(show_evaluate_count){
            cout<<"Evaluate count: "<<std::any_cast<int>(evaluate_number)<<endl;
        }
        if(show_resolve_rating){
            cout<<"resolve rating: "<<std::any_cast<light_up>(resolve["puzzle"]).rating<<endl;
        }
        if(show_iterations_count){
            cout<<"Iterations count: "<<std::any_cast<int>(resolve["iterations"])<<endl;
        }
        if(show_curve){
            for(auto x : std::any_cast<std::vector<int>>(resolve["rating"])){
                cout<<x<<" ";
            }
            cout<<"\n";
            cout<<"Iterations count: "<<std::any_cast<int>(resolve["iterations"])<<endl;
        }
        return 0;
        }
    }
    catch(std::out_of_range aor){
        cout<<"Wrong aruguments"<<endl;
        return 0;
    }
    catch(std::logic_error le){
        cout<<"Wrong aruguments"<<endl;
        return 0;
    }
    return 0;
}