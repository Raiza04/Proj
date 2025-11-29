#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>

#define BAR_NUM 500.0 // adjust the number of bars to sort
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BAR_WIDTH WINDOW_WIDTH / BAR_NUM
#define SLEEP 10 //adjust the speed to visulize

void drawArr(sf::RenderWindow& window, int index, std::vector<int>& arr){
    window.clear(sf::Color::Black);

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    for (int i = 0; i < arr.size(); ++i)
    {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(BAR_WIDTH, arr[i]));
        rect.setPosition(i * BAR_WIDTH, WINDOW_HEIGHT - arr[i]);
        if (i == index)
        {
            rect.setFillColor(sf::Color::Red);
        } else {
            rect.setFillColor(sf::Color::White);
        }
        
        window.draw(rect);
    }

    window.display();
    sf::sleep(sf::milliseconds(SLEEP));
}

bool sorted(std::vector<int>& arr){
    for (size_t i = 0; i < arr.size() - 2; i++)
    {
        if(arr[i] > arr[i + 1]){
            return false;
        }
    }
    return true;
}
