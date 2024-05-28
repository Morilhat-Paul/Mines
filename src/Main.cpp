#include <SFML/Graphics.hpp>
#include <fmt/color.h>
#include <fmt/format.h>

#include "Constant/Constant.hpp"
#include "Game/Game.hpp"

int main(int argc, char const *argv[])
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "Mines" };
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    Mines::Game game(window, 8, 8, 10);
    sf::Clock clock;
    const sf::Time frameTime = sf::seconds(1.f / 60.f);

    fmt::print(fg(fmt::color::blue), "--- Game started ---\n");

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();

        while (elapsed < frameTime) {
            elapsed += clock.getElapsedTime();
        }

        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            game.manageEvents(event);
            // if (game.isGameOver())
            //     window.close();
        }

        window.clear();
        game.draw(window);
        window.display();
    }

    fmt::print(fg(fmt::color::blue), "--- Game ended ---\n");

    return EXIT_SUCCESS;
}
