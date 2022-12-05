//
// Created by mikol on 05.12.2022.
//

#include <map>
#include <string>
#include <any>
#include <algorithm>
#include "full_audit.h"
#include "../puzzle/puzzle.h"

std::map<std::string,std::any> find_resolve_full_audit(light_up board_to_solve,int iterations){
    std::map<std::string,std::any> result;
    std::vector<int> rating;
    int board_size =board_to_solve.size*board_to_solve.size;
    std::vector<int> arr (board_size);
    std::fill_n(arr.begin(),board_size,-3);
    bool result_find = false;
    int number=0;
    for (int i=board_size-1; i>=0;i--){
        arr[i] = -4;
        std::sort(arr.begin(), arr.end());
        do {
            light_up resolve = {board_to_solve.size,arr};
            resolve.light_up_where_is_bulb();
            number++;
            resolve.evaluate_puzzle(board_to_solve);
            rating.push_back(resolve.rating);
            if( resolve.rating== 0){
//                std::cout<<resolve<<std::endl;
//                std::cout<<"Proba numer: "<<number<<std::endl;
                result_find = true;
                result["puzzle"] = resolve;
                result["iterations"] = number;
                result["rating"] = rating;
                return result;
            }
//            std::cout<<resolve<<std::endl;
        } while (std::next_permutation(arr.begin(), arr.end()));
    }
    result["puzzle"] = board_to_solve;
    result["iterations"] = number;
    result["rating"] = rating;
    return result;
}