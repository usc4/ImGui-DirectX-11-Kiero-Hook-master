#include "visuals.h"

uintptr_t V::client = (uintptr_t)GetModuleHandle("client.dll");

void V::PlayerESP()
{
    {
        float(*ViewMatrix)[4][4] = (float(*)[4][4])((client + O::dwViewMatrix));

        auto localPawn = *(uintptr_t*)(client + O::dwLocalPlayerPawn);

        if (!localPawn)
            return;

        auto localTeam = *(int*)(client + O::m_iTeamNum);

        auto entityList = *(uintptr_t*)(client + O::dwEntityList);

        if (!entityList)
            return;

        for (int i = 1; i < 64; i++)
        {
            uintptr_t list_entry1 = *(uintptr_t*)(entityList + 0x8 * ((i & 0x7FFF) >> 9) + 16);
            if (!list_entry1)
                continue;

            uintptr_t playerController = *(uintptr_t*)(list_entry1 + 120 * (i & 0x1FF));
            if (!playerController)
                continue;

            uintptr_t iPlayerPawn = *(uintptr_t*)(playerController + O::m_hPlayerPawn);
            if (!iPlayerPawn)
                continue;

            uintptr_t list_entry2 = *(uintptr_t*)(entityList + 0x8 * ((iPlayerPawn & 0x7FFF) >> 9) + 16);
            if (!list_entry2)
                continue;

            uintptr_t pCSPlayerPawnPtr = *(uintptr_t*)(list_entry2 + 120 * (iPlayerPawn & 0x1FF));
            if (!pCSPlayerPawnPtr)
                continue;

            int health = *(int*)(pCSPlayerPawnPtr + O::m_iHealth);
            if (!health || health > 100)
                continue;

            int team = *(int*)(pCSPlayerPawnPtr + O::m_iTeamNum);
            if (team == localTeam)
                continue;

            Vec3 feetpos = *(Vec3*)(pCSPlayerPawnPtr + O::m_vOldOrigin);
            Vec3 headpos = feetpos;
            headpos.x += 0.0f;
            headpos.y += 0.0f;
            headpos.z += 65.0f;

            Vec2 feet, head;

            if (feetpos.WorldToScreen(feet, ViewMatrix) && headpos.WorldToScreen(head, ViewMatrix)) {
                float height = (head.y - feet.y) * 1.5f;
                float width = height / 2;
                float x = feet.x - width / 2;
                float y = head.y;
                ImGui::GetBackgroundDrawList()->AddRect({ x, y }, { x + width, y + height }, ImColor(255, 255, 255));
            }
        }
    }
}