#include "MineField.hpp"
#include <fmt/color.h>
#include <fmt/format.h>
#include <ctime>

namespace Mines
{

MineField::MineField(int width, int height, int mineCount) :
m_width(width),
m_height(height),
m_mineCount(mineCount),
m_field(width, std::vector<MineCell>(height))
{
    fmt::print(fg(fmt::color::blue), "Mine field created !\n");
    placeMines();
}

MineCell& MineField::getCell(int x, int y)
{
    return m_field[x][y];
}

void MineField::placeMines()
{
    int placedMines = 0;
    std::srand(std::time(0));

    while (placedMines < m_mineCount) {
        int x = std::rand() % m_width;
        int y = std::rand() % m_height;

        if (!m_field[x][y].hasAMine()) {
            m_field[x][y].placeMine();
            placedMines++;
            incrementAdjacentMineCounts(x, y);
        }
    }

    fmt::print(fg(fmt::color::blue), "Mine have been place in the field !\n");
}

void MineField::incrementAdjacentMineCounts(int x, int y)
{
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int nx = x + i;
            int ny = y + j;
            if ((nx >= 0) && (nx < m_width) && (ny >= 0) && (ny < m_height)) {
                if (!(i == 0 && j == 0)) {
                    m_field[nx][ny].setAdjacentMines(m_field[nx][ny].getAdjacentMines() + 1);
                }
            }
        }
    }
}

} // namespace Mines
