#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

// Konstanten
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

// Externe Variablen (Definition in main.cpp)
extern int BAR_NUM;
extern float BAR_WIDTH;
extern int SLEEP_MS;

//vibe coded
struct Config {
    std::string algorithm = "bubble";
    int bar_num = 300;
    int sleep_ms = 10;
};

//vibe coded
Config parseArguments(int argc, char* argv[]);
void drawArr(sf::RenderWindow& window, int index, std::vector<int>& arr);
bool sorted(std::vector<int>& arr);

inline void drawArr(sf::RenderWindow& window, int index, std::vector<int>& arr) {
    window.clear(sf::Color::Black);
    
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) window.close();
    }

    for (int i = 0; i < arr.size(); ++i) {
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(BAR_WIDTH, arr[i]));
        rect.setPosition(i * BAR_WIDTH, WINDOW_HEIGHT - arr[i]);
        rect.setFillColor(i == index ? sf::Color::Red : sf::Color::White);
        window.draw(rect);
    }

    window.display();
    sf::sleep(sf::milliseconds(SLEEP_MS));
}

inline bool sorted(std::vector<int>& arr) {
    for (size_t i = 0; i + 1 < arr.size(); ++i) {
        if (arr[i] > arr[i + 1]) return false;
    }
    return true;
}