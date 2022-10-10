#include <iostream>
#include <vector>

struct light_up {
    int size;
    std::vector<int> board;
    std::vector<int> get_row(int x){
        auto start = board.begin();
        auto end = board.begin() + (size*x);
        std::vector<int> result(size);
        std::copy(start,end,result.begin());
        return result;
    }
//    std::vector<int> get_column(int x){
//        std::vector<int> result(size);
//        for(int i=x-1;i<size*size;i=+size){
//            result.push_back(board.at(i));
//        }
//        return result;
//    }
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
bool check_if_bulbs_are_alone(light_up puzzle){
    for(int i=0;i<puzzle.size;i++){
        bool bulbs_in_row = check_if_bulb_is_alone(puzzle.get_row(i));
//        bool bulbs_in_columns = check_if_bulb_is_alone(puzzle.get_column(i));
        if(!bulbs_in_row){
            return false;
        }
    }

}

int main() {
    using namespace std;
    // -4 = bulb
    // -3 = nieoświetlone
    // -2 = oświetlone
    //  0,1,2,3,4 = czarne z liczba
    // 5 = czarny bez liczby
    light_up puzzle {
        7,
        {
            -2,-2,-4,-2,-2,-2,-2,
            -3,-3,2,-3,-3,-3,-3,
            -3,-3,5,-3,2,2,-3,
            -3,-3,-3,5,-3,-3,-3,
            -3,0,3,-3,1,-3,-3,
            -3,-3,-3,-3,1,-3,-3,
            -3,-3,-3,-3,-3,-3,-3
        }
    };
    cout<<puzzle;
    return 0;
}
