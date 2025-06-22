#include "inc/main.hpp"
#include "inc/bubblesort.hpp"
#include "inc/quicksort.hpp"
#include "inc/mergesort.hpp"


int main() {

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<int> values(BAR_NUM);
    for (int& v : values) {
        v = std::rand() % WINDOW_HEIGHT;
    }

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sort Visualizer");

    BubbleSortState sort;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!sorted(values)) {
            //quicksort(window, values, 0, values.size() - 1);
            //mergesort(window, values, 0, values.size() - 1);
            //sort.step(values, window); //Bubblesort
        }
}



}
