#pragma once

#include "main.hpp"

void insertion(sf::RenderWindow& window, std::vector<int>& arr){
    for (size_t i = 1; i < arr.size(); i++)
    {
        int key = arr[i];
        int j = i-1;
        while(key < arr[j] && j >= 0 ){
            arr[j+1] = arr[j];
            drawArr(window, j + 1, arr); 
            j--;
        }
        arr[j+1] = key;
        drawArr(window, j + 1, arr); 
    }

    drawArr(window, arr.size()-1, arr); 
}