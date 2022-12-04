#include "light_up_puzzle.h"



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
    return 0;
}