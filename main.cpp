#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "WHGC", sf::Style::Fullscreen);

    window.setFramerateLimit(60);
    
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Red);
    player.setPosition(100.f, 100.f);

    float speed = 5.f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // ESC zamyka fullscreen
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        sf::Vector2f position = player.getPosition();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            position.y -= speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            position.y += speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            position.x -= speed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            position.x += speed;
        }

        if (position.x < 0)
            position.x = 0;

        if (position.y < 0)
            position.y = 0;

        if (position.x + player.getSize().x > desktop.width)
            position.x = desktop.width - player.getSize().x;

        if (position.y + player.getSize().y > desktop.height)
            position.y = desktop.height - player.getSize().y;

        player.setPosition(position);

        window.clear(sf::Color::Black);

        window.draw(player);

        window.display();
    }

    return 0;
}