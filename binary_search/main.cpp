#include <iostream>
#include <vector>
#include <string>

template <typename T, typename C = std::less<T>>
int binary_search(const std::vector<T>& vals, const T& val, C compare = C()){
    int start = 0;
    int end = vals.size()-1;
    int index;
    while(start <= end){
        index = (start + end)/2;
        if(compare(vals[index], val)){
            start = index + 1;
        }else if (compare(val, vals[index])){
            end = index - 1;
        }else{
            return index;
        }
    }
    return -1;
}

int main(){
    std::vector<float> vals = {2.0f, 6.0f, 7.0f, 9.0f};
    float val = 2.0f;
    std::cout << binary_search<float>(vals, val) << std::endl;
    val = 6.0f;
    std::cout << binary_search<float>(vals, val) << std::endl;
    val = 7.0f;
    std::cout << binary_search<float>(vals, val) << std::endl;
    val = 9.0f;
    std::cout << binary_search<float>(vals, val) << std::endl;

    std::vector<std::string> words = {"about pi", "h", "program", "turtle", "zebra"};  
    std::string word = "turtle";
    std::cout << binary_search<std::string>(words, word) << std::endl;
    word = "turtles";
    std::cout << binary_search<std::string>(words, word) << std::endl;
    word = "h";
    std::cout << binary_search<std::string>(words, word) << std::endl;
    word = "about pi";
    std::cout << binary_search<std::string>(words, word) << std::endl;

    return 0;
}