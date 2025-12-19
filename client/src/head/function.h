#pragma once

#include <SFML/Graphics/Color.hpp>
#include <cstdint>

inline auto HEX_TO_COLOR(uint32_t hex, uint8_t alpha) -> sf::Color {
    return {static_cast<uint8_t>((hex >> 16) & 0xFF), static_cast<uint8_t>((hex >> 8) & 0xFF),
            static_cast<uint8_t>(hex & 0xFF), alpha};
}
