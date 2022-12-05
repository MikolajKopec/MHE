//
// Created by mikol on 05.12.2022.
//

#include "puzzle.h"
int evaluate_number = 0;

int light_up::get_row_index_by_element_index(int i){
    return i/size;
}
int light_up::get_column_index_by_element_index(int i){
    return i%size;
}
std::vector<int> light_up::get_row(int x){
    int index = 0;
    std::vector<int> result(size);
    for(int i = (x*size);i<(x+1)*size;i++){
        result[index] = board.at(i);
        index++;
    }
    return result;
}
std::vector<int> light_up::get_column(int x){
    std::vector<int> result(size);
    int index = 0;
    for(int i=x;i<=(size*size-(size-x));i=i+size){
        result[index] = board.at(i);
        index++;
    }
    return result;
}
int light_up::check_if_bulb_is_alone(std::vector<int> row){
    using namespace std;
    int bulbs_rating = 0;
    bool bulb_is_in_row = false;
    for (int field:row) {
        if(bulb_is_in_row && field==-4){
            bulbs_rating++;
        }else if(bulb_is_in_row && field>=0){
            bulb_is_in_row = false;
        }
        if (field==-4){
            bulb_is_in_row = true;
        }
    }
    return bulbs_rating;
}
int light_up::check_if_bulbs_are_alone(){
    int result = 0;
    for(int i=0;i<size;i++){
        result += check_if_bulb_is_alone(get_row(i));
        result += check_if_bulb_is_alone(get_column(i));
    }
    return result;
}
void light_up::light_up_field(int iterator){
    if (board[iterator] == -3){
        board[iterator] = -2;
    }
}

void light_up::light_column(int bulb_index){
    int column = get_column_index_by_element_index(bulb_index);
    for(int i = bulb_index;i<board.size();i=i+size){
        light_up_field(i);
        if (board[i]>=0){
            break;
        }
    }
    for(int i = bulb_index;i>=column;i=i-size){
        light_up_field(i);
        if (board[i]>=0){
            break;
        }
    }
}
void light_up::light_row(int bulb_index){
    // std::cout<<"########\n"<<puzzle;
    int row = get_row_index_by_element_index(bulb_index);
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
void light_up::light_up_where_is_bulb(){
    int z = 0;
    for (auto field : board){
        if (field == -4){
            light_row(z);
            light_column(z);
        }
        z++;
    }
}
int light_up::check_if_all_fields_are_light_up(){
    int result = 0;
    for(int field : board){
        if(field == -3){
            result++;
        }
    }
    return result;
}
int light_up::check_field_neighbors(int field_index){
    int field = board[field_index];
    int board_size = size;
    int number_of_neighbors = field;
    if(field_index<board_size){
//                 std::cout<<"up niedostepne"<<std::endl;
    }else{
        if(board[field_index-board_size] == -4){
            number_of_neighbors--;
        }
    }
    if(field_index + board_size>=board_size*board_size){
//                 std::cout<<"down niedostepne"<<std::endl;
    }else{
        if(board[field_index+board_size] == -4){
            number_of_neighbors--;
        }
    }
    if(field_index % board_size == 0 ){
//                 std::cout<<"left niedostepne"<<std::endl;
    }else{
        if(board[field_index-1] == -4){
            number_of_neighbors--;
        }
    }
    if(field_index% (board_size) == board_size-1 ){
//                 std::cout<<"right niedostepne"<<std::endl;
    }else{
        if(board[field_index+1] == -4){
            number_of_neighbors--;
        }
    }
//        std::cout<<number_of_neighbors<<std::endl;
//        std::cout<<"----------\n";
//        std::cout<<field_index<<"\n";
//        std::cout<<number_of_neighbors<<"\n";
//        std::cout<<rating<<"\n";
//        std::cout<<"----------\n";
    if(number_of_neighbors==0 || field==5){
        return 0;
    }else{
        return abs(number_of_neighbors);
    }
}
int light_up::check_if_bulbs_are_next_to_squares(){
    int result = 0;
    for(int i = 0;i<board.size();i++){
        if(board[i]>=0){
            result = result + check_field_neighbors(i);
//                 std::cout<<"Dla kwadratu o indexie: "<< i<<" o wymaganiu: "<<board[i] <<" wynik sasiadow (true/false) = "<<result<<std::endl;
        }
    }
    return result;
}
int light_up::evaluate_puzzle(light_up &board_to_solve){
    evaluate_number++;
    int result = 0;
    for(int i = 0; i<board_to_solve.size * board_to_solve.size;i++){
        if (board_to_solve.board[i]>=0){
            board[i] = board_to_solve.board[i];
        }
    }
    light_up_where_is_bulb();
    result += check_if_bulbs_are_alone();
//        std::cout<<"rating after bulbs_alone"<<result<<std::endl;
    result += check_if_bulbs_are_next_to_squares();
//        std::cout<<"rating after check_if_bulbs_are_next_to_squares"<<result<<std::endl;
    result += check_if_all_fields_are_light_up();
//        std::cout<<"rating after check_if_all_fields_are_light_up"<<result<<std::endl;
    rating = result;
    return rating;
}

light_up light_up::find_best_neighbor(light_up &basic_board){
    light_up best_neighbor = {size,board};
    light_up current_neighbor = best_neighbor;
    int i = 0;
    for(auto field : current_neighbor.board){
        if(field == -2 || field == -3){
            current_neighbor.board[i] = -4;
        }else if(field == -4){
            current_neighbor.board[i] = -3;
        }
        best_neighbor.evaluate_puzzle(basic_board);
        current_neighbor.evaluate_puzzle(basic_board);
        if(best_neighbor.rating>=current_neighbor.rating){
            // std::cout<<"rating: "<<best_neighbor.rating<<std::endl;
            best_neighbor = current_neighbor;
        }else{
            if(current_neighbor.board[i] == -2 || field == -3){
                current_neighbor.board[i] = -4;
            }else if(current_neighbor.board[i] == -4){
                current_neighbor.board[i] = -3;
            }
        }
        i++;
    }
    return best_neighbor;
}
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