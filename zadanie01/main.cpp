#include <iostream>
#include <fstream>
#include "json.hpp"
#include <string>
#include <vector>



std::vector<std::string> split_string(std::string text,int max_lenght){
    std::cout<<"Text: "<<text<<std::endl;
    std::cout<<"max_lenght: "<<max_lenght<<std::endl;
    std::vector<std::string> result;
    int i = 0;
    std::string temp_str = "";
    for(char c : text){
        temp_str +=c;
        if(temp_str.length()==max_lenght){
            std::cout<<"string: "<<temp_str<<std::endl;
            result.push_back(temp_str);
            temp_str = "";
        }
    }
    if(temp_str.length()!=0){
        std::cout<<"string: "<<temp_str<<std::endl;
        result.push_back(temp_str);
    }
    
    return result;
}

int left_space(int width,int text_lenght){
    return ceil((width-text_lenght-2)/2.0);
}
int right_space(int width,int text_lenght){
    return floor((width-text_lenght-2)/2.0);
}
void print_border(int w, char delimeter){
    using namespace std;
    cout<<string(w, delimeter)<<endl;
}
int main(int argc, char **argv){
    using namespace std;
    string file_name = argv[1];
    ifstream file(file_name);
    bool too_loong = false;
    nlohmann::json data = nlohmann::json::parse(file);
    int w = data["w"];
    int h = data["h"];
    h=h-2;
    string text = data["text"];
    char delimeter = '*';
    bool text_to_long = text.length()>(w-2);
    vector<string> splited_strings;
    switch (text_to_long)
    {
    case 1:
        splited_strings = split_string(text,w-2);
        break;
    
    case 0:
        splited_strings.push_back(text);
        break;
    }
    if(((w-2)*h)<splited_strings.size()){
            cout<<"Wysokosc albo szerokosc okna jest za mala zeby wyswietlic napis.";
            return 0;
        }
    bool text_is_printed = false;
    print_border(w, delimeter);
    int start_print = ((h-splited_strings.size())/2);
    int end_print = splited_strings.size()+start_print;
    for (int i = 0; i<h; ++i) {
        if(i>=start_print && i<end_print){
            if(!text_is_printed){
            for(string text_to_print:splited_strings){
                int ls = left_space(w,text_to_print.length());
                int rs = right_space(w,text_to_print.length());
                cout<<delimeter;
                if(ls>=0){
                    cout<<string(ls,' ');
                }
                cout<<text_to_print;
                if(rs>=0){
                    cout<<string(rs,' ');
                }
                cout<<delimeter<<endl;
                text_is_printed = true;
            }
            }
        }else{
            cout<<delimeter<<string(w-2,' ')<<delimeter<<endl;
        }
    }
    print_border(w,delimeter);
    
    return 0;
}