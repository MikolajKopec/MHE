#include <iostream>
#include <vector>


struct puzzle_t {
        int width;
        int height;
        std::vector<int> board;
        int &get(const int x,const int y) {
            return board[y*width+x];
        }
        int get(int x,int y) const {
            return board.at(y*width+x);
        }
};
class solution_t: public puzzle_t{};

std::ostream &operator<<(std::ostream &o, const puzzle_t &puzzle){
    using namespace std;
    for (int y = 0; y<puzzle.height;y++){
        for (int x = 0; x<puzzle.width;x++) {
            auto &val =puzzle.board[y*puzzle.width+x];
            o<< "\t" <<
            ((val>0) ? std::to_string(val):"***") << "|";
        }
        o <<endl;
    }

    return o;
}

int count_inconsistant(puzzle_t puzzle){
    int cx = -1, cy = -1;
    for(int y =0; y < puzzle.width;y++){

    }
}
double evalueate(const puzzle_t & puzzle){

}

int main() {
    puzzle_t puzzle{
        4,
        4,
        {
            0,0,0,3,
             0,4,0,0,
             5,0,6,0,
             0,0,0,2
            }
    };
    puzzle_t puzzle_solution{
            4,
            4,
            {
                    0,-1,-1,3,
                    0,4,-1,0,
                    5,-1,6,-1,
                    -1,0,0,2
            }
    };
    std::cout<<puzzle;
    std::cout<<puzzle_solution;
    return 0;
}
