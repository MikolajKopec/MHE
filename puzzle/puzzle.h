#include <vector>
#include <iostream>

#ifndef MHE1_PUZZLE_H
#define MHE1_PUZZLE_H
struct light_up {
    int size = 0;
    std::vector<int> board;
    int rating = 0;

    int get_row_index_by_element_index(int i);

    int get_column_index_by_element_index(int i);
    std::vector<int> get_row(int x);
    std::vector<int> get_column(int x);
    int check_if_bulb_is_alone(std::vector<int> row);
    int check_if_bulbs_are_alone();
    void light_up_field(int iterator);

    void light_column(int bulb_index);
    void light_row(int bulb_index);
    void light_up_where_is_bulb();
    int check_if_all_fields_are_light_up();
    int check_field_neighbors(int field_index);
    int check_if_bulbs_are_next_to_squares();
    int evaluate_puzzle(light_up &board_to_solve);

    light_up find_best_neighbor(light_up &basic_board);
};
std::ostream &operator<<(std::ostream &o, const light_up &puzzle);
#endif