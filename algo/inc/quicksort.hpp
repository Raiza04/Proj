#pragma once
#include "main.hpp"

inline void quicksort(sf::RenderWindow& window, std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                std::swap(arr[i], arr[j]);
                drawArr(window, j, arr);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        drawArr(window, i + 1, arr);
        
        int pi = i + 1;
        quicksort(window, arr, low, pi - 1);
        quicksort(window, arr, pi + 1, high);
    }
}