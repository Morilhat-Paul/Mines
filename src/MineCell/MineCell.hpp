#ifndef MINECELL_HPP_
#define MINECELL_HPP_

namespace Mines
{
    class MineCell {
        public:
            MineCell() : m_hasMine(false), m_isRevealed(false), m_isFlagged(false), m_adjacentMines(0) {};
            ~MineCell() = default;

            inline bool hasAMine() const { return m_hasMine; }
            inline void placeMine() { m_hasMine = true; }

            inline bool isRevealed() const { return m_isRevealed; }
            inline void reveal() { m_isRevealed = true; }

            inline bool isFlagged() const { return m_isFlagged; }
            inline void toggleFlag() { m_isFlagged = !m_isFlagged; }

            inline int getAdjacentMines() const { return m_adjacentMines; }
            inline void setAdjacentMines(int count) { m_adjacentMines = count; }

            bool isClicked() const;

        private:
            bool m_hasMine;
            bool m_isRevealed;
            bool m_isFlagged;
            int m_adjacentMines;
    };
} // namespace Mines

#endif /* !MINECELL_HPP_ */
