#include <SFML/Graphics.hpp>
#include <iostream>


void clear(sf::RenderWindow& win) {
    win.clear();
}

class Stvorec {
public:
    float width = 40.0f;
    sf::Vector2i position;

    sf::RectangleShape rectangle;

    Stvorec(int x, int y) {
        this->position.x = x;
        this->position.y = y;
        this->rectangle = sf::RectangleShape({this->width, this->width});
        this->rectangle.setPosition(sf::Vector2f(position));
        this->rectangle.setFillColor(sf::Color::Blue);
    }

    void setPosition(sf::Vector2i np) {
        this->position = np;
        this->rectangle.setPosition(sf::Vector2f(this->position));
    }

    bool collide(const sf::Vector2i a) const {
        return a.x >= this->position.x && a.x <= this->position.x + this->width && a.y >= this->position.y && a.y <= this->position.y + this->width;
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode({500, 500}), "Flappy Birds");
    window.setFramerateLimit(180);
    sf::Clock clock;
    sf::Time last = clock.getElapsedTime();


    Stvorec s(100, 100);


    int fps = 0;
    while (window.isOpen()) {

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }


        }

        auto pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        auto mouse = sf::Mouse::getPosition(window);


        if (pressed && s.collide(mouse)) {
            s.rectangle.setFillColor(sf::Color::Red);
            s.setPosition({mouse.x - (int)s.width / 2, mouse.y - (int)s.width / 2});
        } else {
            s.rectangle.setFillColor(sf::Color::Blue);
        }



        sf::Time current = clock.getElapsedTime();
        fps++;
        if (current.asSeconds() - last.asSeconds() >= 1.0f) {
            std::cout << "FPS: " << fps << std::endl;
            fps = 0;
            last = current;
        }

        window.clear();
        window.draw(s.rectangle);

        window.display();

    }

    return 0;
};