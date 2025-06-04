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
        return  obj.position.x + obj.size.x > this->position.x &&
                obj.position.x < this->position.x + this->size.x &&
                obj.position.y + obj.size.y > this->position.y &&
                obj.position.y < this->position.y + this->size.y;
    }
};


class Player : public GameObj {
public:
    float speed = 300.f;
    float friction = 0.99f;
    float gravity = 981.f;
    float jump_force = 400.f;
    float bottom_border = 500.f;

    sf::Vector2f velocity;

    Player(sf::Vector2f position)
        : GameObj(50, 50, position, sf::Color::Blue)
    {

    }



    void move_left(float deltaTime) {
        this->position.x -= speed * deltaTime * friction;
    }
    void move_right(float deltaTime) {
        this->position.x += speed * deltaTime * friction;
    }

    void jump() {
        if (this->position.y > 0) {
            this->velocity.y = -jump_force;
        }

    }

    void update(float deltaTime) {
        this->velocity.y += gravity * deltaTime;
        this->position.y += velocity.y * deltaTime;

        if (this->position.y > bottom_border) {
            this->position.y = bottom_border;
        }

        this->rect.setPosition(this->position);
    }
};


class Pipe : public GameObj {
public:
    float speed = 150.f;
    float gap;
    sf::RectangleShape rect_up;
    sf::RectangleShape rect_down;

    Pipe(float gap, sf::Vector2f position) : GameObj(100, 300, position, sf::Color::Red) {
        auto size = this->rect.getSize();
        this->gap = gap;

        if (rand() % 2 == 0) {
            rect_up.setSize({size.x, size.y - gap});
            rect_down.setSize(size);
        } else {
            rect_up.setSize(size);
            rect_down.setSize({size.x, size.y - gap});
        }
        rect_up.setPosition({position.x, position.y});
        rect_down.setPosition({position.x, size.y + gap + position.y});

    }

    void update(float deltaTime) {
        if (this->position.x + this->size.x >= 0) {
            this->position.x -= speed * deltaTime;
        }
        // this->rect.setSize(this->size);
        this->rect_up.setPosition(this->position);
        this->rect_down.setPosition({this->position.x, this->rect_up.getSize().y + this->gap + this->position.y});
    }

    bool collide(const GameObj& obj) const {
        return  obj.position.x + obj.size.x > rect_up.getPosition().x &&
                obj.position.x < rect_up.getPosition().x + rect_up.getSize().x &&
                obj.position.y + obj.size.y > rect_up.getPosition().y &&
                obj.position.y < rect_up.getPosition().y + rect_up.getSize().y ||
                    obj.position.x + obj.size.x > rect_down.getPosition().x &&
                obj.position.x < rect_down.getPosition().x + rect_down.getSize().x &&
                obj.position.y + obj.size.y > rect_down.getPosition().y &&
                obj.position.y < rect_down.getPosition().y + rect_down.getSize().y;
    }


    void draw(sf::RenderWindow& window) {
        window.draw(rect_up);
        window.draw(rect_down);
    }


};


int main() {
    sf::RenderWindow window(sf::VideoMode({500, 500}), "Flappy Hampt");
    window.setFramerateLimit(180);
    sf::Clock clock;
    sf::Time last = clock.getElapsedTime();

    bool fly_released = true;
    int fps = 0;
    int points = 0;
    bool passed = false;

    Player p({100, 100});
    Pipe* pipe = new Pipe(100, {400, 0});

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && fly_released) {
            p.jump();
            fly_released = false;
        } else if (not sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            fly_released = true;
        }



        window.clear();

        sf::Time current = clock.getElapsedTime();
        fps++;
        if (current.asSeconds() - last.asSeconds() >= 1.0f) {
            std::cout << "FPS: " << fps << std::endl;
            fps = 0;
            last = current;
        }


        pipe->draw(window);
        p.draw(window);

        if (pipe->position.x + pipe->size.x <= 0) {
            delete pipe;
            float gap = rand() % 200 + 50;
            pipe = new Pipe(gap, {500, 0});
        }

        if (!pipe->collide(p)) {
            pipe->update(deltaTime);
        } else {
            points = 0;
        }

        if (p.position.x > pipe->position.x + pipe->size.x) {
            if (not passed) {
                points++;
                std::cout << "Points: " << points << std::endl;
                passed = true;
            }

        } else {
            passed = false;
        }

        p.update(deltaTime);
        window.display();

    }

    return 0;
};