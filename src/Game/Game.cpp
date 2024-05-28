#include "Game.hpp"
#include "Constant/Constant.hpp"
#include "fmt/color.h"
#include "fmt/format.h"

namespace Mines
{

Game::Game(sf::RenderWindow& window, int width, int height, int mineCount) :
m_window(window),
m_field(width, height, mineCount),
m_gameOver(false),
m_gameWon(false),
hiddenCellShape(sf::Vector2f(Constant::cellSizeX, Constant::cellSizeY)),
revealedCellShape(sf::Vector2f(Constant::cellSizeX, Constant::cellSizeY)),
mineSprite(),
flagSprite(),
numberText()
{
        hiddenCellShape.setFillColor(sf::Color::Blue);
        revealedCellShape.setFillColor(sf::Color::White);

        m_textures.m_mineTexture.loadFromFile(Constant::pathToMinePNG);
        mineSprite.setTexture(m_textures.m_mineTexture);

        m_textures.m_flagTexture.loadFromFile(Constant::pathToFlagPNG);
        flagSprite.setTexture(m_textures.m_flagTexture);

        font.loadFromFile(Constant::pathToArialTTF);
        numberText.setFont(font);
        numberText.setCharacterSize(24);
        numberText.setFillColor(sf::Color::Black);
}

void Game::manageEvents(const sf::Event &event)
{
    int fieldWidth = m_field.getWidth() * Constant::cellSizeX;
    int fieldHeight = m_field.getHeight() * Constant::cellSizeY;

    int offsetX = (m_window.getSize().x - fieldWidth) / 2;
    int offsetY = (m_window.getSize().y - fieldHeight) / 2;

    int x = 0;
    int y = 0;

    if (event.type == sf::Event::MouseButtonPressed) {
        int mouseX = event.mouseButton.x;
        int mouseY = event.mouseButton.y;

        int fieldX = (mouseX - offsetX) / Constant::cellSizeX;
        int fieldY = (mouseY - offsetY) / Constant::cellSizeY;

        fmt::print("Clicked on cell {}:{}\n", fieldX, fieldY);

        if (fieldX >= 0 && fieldX < m_field.getWidth() && fieldY >= 0 && fieldY < m_field.getHeight()) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                reveal(fieldX, fieldY);
            } else if (event.mouseButton.button == sf::Mouse::Right) {
                flag(fieldX, fieldY);
            }
        }
    }

    if (isGameOver())
        fmt::print(fg(fmt::color::blue), "Game Over ...\n");
    if (isGameWon())
        fmt::print(fg(fmt::color::blue), "Game Won, GG !!\n");
}

void Game::draw(sf::RenderWindow& window)
{
    int fieldWidth = m_field.getWidth() * Constant::cellSizeX;
    int fieldHeight = m_field.getHeight() * Constant::cellSizeY;

    int offsetX = (window.getSize().x - fieldWidth) / 2;
    int offsetY = (window.getSize().y - fieldHeight) / 2;

    for (int x = 0; x < m_field.getWidth(); ++x) {
        for (int y = 0; y < m_field.getHeight(); ++y) {
            const MineCell& cell = m_field.getCell(x, y);
            sf::Vector2f position(offsetX + x * Constant::cellSizeX, offsetY + y * Constant::cellSizeY);

            if (cell.isRevealed()) {
                revealedCellShape.setPosition(position);
                window.draw(revealedCellShape);

                if (cell.hasAMine()) {
                    mineSprite.setPosition(position);
                    window.draw(mineSprite);
                }
            } else {
                hiddenCellShape.setPosition(position);
                window.draw(hiddenCellShape);

                if (cell.isFlagged()) {
                    flagSprite.setPosition(position);
                    window.draw(flagSprite);
                }
            }

            if (cell.isRevealed() && !cell.hasAMine() && cell.getAdjacentMines() > 0) {
                numberText.setString(std::to_string(cell.getAdjacentMines()));
                numberText.setPosition(offsetX + (x * Constant::cellSizeX) + (Constant::cellSizeX * 0.25), offsetY + y * Constant::cellSizeY);
                window.draw(numberText);
            }
        }
    }
}

void Game::reveal(int x, int y)
{
    if (!isGameOver()) {
        revealCell(x, y);
        checkGameWon();
    }
}

void Game::flag(int x, int y)
{
    if (!isGameOver() && !m_field.getCell(x, y).isRevealed()) {
        m_field.getCell(x, y).toggleFlag();
    }
}

void Game::checkGameWon()
{
    int revealedCount = 0;
    int totalCells = m_field.getWidth() * m_field.getHeight();

    for (int x = 0; x < m_field.getWidth(); ++x) {
        for (int y = 0; y < m_field.getHeight(); ++y) {
            if (m_field.getCell(x, y).isRevealed()) {
                revealedCount++;
            }
        }
    }
    if (revealedCount == totalCells - m_field.getMineCount()) {
        m_gameWon = true;
    }
}

void Game::revealCell(int x, int y)
{
    if (m_field.getCell(x, y).isRevealed() || m_field.getCell(x, y).isFlagged())
        return;

    m_field.getCell(x, y).reveal();
    if (m_field.getCell(x, y).hasAMine()) {
        m_gameOver = true;
    } else if (m_field.getCell(x, y).getAdjacentMines() == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int nx = x + i;
                int ny = y + j;
                if (nx >= 0 && nx < m_field.getWidth() && ny >= 0 && ny < m_field.getHeight()) {
                    revealCell(nx, ny);
                }
            }
        }
    }
}

} // namespace Mines
