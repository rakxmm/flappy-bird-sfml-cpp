#include <SFML/Graphics.hpp>




void clear(sf::RenderWindow& win) {
    win.clear();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(512, 512), "Flappy Bird", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
    window.setFramerateLimit(144);
    sf::RectangleShape cube(sf::Vector2f(100.0f, 100.0f));
    cube.setFillColor(sf::Color::Blue);


    int fps = 0;
    float speed = 3.0f;
    sf::Clock clock;
    sf::Time time = clock.getElapsedTime();
    while (window.isOpen()) {

        sf::Event ev;

        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                window.close();
            }
        }

        clear(window);

        window.draw(cube);
        window.display();

        fps++;
        sf::Time current = clock.getElapsedTime();
        if (current.asSeconds() - time.asSeconds() >= 1.0f) {
            printf("FPS: %i \n", fps);
            fps = 0;
            time = current;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            cube.move(0.0f, -speed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            cube.move(0.0f, speed);
        }

    }


    return 0;
};