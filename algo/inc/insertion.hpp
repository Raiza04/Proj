#pragma once
#include "main.hpp"

inline void insertion(sf::RenderWindow& window, std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            drawArr(window, j + 1, arr);
            j--;
        }
        arr[j + 1] = key;
        drawArr(window, i, arr);
    }
}