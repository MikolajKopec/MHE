#include <iostream>
#include <vector>
// namespace methaurystyki{
//     void wypisz() {
//         std::cout<<"wypisz" <<std::endl;
//     }
// }
// methaurystyki::wypisz();
class MojaKlasa{
    static int licznik;
public:
int id;
    MojaKlasa(){
        id = licznik++;
        std::cout << id << " created"<<std::endl;
    }
    MojaKlasa(int myID){
        id = myID;
        std::cout << id << " created ID"<<std::endl;
    }
    // MojaKlasa(MojaKlasa &&m){
    //     id = m.id;
    //     std::cout << id << " created"<<std::endl;
    // }
    ~MojaKlasa(){
        std::cout << id << " deleted "<<std::endl;
    }
};
int MojaKlasa::licznik = 0;

int main(int argc,char **argv){
    using namespace std;
    vector<MojaKlasa> tablica0b;
    MojaKlasa bla(123);
    tablica0b.push_back({});
    return 0;
}