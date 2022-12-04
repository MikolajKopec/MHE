

#ifndef MHE1_FULL_ADUIT_H
#define MHE1_FULL_AUDIT_H
light_up find_resolve_full_audit(light_up board_to_solve,int iterations){
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
            number = number+1;
            if(resolve.evaluate_puzzle(board_to_solve) == 0){
                std::cout<<resolve<<std::endl;
                std::cout<<"Proba numer: "<<number<<std::endl;
                result_find = true;
                return resolve;
            }
//            std::cout<<resolve<<std::endl;
        } while (std::next_permutation(arr.begin(), arr.end()));
    }
    return board_to_solve;
}
#endif