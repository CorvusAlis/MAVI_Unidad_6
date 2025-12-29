#include "Game.h"

using namespace std;

Game::Game()
    : cannon({ 75.0f, 650.0f }),
    seagullSpawnTimer(0.0f),
    seagullSpawnInterval(2.0f),
    basket({ GetScreenWidth() / 2.0f - 64.0f, GetScreenHeight() - 120.f })
{

}

Game::~Game() {
}

void Game::Init() {
    //Carga de recursos (siempre después de InitWindow) - NO OLVIDAR
    CannonBall::LoadTextureOnce();
    Seagull::LoadTexturesOnce();
    Basket::LoadTexturesOnce();
}

void Game::Shutdown() {
    //Liberación explícita de recursos
    CannonBall::UnloadTextureOnce();
    //Seagull::UnloadTexturesOnce();
    Basket::UnloadTexturesOnce();
}

void Game::Update(float deltaTime) {

    //update de entradas y timers
    cannon.Update(deltaTime);

    // spawn de entidades
    seagullSpawnTimer += deltaTime;

    if (seagullSpawnTimer >= seagullSpawnInterval)
    {
        seagullSpawnTimer = 0.0f;   //control del intervalo de aparicion

        //sale uno de los 3 tipos de gaviota de forma aleatoria
        int randomType = GetRandomValue(0, 2);
        SeagullType type = static_cast<SeagullType>(randomType);

        Vector2 spawnPos;

        switch (type)
        {
        case SeagullType::SlowFly:
        case SeagullType::FastFly:
        {
            float randomY = GetRandomValue(50, 300);    //aparecen por el costado izquierdo
            spawnPos = Vector2{ -50.0f, randomY };
            break;
        }

        case SeagullType::DiveBounce:
        {
            float randomX = GetRandomValue(50, GetScreenWidth() - 50);  //aparecen por la parte superior
            spawnPos = Vector2{ randomX, -50.0f };
            break;
        }
        }

        // Crear la gaviota
        seagulls.emplace_back(spawnPos, type);
    }

    //update de entidades

    for (auto& g : seagulls)
        g.Update(deltaTime);

    //for (auto& b : cannon.GetBullets())
    //    b.Update(deltaTime);

    //colisiones

    //bala - gaviota
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

    //gaviota - canasta
    for (auto& g : seagulls)
    {
        if (!g.IsActive()) continue;

        if (g.GetHitbox().Intersectan(basket.GetHitbox()))
        {
            g.Deactivate();
            basket.LoseFish();
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
    basket.Draw();

    for (const auto& g : seagulls)
        g.Draw();

    EndDrawing();
}

void Game::DrawUI() const {
    //info cañon - barra de potencia                
    const int barWidth = 200;
    const int barHeight = 10;

    int barX = 20;
    int barY = GetScreenHeight() - 30;
                                            //MAX_POWER en cannon
    float powerRatio = cannon.GetPower() / 900.0f;

    DrawRectangle(
        barX,
        barY,
        (int)(powerRatio * barWidth),
        barHeight,
        RED
    );

    DrawRectangleLines(
        barX,
        barY,
        barWidth,
        barHeight,
        BLACK
    );

    //instrucciones
    DrawText(
        "Arriba/Abajo: Angulo | Izquierda/Derecha: Potencia | Espacio: Disparar",
        20,
        20,
        20,
        DARKGRAY
    );
}
