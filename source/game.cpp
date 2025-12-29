#include "Game.h"
#include <string>

using namespace std;

static constexpr float BASKET_ATTACK_MARGIN = 50.0f;

Game::Game()
    : cannon({ 75.0f, 650.0f }),
    seagullSpawnTimer(0.0f),
    seagullSpawnInterval(2.0f),
    basket({ GetScreenWidth() / 2.0f - 64.0f, GetScreenHeight() - 120.f }),
    state(GameState::Playing)
{

}

Game::~Game() {
}

void Game::Init() {
    //Carga de recursos (siempre después de InitWindow) - NO OLVIDAR
    CannonBall::LoadTextureOnce();
    Seagull::LoadTexturesOnce();
    Basket::LoadTexturesOnce();
    basket.Init();
}

void Game::Shutdown() {
    //Liberación explícita de recursos
    CannonBall::UnloadTextureOnce();
    //Seagull::UnloadTexturesOnce();
    Basket::UnloadTexturesOnce();
}

void Game::Update(float deltaTime) {

    //DERRORTA
    if (state == GameState::GameOver)
    {
        UpdateGameOver();
        return;
    }

    //JUGANDO

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

        //para las gaviotas que rebotan
        Vector2 initialVelocity{ 0.0f, 0.0f };
        bool needsCustomVelocity = false;

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
            //calculo para que targeteen la canasta
            float basketCenterX = basket.GetPosition().x + basket.GetWidth() * 0.5f;

            float minAttackX = basketCenterX - BASKET_ATTACK_MARGIN;
            float maxAttackX = basketCenterX + BASKET_ATTACK_MARGIN;

            float spawnX = GetRandomValue(     //mejora para acotar la zona de spawn
                (int)minAttackX,
                (int)maxAttackX
            );

            spawnPos = Vector2{ spawnX, -50.0f };

            const float AIM_ERROR = 10.0f;
            float targetX = basketCenterX + GetRandomValue(-AIM_ERROR, AIM_ERROR);  

            float dirX = targetX - spawnX;

            initialVelocity = {
                dirX * 1.2f,
                280.0f
            };

            needsCustomVelocity = true; //luego se usa para ajustar
            break;
        }
        }

        // Crear la gaviota
        seagulls.emplace_back(spawnPos, type);

        //para la gaviota que rebota, se setea la velocidad
        if (needsCustomVelocity)
        {
            seagulls.back().SetVelocity(initialVelocity);
        }
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

                seagullsKilled++;

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

    //control de vidas y derrota
    if (basket.IsEmpty())
    {
        state = GameState::GameOver;
    }

}

void Game::Draw() const {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawUI();

    if (state == GameState::Playing)
    {
        DrawUI();
        cannon.Draw();
        basket.Draw();

        for (const auto& g : seagulls)
            g.Draw();
    }
    else
    {
        DrawGameOver();
    }

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

void Game::UpdateGameOver()
{
    if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        ResetGame();
        state = GameState::Playing;
    }
}

void Game::DrawGameOver() const
{
    const char* title = "Te quedaste sin pescado!";
    string stats = "Abatiste " + to_string(seagullsKilled) + " gaviotas antes de que te robaran todo el pescado.";
    const char* restart = "Para intentar de nuevo, presiona ENTER o has CLICK";

    int titleSize = 50;
    int statsSize = 30;
    int restartSize = 20;

    int centerX = GetScreenWidth() / 2;
    int centerY = GetScreenHeight() / 2;

    int titleWidth = MeasureText(title, titleSize);
    int statsWidth = MeasureText(stats.c_str(), statsSize);
    int restartWidth = MeasureText(restart, restartSize);

    //mensaje derrota
    DrawText(
        title,
        centerX - titleWidth / 2,
        centerY - 80,
        titleSize,
        RED
    );

    //estadísticas
    DrawText(
        stats.c_str(),
        centerX - statsWidth / 2,
        centerY - 10,
        statsSize,
        GOLD
    );

    //instrucciones
    DrawText(
        restart,
        centerX - restartWidth / 2,
        centerY + 40,
        restartSize,
        DARKGRAY
    );
}


void Game::ResetGame()
{
    //reseteo al estado inicial del juego
    seagulls.clear();
    cannon.Reset();
    basket.Reset();

    seagullSpawnTimer = 0.0f;
}