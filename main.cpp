#include <SFML/Graphics.hpp>
#include <iostream>


class GameObj {
public:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::RectangleShape rect;

    GameObj(float width, float height, sf::Vector2f position, sf::Color color) {
        this->size = {width, height};
        this->position = position;

        this->rect.setSize(this->size);
        this->rect.setPosition(this->position);
        this->rect.setFillColor(color);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(this->rect);
    }

    bool collide(const GameObj& obj) const {
        return  obj.position.x + obj.size.x >= this->position.x &&
                obj.position.x <= this->position.x + this->size.x &&
                obj.position.y + obj.size.y >= this->position.y &&
                obj.position.y <= this->position.y + this->size.y;
    }
};


class Player : public GameObj {
public:
    float speed = 300.f;
    float friction = 0.99f;

    Player(sf::Vector2f position)
        : GameObj(50, 50, position, sf::Color::Blue)
    {

    }


    void move_up(float deltaTime) {
        this->position.y -= speed * deltaTime * friction;
    }

    void move_down(float deltaTime) {
        this->position.y += speed * deltaTime * friction;
    }
    void move_left(float deltaTime) {
        this->position.x -= speed * deltaTime * friction;
    }
    void move_right(float deltaTime) {
        this->position.x += speed * deltaTime * friction;
    }

    void update() {
        this->rect.setPosition(this->position);
    }
};





int main() {
    sf::RenderWindow window(sf::VideoMode({500, 500}), "Flappy Hampt");
    window.setFramerateLimit(180);
    sf::Clock clock;
    sf::Time last = clock.getElapsedTime();

    bool fly_released = true;
    int fps = 0;

    Player p({100, 100});
    GameObj o2(100, 100, {200, 100}, sf::Color::Red);

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && fly_released) {

            fly_released = false;
        } else if (not sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            fly_released = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            p.move_up(deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            p.move_right(deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            p.move_left(deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            p.move_down(deltaTime);
        }

        window.clear();

        sf::Time current = clock.getElapsedTime();
        fps++;
        if (current.asSeconds() - last.asSeconds() >= 1.0f) {
            std::cout << "FPS: " << fps << std::endl;
            fps = 0;
            last = current;
        }


        o2.draw(window);
        p.draw(window);

        if (p.collide(o2)) {
            std::cout << "Collided" << std::endl;
        }


        p.update();
        window.display();

    }

    return 0;
};