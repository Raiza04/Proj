#pragma once
#include "main.hpp"

class Ball {
public:
    Ball(float x, float y, const float r, sf::Color color)
        : xPos(x), yPos(y), radius(r), canSpawn(true) {
        ball.setRadius(radius);
        ball.setFillColor(color);
        ball.setOrigin(radius, radius);
        ball.setPosition({xPos, yPos});
        velocity = sf::Vector2f(0, 0);
    }

    bool updatePhysics(sf::CircleShape& outerball, const std::vector<std::vector<std::vector<Ball*>>>& grid) {
        // Apply gravity
        velocity.y += gravity * deltaTime;
        
        // Update position
        xPos += velocity.x * deltaTime;
        yPos += velocity.y * deltaTime;
        
        // Handle collisions
        bool shouldSpawn = handleOuterBallCollision(outerball);
        handleBallCollisions(grid);
        handleBoundaryCollisions();
        
        return shouldSpawn;
    }

    void draw(sf::RenderWindow& window) {
        ball.setPosition({xPos, yPos});
        window.draw(ball);
    }

    inline float getxPos(){ return xPos;}
    inline float getyPos(){ return yPos;}

private:
    void handleBallCollisions(const std::vector<std::vector<std::vector<Ball*>>>& grid) {
        const int cellX = static_cast<int>(xPos / CELL_SIZE);
        const int cellY = static_cast<int>(yPos / CELL_SIZE);

        // Check 3x3 neighborhood
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                const int nx = cellX + dx;
                const int ny = cellY + dy;
                
                if (nx >= 0 && nx < GRID_WIDTH && ny >= 0 && ny < GRID_HEIGHT) {
                    for (Ball* other : grid[nx][ny]) {
                        if (other != this) {
                            resolveCollision(*other);
                        }
                    }
                }
            }
        }
    }

    void resolveCollision(Ball& other) {
        const float dx = other.xPos - xPos;
        const float dy = other.yPos - yPos;
        const float distSq = dx*dx + dy*dy;
        const float minDist = radius + other.radius;
        
        // Early exit using squared distance
        if (distSq > minDist*minDist || distSq < 0.01f) return;
        
        const float dist = mySqrt(dx,dy);
        const float nx = dx / dist;
        const float ny = dy / dist;
        
        // Relative velocity
        const float rvx = other.velocity.x - velocity.x;
        const float rvy = other.velocity.y - velocity.y;
        
        // Velocity along normal
        const float velAlongNormal = rvx * nx + rvy * ny;
        
        // Only resolve if moving toward each other
        if (velAlongNormal > 0) return;
        
        // Calculate impulse
        const float impulse = (1.0f + elasticity) * velAlongNormal;
        const float massFactor = 1 / (1/radius + 1/other.radius);
        
        // Apply impulse
        velocity.x += impulse * nx * massFactor / radius;
        velocity.y += impulse * ny * massFactor / radius;
        other.velocity.x -= impulse * nx * massFactor / other.radius;
        other.velocity.y -= impulse * ny * massFactor / other.radius;
        
        // Position correction
        const float overlap = 0.5f * (minDist - dist);
        xPos -= overlap * nx;
        yPos -= overlap * ny;
        other.xPos += overlap * nx;
        other.yPos += overlap * ny;
    }

    bool handleOuterBallCollision(sf::CircleShape& outerball) {
        float dx = outerball.getPosition().x - xPos;
        float dy = outerball.getPosition().y - yPos;
        float dist = mySqrt(dx, dy);
        float outerRadius = outerball.getRadius();
        
        if (dist > outerRadius - radius) {
            float nx = dx / dist;
            float ny = dy / dist;
            
            float overlap = dist - (outerRadius - radius);
            xPos += nx * overlap;
            yPos += ny * overlap;
            
            float dot = velocity.x * nx + velocity.y * ny;
            velocity.x -= (1.0f + elasticity) * dot * nx;
            velocity.y -= (1.0f + elasticity) * dot * ny;

            if (canSpawn) {
                canSpawn = false;
                return true;
            }
        } else {
            canSpawn = true;
        }
        return false;
    }

    void handleBoundaryCollisions() {
        // Bottom
        if (yPos + radius >= WINDOW_HEIGHT) {
            yPos = WINDOW_HEIGHT - radius;
            velocity.y *= -resistance;
            velocity.x *= groundFriction;
            if (std::abs(velocity.y) < minVelocity) velocity.y = 0;
        }
        // Top
        if (yPos - radius < 0) {
            yPos = radius;
            velocity.y = std::abs(velocity.y) * resistance;
        }
        // Left
        if (xPos - radius < 0) {
            xPos = radius;
            velocity.x = std::abs(velocity.x) * resistance;
        }
        // Right
        if (xPos + radius > WINDOW_WIDTH) {
            xPos = WINDOW_WIDTH - radius;
            velocity.x = -std::abs(velocity.x) * resistance;
        }
    }

    float xPos;
    float yPos;
    const float radius;
    const float gravity = 9.81f;
    const float deltaTime = 0.2f;
    const float resistance = 0.98f; // other resistencas like air
    const float elasticity = 0.97f; // bouncing factor [0.0,1.0]
    const float groundFriction = 0.98f; // ground frinction that slows the balls if they touch ground [0.0, 1.0]
    const float minVelocity = 5.0f;
    sf::Vector2f velocity;
    sf::CircleShape ball;
    bool canSpawn;
};