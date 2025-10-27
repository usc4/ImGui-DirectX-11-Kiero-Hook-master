#pragma once
#include "../../math/math.h"
#include "../../../ext/imgui/imgui.h"
#include <cstddef>

namespace O
{
    constexpr std::ptrdiff_t dwEntityList = 0x1D07A80; // Updated
    constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x1BE2D10; // Updated
    constexpr std::ptrdiff_t dwViewMatrix = 0x1E25F30; // Updated

    constexpr std::ptrdiff_t m_hPlayerPawn = 0x7DC; // Need Updating 
    constexpr std::ptrdiff_t m_iHealth = 0x324; // Need Updating 
    constexpr std::ptrdiff_t m_iTeamNum = 0x3C3; // Need Updating 
    constexpr std::ptrdiff_t m_vOldOrigin = 0x1274; // Need Updating 
}

namespace V
{
    extern uintptr_t client;

    void PlayerESP();
}
