#include <iostream>
#include <fstream>
#include "json.hpp"
#include <string>



int main(int argc, char **argv){
    using namespace std;
    string file_name = argv[1];
    ifstream file(file_name);
    bool too_loong = false;
    nlohmann::json data = nlohmann::json::parse(file);
    int w = data["w"];
    int h = data["h"];
    string text = data["text"];
    char delimeter = '*';
    int text_lenght = text.length();
    int wl = ceil((w-text_lenght-2)/2.0);
    int wr = floor((w-text_lenght-2)/2.0);
    cout<<string(w, delimeter)<<endl;
    for (int i = 0; i <h-2; ++i) {
        if(i == int(h/2)-1){
            cout<<delimeter<<string(wl,' ')<<text<<string(wr,' ')<<delimeter<<endl;
        }
        else{
            cout<<delimeter<<string(w-2,' ')<<delimeter<<endl;
        }
    }

    cout<<string(w, delimeter)<<endl;
    return 0;
}