#include "Game.h"

using namespace std;

Game::Game()
    : cannon({ 75.0f, 650.0f }),
    seagullSpawnTimer(0.0f),
    seagullSpawnInterval(2.0f)
{

}

Game::~Game() {
}

void Game::Init() {
    //Carga de recursos (siempre después de InitWindow)
    CannonBall::LoadTextureOnce();
    Seagull::LoadTexturesOnce();
}

void Game::Shutdown() {
    //Liberación explícita de recursos
    CannonBall::UnloadTextureOnce();
    //Seagull::UnloadTexturesOnce();
}

void Game::Update(float deltaTime) {

    //update de entradas y timers
    cannon.Update(deltaTime);

    seagullSpawnTimer += deltaTime;

    //spawn de entidades
    if (seagullSpawnTimer >= seagullSpawnInterval) {
        seagullSpawnTimer = 0.0f;   //controla la salida de gaviotas cada intervalo de tiempo

        float randomY = GetRandomValue(50, 300);    //spawnea una gaviota a distintas alturas

        SeagullType type =
            (GetRandomValue(0, 1) == 0) ? SeagullType::SlowFly : SeagullType::FastFly;

        //importante - paso la ubicacion y el tipo de la gaviota; el tipo tiene los demas datos
        seagulls.emplace_back(
            Vector2{ -50.0f, (float)randomY },
            type
        );
    }

    //update de entidades

    for (auto& g : seagulls)
        g.Update(deltaTime);

    for (auto& b : cannon.GetBullets())
        b.Update(deltaTime);

    //colisiones

    for (auto& b : cannon.GetBullets()) {
        if (!b.IsActive()) continue;

        for (auto& g : seagulls) {
            if (!g.IsActive()) continue;

            if (b.GetHitbox().Intersectan(g.GetHitbox())) {
                b.Deactivate();
                g.Deactivate();
                break; //la bala ya no puede colisionar más
            }
        }
    }

    //limpio objetos inactivos

    cannon.CleanBullets();

    seagulls.erase(
        remove_if(
            seagulls.begin(),
            seagulls.end(),
            [](const Seagull& g) { return !g.IsActive(); }
        ),
        seagulls.end()
    );

}

void Game::Draw() const {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawUI();

    cannon.Draw();

    for (const auto& g : seagulls)
        g.Draw();

    EndDrawing();
}

void Game::DrawUI() const {
    DrawText(
        "Arriba/Abajo - Angulo de tiro | Izquierda/Derecha - Potencia de disparo | Espacio: Disparar!",
        20, 20, 15, DARKGRAY
    );
}
