#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

template <typename T, typename C = std::less<T>>
int partition(std::vector<T>& vals, int start, int end, C compare = C()){
    int left = start - 1;

    for(int i = start; i < end; i++){
        if(compare(vals[i], vals[end])){
            left++;
            if(left != i){
                std::swap(vals[i], vals[left]);
            }
        }
    }
    std::swap(vals[left + 1], vals[end]);
    return left + 1;
}

template <typename T, typename C = std::less<T>>
void quicksort(std::vector<T>& vals, int start, int end){
    if(start < end){
        int partition_index = partition(vals, start, end);

    quicksort(vals, start, partition_index - 1);
    quicksort(vals, partition_index + 1, end);
    }
}

int main(){
    std::vector<int> test = {7, 2, 1, 8, 6, 3, 5, 4};
    partition(test, 0, 7);
    for(int i = 0; i < test.size(); i++){
        std::cout << test[i] << " ";
    }
    std::cout << '\n';
    quicksort(test, 0 , 7);
    for(int i = 0; i < test.size(); i++){
        std::cout << test[i] << " ";
    }  
    std::cout << '\n';

    std::vector<int> test2 = {1, 2, 4, 3, 0, 5, 3};
    partition(test2, 0, 6);
    for(int i = 0; i < test2.size(); i++){
        std::cout << test2[i] << " ";
    }
    std::cout << '\n';
    quicksort(test2, 0 , 6);
    for(int i = 0; i < test2.size(); i++){
        std::cout << test2[i] << " ";
    }
    std::cout << '\n';

    return 0;
}