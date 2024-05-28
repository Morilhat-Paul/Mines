#ifndef GAME_HPP_
#define GAME_HPP_

#include <SFML/Graphics.hpp>
#include "MineField/MineField.hpp"
#include "Textures/Textures.hpp"

namespace Mines
{
    class Game {
        public:
            Game(sf::RenderWindow& window, int width, int height, int mineCount);
            ~Game() = default;

            bool isGameOver() const { return m_gameOver; };
            bool isGameWon() const { return m_gameWon; };

            void manageEvents(const sf::Event& event);
            void draw(sf::RenderWindow& window);

            void reveal(int x, int y);
            void flag(int x, int y);
            void checkGameWon();

        private:
            sf::RenderWindow& m_window;
            MineField m_field;
            bool m_gameOver;
            bool m_gameWon;

            Textures m_textures;
            sf::Font font;
            sf::Text numberText;
            sf::RectangleShape hiddenCellShape;
            sf::RectangleShape revealedCellShape;
            sf::Sprite mineSprite;
            sf::Sprite flagSprite;

            void revealCell(int x, int y);

    };
} // namespace Mines

#endif /* !GAME_HPP_ */
