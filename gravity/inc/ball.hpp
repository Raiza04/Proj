#pragma once

#include "main.hpp"

class Ball {
public:
    Ball(float x, float y, const float r, sf::Color color)
        : xPos(x), yPos(y), radius(r) {
        ball.setRadius(radius);
        ball.setFillColor(color);
        ball.setOrigin(radius, radius);
        ball.setPosition({xPos, yPos});
        velocity = sf::Vector2f(0, 0);
    }

    void updatePhysics(std::vector<Ball>& balls) {
        velocity.y += gravity * deltaTime;
        
        xPos += velocity.x * deltaTime;
        yPos += velocity.y * deltaTime;
        
        handleBoundaryCollisions();
        
        for (auto& other : balls) {
            if (&other == this) continue;
            handleBallCollision(other);
        }
    }

    void draw(sf::RenderWindow& window) {
        ball.setPosition({xPos, yPos});
        window.draw(ball);
    }

    void applyImpulse(float dx, float dy) {
        velocity.x += dx;
        velocity.y += dy;
    }

private:
    void handleBoundaryCollisions() {
        if (yPos + radius >= WINDOW_HEIGHT) {
            yPos = WINDOW_HEIGHT - radius;
            velocity.y *= -resistance;
            velocity.x *= groundFriction;
            if (std::abs(velocity.y) < minVelocity) velocity.y = 0;
        }

        if (yPos - radius < 0) {
            yPos = radius;
            velocity.y = std::abs(velocity.y) * resistance;
        }

        if (xPos - radius < 0) {
            xPos = radius;
            velocity.x = std::abs(velocity.x) * resistance;
        }

        if (xPos + radius > WINDOW_WIDTH) {
            xPos = WINDOW_WIDTH - radius;
            velocity.x = -std::abs(velocity.x) * resistance;
        }
    }

    void handleBallCollision(Ball& other) {
        float dx = other.xPos - xPos;
        float dy = other.yPos - yPos;
        float dist = mySqrt(dx, dy);

        // Check if balls are colliding
        if (dist < 2*radius && dist > 0.1f) {
            // Calculate collision normal
            float nx = dx / dist;
            float ny = dy / dist;
            
            // Relative velocity
            float rvx = other.velocity.x - velocity.x;
            float rvy = other.velocity.y - velocity.y;
            
            // Velocity along the normal
            float velocityAlongNormal = rvx * nx + rvy * ny;
            
            // Only resolve if balls are moving toward each other
            if (velocityAlongNormal > 0) return;
            
            // Calculate impulse (elastic collision with equal mass)
            float impulse = (1.0f + elasticity) * velocityAlongNormal;
            impulse /= (1/radius + 1/other.radius); // Mass factor
            
            // Apply impulse
            velocity.x += impulse * nx * (1/radius);
            velocity.y += impulse * ny * (1/radius);
            other.velocity.x -= impulse * nx * (1/other.radius);
            other.velocity.y -= impulse * ny * (1/other.radius);
            
            // Position correction to prevent sticking
            float overlap = 0.5f * (2*radius - dist);
            xPos -= overlap * nx;
            yPos -= overlap * ny;
            other.xPos += overlap * nx;
            other.yPos += overlap * ny;
        }
    }

    float xPos;
    float yPos;
    const float radius;
    const float gravity = 9.81f;
    const float deltaTime = 0.2f;
    const float resistance = 0.95f;
    const float elasticity = 1.0f;
    const float groundFriction = 0.7f;
    const float minVelocity = 5.0f;
    sf::Vector2f velocity;
    sf::CircleShape ball;
};
