#include "Game.h"

Game::Game()
    : cannon({ 75.0f, 650.0f }) {
}

Game::~Game() {
}

void Game::Init() {
    //Carga de recursos (siempre después de InitWindow)
    CannonBall::LoadTextureOnce();
}

void Game::Shutdown() {
    //Liberación explícita de recursos
    CannonBall::UnloadTextureOnce();
}

void Game::Update(float deltaTime) {
    cannon.Update(deltaTime);
}

void Game::Draw() const {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawUI();

    cannon.Draw();

    EndDrawing();
}

void Game::DrawUI() const {
    DrawText(
        "Arriba/Abajo - Angulo de tiro | Izquierda/Derecha - Potencia de disparo | Espacio: Disparar!",
        20, 20, 15, DARKGRAY
    );
}
