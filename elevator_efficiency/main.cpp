#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

size_t compute_cost(std::vector<size_t>& destinations, size_t elevator){
    size_t cost = 0;
    for(size_t i = 0; i < destinations.size(); i++){
        if(destinations[i] > elevator){
            cost += destinations[i] - elevator;
        }
        if(destinations[i] < elevator){
            cost += std::min(elevator - destinations[i], destinations[i]);
        }
    }
    return cost;
}

size_t elevator_efficiency(std::vector<size_t>& destinations, size_t height){
    if(height < 1){
        throw std::runtime_error("Number of floors cannot be less than 1");
    }
    size_t min = std::numeric_limits<double>::infinity();
    size_t ideal_elevator = 0;
    for(size_t i = 1; i < height; i++){
        size_t cost = compute_cost(destinations, i);
        if(cost < min){
            min = cost;
            ideal_elevator = i;
        }
    }
}       