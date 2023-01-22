
#include <fstream>
#include "json.hpp"
#include <numeric>
#include "./algs/full_audit.h"
#include "./algs/random_sampling.h"
#include "./algs/hill_climbing.h"
#include "./algs/random_hill_climbing.h"
#include "./algs/tabu.h"
#include "./algs/simulated_annealing.h"
#include "./genetic/genetic.h"
#include <omp.h>

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
        bool omp = check_arg(argv[10]);
        ifstream file(file_path);
        nlohmann::json data = nlohmann::json::parse(file);
//
        int puzzle_size = int(data["size"]);
        vector<int> puzzle_board;
        for (int x: data["puzzle"]) {
            puzzle_board.push_back(x);
        }
        light_up puzzle_from_file = {puzzle_size, puzzle_board};

        if(selected_function == "all"){
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
        }
        else if(omp== true && selected_function=="gen"){
            std::chrono::time_point<std::chrono::system_clock> start, end,start2, end2;
            vector<double> timer_normal,timer_omp,fitness_normal,fitness_omp;
            double x1,x2;
            for(int i=0;i<10;i++){
                start = std::chrono::system_clock::now();
                std::map<std::string,std::any> resolve;
                resolve = genetic_alg(puzzle_from_file,number_of_iterations,0.4);
                end = std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds = end - start;
                x1 = std::any_cast<double>(resolve["best_score"]);
                fitness_normal.push_back(x1);
                timer_normal.push_back(elapsed_seconds.count());
                start2 = std::chrono::system_clock::now();
                std::map<std::string,std::any> resolve2;
                resolve2 = genetic_alg_omp(puzzle_from_file,number_of_iterations,0.4);
                end2 = std::chrono::system_clock::now();
                x2 = std::any_cast<double>(resolve2["best_score"]);
                fitness_omp.push_back(x2);
                std::chrono::duration<double> elapsed_seconds2 = end2 - start2;
                timer_omp.push_back(elapsed_seconds2.count());
            }
            double avg_time_normal = 0,avg_time_omp = 0,avg_rating_normal = 0,avg_rating_omp = 0;
            for(int i = 0;i<10;i++){
                avg_time_normal += timer_normal[i];
                avg_time_omp += timer_omp[i];
                avg_rating_normal += fitness_normal[i];
                avg_rating_omp += fitness_omp[i];
            }
            avg_time_normal = avg_time_normal/10;
            avg_time_omp = avg_time_omp/10;
            avg_rating_normal = avg_rating_normal/10;
            avg_rating_omp = avg_rating_omp/10;
            cout<<"Time: normal "<<avg_time_normal<<endl;
            cout<<"Time: omp "<<avg_time_omp<<endl;
            cout<<"Rating: normal "<<avg_rating_normal<<endl;
            cout<<"Rating: omp "<<avg_rating_omp<<endl;
        }
        else if(selected_function == "island_omp"){
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();
            island_omp(puzzle_from_file,number_of_iterations,0.4,3,10);
            end = std::chrono::system_clock::now();
        }
        else{
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();
            std::map<std::string,std::any> resolve;
            if(selected_function == "gen"){
                resolve = genetic_alg(puzzle_from_file,number_of_iterations,0.4);
            }else{
                auto s_function = my_functions.at(selected_function);
                resolve = s_function(puzzle_from_file,number_of_iterations);
            }
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start;
            int resolve_rating = 0;
            if(show_resolve){
                if(selected_function=="gen"){
                    phenotype_t x = std::any_cast<chromosome_t>(resolve["puzzle"]);
                    for(int i =0;i<x.size();i++){
                        if(x[i]==1){
                            x[i] = -4;
                        }else{
                            x[i] = -3;
                        }
                    }
                    light_up result = {puzzle_from_file.size,x};
                    result.evaluate_puzzle(puzzle_from_file);
//                result.light_up_where_is_bulb();
                    cout<<result;
                    resolve_rating = result.rating;
                }
                else{
                    cout<<std::any_cast<light_up>(resolve["puzzle"]);
                }
            }
            if(show_time){
                cout<<"Czas dzialania: "<<elapsed_seconds.count()<<"s"<<endl;
            }
            if(show_evaluate_count){
                cout<<"Evaluate count: "<<std::any_cast<int>(evaluate_number)<<endl;
            }
            if(show_resolve_rating){
                if(selected_function == "gen"){
                    cout<<"resolve rating: "<<resolve_rating<< std::endl;
                }else{
                    cout<<"resolve rating: "<<std::any_cast<light_up>(resolve["puzzle"]).rating<<endl;
                }
            }
            if(show_iterations_count){
                cout<<"Iterations count: "<<std::any_cast<int>(resolve["iterations"])<<endl;
            }
            if(show_curve == 'y'){
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