#ifndef TEXTURES_HPP_
#define TEXTURES_HPP_

#include <SFML/Graphics/Texture.hpp>

namespace Mines
{
    class Textures {
        public:
            Textures();
            ~Textures();

            sf::Texture m_mineTexture;
            sf::Texture m_flagTexture;

        private:

    };
} // namespace Mines

#endif /* !TEXTURES_HPP_ */
