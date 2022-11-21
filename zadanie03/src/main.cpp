#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <random>
#include <fstream>
#include "json.hpp"
std::random_device rd;
std::mt19937 mt_generator(rd());
bool check_if_bulb_is_alone(std::vector<int> row){
    using namespace std;
    bool is_bulb = false;
    for (int field:row) {
        if(is_bulb && field==-4){
            return false;
        }else if(is_bulb && field>=0){
            is_bulb = false;
        }
        if (field==-4){
            is_bulb = true;
        }

    }
    return true;
}

struct light_up {
    int size;
    std::vector<int> board;
    int rating = 0;
    std::vector<int> get_row(int x){
        int index = 0;
        std::vector<int> result(size);
        for(int i = (x*size);i<(x+1)*size;i++){
            result[index] = board.at(i);
            index++;
        }
        return result;
    }
    void change_field(int field_index,int value){
        board[field_index] = value;
    }
    std::vector<int> get_column(int x){
        std::vector<int> result(size);
        int index = 0;
        for(int i=x;i<=(size*size-(size-x));i=i+size){
            result[index] = board.at(i);
            index++;
        }
        return result;
    }
    bool check_if_bulbs_are_alone(){
    for(int i=0;i<size;i++){
        bool bulbs_in_row = check_if_bulb_is_alone(get_row(i));
        bool bulbs_in_columns = check_if_bulb_is_alone(get_column(i));
        if(bulbs_in_row == false ){
            rating = rating -1;
        }
        if(bulbs_in_columns == false){
            rating = rating -1;
        }
    }
    return true;
    }
    bool check_if_all_fields_are_light_up(){
        for(int field : board){
            if(field == -3){
                // std::cout<<"Pozostały niezapalone pola"<<std::endl;
                rating = rating - 1;
            }
        }
        return true;
    }
    bool check_field_neighbors(int field,int field_index){
    int board_size = size;
    int number_of_neighbors = field;
    if(field_index<board_size){
        // std::cout<<"up niedostepne"<<std::endl;
    }else{
        if(board[field_index-board_size] == -4){
            number_of_neighbors--;
        }
    }
    if(field_index + board_size>=board_size*board_size){
        // std::cout<<"down niedostepne"<<std::endl;
    }else{
        if(board[field_index+board_size] == -4){
            number_of_neighbors--;
        }
    }
    if(field_index % board_size == 0 ){
        // std::cout<<"left niedostepne"<<std::endl;
    }else{
        if(board[field_index-1] == -4){
            number_of_neighbors--;
        }
    }
    if(field_index% (board_size) == board_size-1 ){
        // std::cout<<"right niedostepne"<<std::endl;
    }else{
        if(board[field_index+1] == -4){
            number_of_neighbors--;
        }
    }
    // std::cout<<number_of_neighbors;
    if(number_of_neighbors==0 || field==5){
        return true;
    }else{
        rating = rating +  (-1 * number_of_neighbors);
        return false;
    }
}
bool check_if_bulbs_are_next_to_squares(){
    bool result;
    for(int i = 0;i<board.size();i++){
        int field = board[i];
        if(field>0){
            result = check_field_neighbors(field,i);
            // std::cout<<"Dla kwadratu o indexie: "<< i<<" o wymaganiu: "<<field <<" wynik sasiadow (true/false) = "<<result<<std::endl;
            if (!result){
                
            }
        }
    }
    return true;
    }
    void light_up_field(int iterator){
        if (board[iterator] == -3){
            change_field(iterator,-2);
        }
    }
    void light_row(int bulb_index){
    // std::cout<<"########\n"<<puzzle;
    int row = check_row(bulb_index);
    for(int i = bulb_index; i<size*(row+1);i++){
        light_up_field(i);
        if (board[i]>=0){
            break;
        }
    }
    for(int i = bulb_index;i>=size*row;i--){
        light_up_field(i);
        if (board[i]>=0){
            break;
        }
    }
    // std::cout<<"########\n"<<puzzle;
}
int check_row(int i){
    return i/size;
}
int check_column(int i){
    return i%size;
}
void light_column(int bulb_index){
    int column = check_column(bulb_index);
    int i = bulb_index;
    for(int i = bulb_index;i<(size*size) - size + column;i=i+size){
        light_up_field(i);
        if (board[i]>=0){
            break;
        }
    }
    for(int i = bulb_index;i>column;i=i-size){
        light_up_field(i);
        if (board[i]>=0){
            break;
        }
    }
}
void change_to_light_up(){
    int z = 0;
    for (auto field : board){
        if (field == -4){
            light_row(z);
            light_column(z);
        }
        z++;
    }
}

bool evaluate_puzzle(light_up &basic_board){
    rating = 0;
    for(int i = 0; i<basic_board.size * basic_board.size;i++){
        if (basic_board.board[i]>=0){
        board[i] = basic_board.board[i];
        }
    }
    check_if_bulbs_are_alone();
    check_if_bulbs_are_next_to_squares();
    check_if_all_fields_are_light_up();
    if(rating == 0){
        // std::cout<<"Puzzle poprawne"<<std::endl;
        // std::cout<<"Rating: "<<rating <<std::endl;
        return true;
    }else{
        // std::cout<<"Puzzle niepoprawne"<<std::endl;
        // std::cout<<"Rating: "<<rating <<std::endl;
        return false;
    }
}

    light_up find_best_neighbor(light_up &basic_board){
        light_up best_neighbor = {size,board};
        best_neighbor.change_to_light_up();
        int i = 0;
        for(auto field : best_neighbor.board){
            if(field == -2){
                best_neighbor.board[i] = -4;
            }else if(field == -4){
                best_neighbor.board[i] = -2;
            }
            best_neighbor.evaluate_puzzle(basic_board);
            if(best_neighbor.rating>rating){
                // std::cout<<"rating: "<<best_neighbor.rating<<std::endl;
                return best_neighbor;
            }else{
                if(best_neighbor.board[i] == -2){
                    best_neighbor.board[i] = -4;
                }else if(best_neighbor.board[i] == -4){
                    best_neighbor.board[i] = -2;
                }
            }
            i++;
        }
        return best_neighbor;
    }

};

std::ostream &operator<<(std::ostream &o, const light_up &puzzle){
    using namespace std;
    for (int y = 0; y<puzzle.size;y++){
        for (int x = 0; x<puzzle.size;x++) {
            auto &val = puzzle.board[y*puzzle.size+x];
            string display_ch;
            switch (val) {
                case -4:
                    display_ch = 'o';
                    break;
                case -3:
                    display_ch = '#';
                    break;
                case -2:
                    display_ch = '*';
                    break;
                default:
                    display_ch = to_string(val);
                    break;

            }
            o<< "\t" <<display_ch;
        }
        o <<endl;
    }

    return o;
}







light_up find_resolve_full_audit(light_up board_to_solve){
    int arr[16] = { };
    std::fill_n(arr, 16, -3);
    bool result_find = false;
    int number=0;
    for (int i=15; i>=0;i--){
        arr[i] = -4;
        std::sort(arr, arr + 3);
        do { 
            std::vector<int> v(arr, arr + sizeof arr / sizeof arr[0]);
            light_up resolve = {4,v};
            resolve.change_to_light_up();
            number = number+1;
            if(resolve.evaluate_puzzle(board_to_solve) == true){
                std::cout<<resolve<<std::endl;
                std::cout<<"Proba numer: "<<number<<std::endl;
                result_find = true;
                return resolve;
            }
            std::cout<<resolve<<std::endl;
        } while (std::next_permutation(arr, arr + 16));
    }
    
}

light_up generate_random_puzzle(){
    int arr[16] = { };
    std::vector<int> v(arr, arr + sizeof arr / sizeof arr[0]);
    light_up random_puzzle{4,v};
    std::uniform_int_distribution<int> dist(3,4);
    for(int i = 0;i<16;i++){
        random_puzzle.board[i] = -1 * dist(mt_generator);
    }
    return random_puzzle;
}

light_up hill_climbing(light_up board_to_solve){
    int arr[16] = { };
    std::fill_n(arr, 16, -2);
    std::vector<int> v(arr, arr + sizeof arr / sizeof arr[0]);
    light_up result = {4,v};
    result.change_to_light_up();
    int rating = -1;
    bool res = result.evaluate_puzzle(board_to_solve);
    if(res == true){
        return result;
    }
    do{
        result = result.find_best_neighbor(board_to_solve);
        rating = result.rating;
        std::cout<<rating<<std::endl;
    }while(rating != 0);
    std::cout<<result<<std::endl;
}

light_up random_hill_climbing(light_up board_to_solve){;
    light_up result = generate_random_puzzle(); 
    result.change_to_light_up();
    int rating = -1;
    bool res = result.evaluate_puzzle(board_to_solve);
    if(res == true){
        return result;
    }
    do{
        result = result.find_best_neighbor(board_to_solve);
        rating = result.rating;
        std::cout<<rating<<std::endl;
    }while(rating != 0);
    std::cout<<result<<std::endl;
}

light_up find_resolve_random_sample(light_up board_to_solve){
    std::vector<light_up> used_samples;
    int i = 0;
    bool res = false;
    do{
    used_samples.push_back(generate_random_puzzle());
    used_samples[i].change_to_light_up();
        res = used_samples[i].evaluate_puzzle(board_to_solve);
        std::cout<<"res rating"<<used_samples[i].rating<<std::endl;
        i=i+1;
    }while (!res);
    std::cout<<"Proba numer: "<<i<<std::endl;
    return used_samples[i-1];
}

int main(int argc, char **argv) {
    using namespace std;
    map <string,function<light_up(light_up) >> my_functions;
    my_functions["full_audit"] = find_resolve_full_audit;
    my_functions["random_sample"] = find_resolve_random_sample;
    my_functions["hill_climb"] = hill_climbing;
    my_functions["r_hill_climb"] = random_hill_climbing;
    try{
        vector<string> selected_function(argv,argv+2);
        vector<string> number_of_iterations(argv+2,argv+3);
        vector<string> file_path(argv+3,argv+4);
        ifstream file(file_path[0]);
        nlohmann::json data = nlohmann::json::parse(file);
        std::vector<double> doubleVector(number_of_iterations.size());
        std::transform(number_of_iterations.begin(), number_of_iterations.end(), doubleVector.begin(), [](const std::string& val)
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
        s_function(puzzle_from_file);
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