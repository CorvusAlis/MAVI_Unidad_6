#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"

int main(void)
{

    InitWindow(800, 450, "Salva tus peces!");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(SKYBLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

