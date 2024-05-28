#include "Constant/Constant.hpp"
#include "Textures.hpp"
#include <fmt/color.h>
#include <fmt/format.h>

namespace Mines
{

Textures::Textures()
{
    m_flagTexture.loadFromFile(Constant::pathToFlagPNG);
    m_mineTexture.loadFromFile(Constant::pathToMinePNG);
    fmt::print(fg(fmt::color::green), "All textures load\n");
}

Textures::~Textures()
{
    fmt::print(fg(fmt::color::green), "All textures unload\n");
}

} // namespace Mines
