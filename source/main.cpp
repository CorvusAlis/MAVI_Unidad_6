#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include "game.h"

int main(void)
{

    InitWindow(1280, 720, "Salva tus peces!");
    SetTargetFPS(60);

    Game game; //se maneja todo desde esta clase
    game.Init();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        //todos los cambios en los updates y draws se manejan desde game
        BeginDrawing();
        game.Update(dt);
        game.Draw();
        EndDrawing();
    }

    game.Shutdown();
    CloseWindow();

    return 0;
}

