#include "inc/ball.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gravity");

    std::vector<Ball> balls;
    bool wasRightMousePressed = false;
    sf::Color colorArr[8] = {sf::Color::Red, sf::Color::Blue, sf::Color::Black, sf::Color::White, sf::Color::Cyan
    , sf::Color::Green, sf::Color::Yellow, sf::Color::Magenta};

    std::srand(std::time(NULL));
    window.setFramerateLimit(60);
    bool wasMousePressed = false;

    while (window.isOpen()) {

        int i = rand() % 8;        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(137,137,137));

        bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (isPressed && !wasMousePressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int colorIndex = rand() % 8;
            balls.emplace_back(mousePos.x, mousePos.y, 20 + rand() % 20, colorArr[colorIndex]);
        }
        wasMousePressed = isPressed;

        for (auto& ball : balls) {
            ball.updatePhysics(balls);
            ball.draw(window);
        }

        window.display();
    }

    return 0;
}
