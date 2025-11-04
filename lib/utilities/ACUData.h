#ifndef ACUDATA_H
#define ACUDATA_H

#include <cstdint>
#include <array>

namespace ACUConstants
{
    constexpr uint8_t NUM_CHIPS = 12;
    constexpr uint8_t NUM_CELLS = 126;
    constexpr uint8_t NUM_CELLTEMPS = 48;

    constexpr std::array<uint8_t, NUM_CHIPS> VOLTAGE_CELLS_PER_CHIP = {
        12, 9, 12, 9, 12, 9, 12, 9, 12, 9, 12, 9
    };

    constexpr std::array<uint8_t, NUM_CHIPS> TEMPS_PER_CHIP = {
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    };
}

#endif