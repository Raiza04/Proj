#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP

#include "main.hpp"

struct BubbleSortState {
    int i = 0;
    int j = 0;
    bool sorted = false;

    void step(std::vector<int>& arr, sf::RenderWindow& window) {
        if (sorted) return;

        if (i < arr.size() - 1) {
            if (j < arr.size() - i - 1) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                }
                drawArr(window, j, arr);
                ++j;
            } else {
                j = 0;
                ++i;
            }
        } else {
            sorted = true;
        }
    }
};


#endif