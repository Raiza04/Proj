#pragma once

#include "main.hpp"


int partition(sf::RenderWindow& window, std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
            drawArr(window, j, arr);
            sf::sleep(sf::milliseconds(SLEEP));
        }
    }
    std::swap(arr[i + 1], arr[high]);
    drawArr(window, i, arr);
    sf::sleep(sf::milliseconds(SLEEP));
    return (i + 1);
}

void quicksort(sf::RenderWindow& window, std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(window, arr, low, high);
        quicksort(window, arr, low, pi - 1);
        quicksort(window, arr, pi + 1, high);
    }
}