#ifndef MINEFIELD_HPP_
#define MINEFIELD_HPP_

#include <vector>
#include "MineCell/MineCell.hpp"

namespace Mines
{
    class MineField {
        public:
            MineField(int width, int height, int mineCount);
            ~MineField() = default;

            MineCell& getCell(int x, int y);
            int getWidth() const { return m_width; };
            int getHeight() const { return m_height; };
            int getMineCount() const { return m_mineCount; };

        private:
            std::vector<std::vector<MineCell>> m_field;
            int m_width;
            int m_height;
            int m_mineCount;

            void placeMines();
            void incrementAdjacentMineCounts(int x, int y);
    };
} // namespace Mines

#endif /* !MINEFIELD_HPP_ */
