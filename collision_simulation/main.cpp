#include "inc/ball.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gravity");
    
    // Create spatial grid
    std::vector<std::vector<std::vector<Ball*>>> grid(
        GRID_WIDTH, 
        std::vector<std::vector<Ball*>>(GRID_HEIGHT)
    );

    float outerBallRadius = WINDOW_HEIGHT / 2 - 50;
    sf::CircleShape outerBall;
    outerBall.setRadius(outerBallRadius);
    outerBall.setPointCount(300);
    outerBall.setOrigin({outerBallRadius, outerBallRadius});
    outerBall.setPosition({WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
    outerBall.setFillColor(sf::Color::Transparent);
    outerBall.setOutlineColor(sf::Color::White);
    outerBall.setOutlineThickness(1.0f);
    
    std::vector<Ball> balls;
    sf::Color colorArr[COLOR_NUM] = {
        sf::Color::Red, sf::Color::Blue, sf::Color::White, 
        sf::Color::Cyan, sf::Color::Green, sf::Color::Yellow, 
        sf::Color::Magenta
    };
    
    std::srand(std::time(NULL));
    window.setFramerateLimit(60);
    bool wasMousePressed = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // Clear grid each frame
        for (auto& row : grid) {
            for (auto& cell : row) {
                cell.clear();
            }
        }
        
        // Populate grid with balls
        for (auto& ball : balls) {
            int x = static_cast<int>(ball.getxPos() / CELL_SIZE);
            int y = static_cast<int>(ball.getyPos() / CELL_SIZE);
            if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
                grid[x][y].push_back(&ball);
            }
        }
        
        window.clear(sf::Color::Black);
        window.draw(outerBall);
    
        // Handle mouse input
        bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (isPressed && !wasMousePressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int colorIndex = rand() % COLOR_NUM;
            balls.emplace_back(mousePos.x, mousePos.y, BALL_RADIUS, colorArr[colorIndex]);
        }
        wasMousePressed = isPressed;
        
        // Update physics and collect spawn requests
        std::vector<bool> spawnFlags;
        for (auto& ball : balls) {
            spawnFlags.push_back(ball.updatePhysics(outerBall, grid));
        }
        
        // Spawn new balls if requested and within limit
        for (size_t i = 0; i < spawnFlags.size(); ++i) {
            if (spawnFlags[i] && balls.size() < BALL_BOUND) {
                int colorIndex = rand() % COLOR_NUM;
                balls.emplace_back(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, BALL_RADIUS, colorArr[colorIndex]);
            }
        }
        
        // Draw all balls
        for (auto& ball : balls) {
            ball.draw(window);
        }

        window.display();
    }

    return 0;
}