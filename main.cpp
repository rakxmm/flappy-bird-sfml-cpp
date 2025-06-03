#include <SFML/Graphics.hpp>
#include <iostream>

class Hampster {
public:
    float width = 40.0f;
    float height = 40.0f;

    sf::Vector2f position;
    sf::Vector2f velocity = {0.f, 0.f};
    sf::RectangleShape rectangle;
    sf::Texture texture;
    std::unique_ptr<sf::Sprite> sprite;



    float speed = 300.f;
    float jump_force = 600.f;
    float gravity = 9.81f;
    float friction = 0.92f;
    float bottom_border = 400.f;



    Hampster(int x, int y) {
        this->position.x = x;
        this->position.y = y;


        if (!texture.loadFromFile("images/Hampster.png")) {
            std::cerr << "Image was not found!!" << std::endl;
        } else {
            sprite = std::make_unique<sf::Sprite>(texture);
            auto textureSize = texture.getSize();

            float scaleX = this->width / textureSize.x;
            float scaleY = this->height / textureSize.y;

            sprite->setScale({scaleX, scaleY});
            sprite->setPosition(sf::Vector2f(position));
        }

        this->rectangle = sf::RectangleShape({this->width, this->width});
        this->rectangle.setPosition(sf::Vector2f(position));
        this->rectangle.setFillColor(sf::Color::Blue);
    }

    void update(float deltaTime) {
        this->velocity.y += this->gravity;
        this->position.y += this->velocity.y * deltaTime;
        this->position.x += this->velocity.x * this->friction * deltaTime;
        this->velocity.x *= this->friction;
        if (this->rectangle.getRotation() <= sf::degrees(90)) {
            this->rectangle.rotate(sf::degrees(100 * deltaTime));
        }

        if (this->position.y >= this->bottom_border) {
            this->velocity.y = 0;
            this->position.y = this->bottom_border;
        }

        this->rectangle.setPosition(sf::Vector2f(this->position));
    }

    bool collide(const sf::Vector2i a) const {
        return a.x >= this->position.x && a.x <= this->position.x + this->width && a.y >= this->position.y && a.y <= this->position.y + this->width;
    }

    void jump() {
        if (this->position.y > 0) {
            this->rectangle.setRotation(sf::degrees(10));
            this->velocity.y = -this->jump_force;
        }
    }

    void move(bool move_left) {
        if (move_left) {
            this->velocity.x = -this->speed;
        } else {
            this->velocity.x = this->speed;
        }
    }

    void draw(sf::RenderWindow& window) {
        if (sprite) {
            window.draw(*sprite);
        }
    };
};




int main() {
    sf::RenderWindow window(sf::VideoMode({500, 500}), "Flappy Hampt");
    window.setFramerateLimit(180);
    sf::Clock clock;
    sf::Time last = clock.getElapsedTime();


    Hampster bird(100, 100);

    bool fly_released = true;
    int fps = 0;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }




        }



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && fly_released) {
            bird.jump();
            fly_released = false;
        } else if (not sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            fly_released = true;
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            bird.move(false);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            bird.move(true);
        }



        bird.update(deltaTime);


        sf::Time current = clock.getElapsedTime();
        fps++;
        if (current.asSeconds() - last.asSeconds() >= 1.0f) {
            std::cout << "FPS: " << fps << std::endl;
            fps = 0;
            last = current;
        }

        window.clear();
        bird.draw(window);

        window.display();

    }

    return 0;
};