#pragma once
#include "main.hpp"

class BubbleSortState {
public:
    BubbleSortState() : i(0), j(0) {}
    void step(std::vector<int>& arr, sf::RenderWindow& window) {
        if (i >= arr.size()) return;
        
        if (j < arr.size() - i - 1) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
            drawArr(window, j + 1, arr);
            j++;
        } else {
            j = 0;
            i++;
        }
    }
private:
    size_t i, j;
};