#pragma once
#include "main.hpp"

inline void merge(sf::RenderWindow& window, std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    
    for (i = left; i <= right; i++) {
        arr[i] = temp[i - left];
        drawArr(window, i, arr);
    }
}

inline void mergesort(sf::RenderWindow& window, std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesort(window, arr, left, mid);
        mergesort(window, arr, mid + 1, right);
        merge(window, arr, left, mid, right);
    }
}