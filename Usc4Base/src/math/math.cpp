#include "math.h"

const bool Vec3::WorldToScreen(Vec2& out, float(*viewMatrix)[4][4])
{
    const float w = (*viewMatrix)[3][0] * x + (*viewMatrix)[3][1] * y + (*viewMatrix)[3][2] * z + (*viewMatrix)[3][3];

    if (w < 0.01)
    {
        return false;
    }

    const float invW = 1.0f / w;

    const float screenWidth = GetSystemMetrics(SM_CXSCREEN);
    const float screenHeight = GetSystemMetrics(SM_CYSCREEN);

    out.x = (screenWidth / 2) + (((*viewMatrix)[0][0] * x + (*viewMatrix)[0][1] * y + (*viewMatrix)[0][2] * z + (*viewMatrix)[0][3]) * invW * (screenWidth / 2));
    out.y = (screenHeight / 2) - (((*viewMatrix)[1][0] * x + (*viewMatrix)[1][1] * y + (*viewMatrix)[1][2] * z + (*viewMatrix)[1][3]) * invW * (screenHeight / 2));

    return true;
}