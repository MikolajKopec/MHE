#include <iostream>
#include <fstream>
#include "json.hpp"



int main(){
    std::ifstream file("window_settings.json");
    nlohmann::json data = nlohmann::json::parse(file);
    
    for(auto i:data){
        std::cout<<i<<std::endl;
    }

    return 0;
}