#pragma once
#include "raylib.h"
#include "cannon.h"
#include "cannonball.h"
#include "seagull.h"
#include "basket.h"

using namespace std;

//Esta clase se encargara de hacer todos los draw, updates y colisiones de la entidades del juego
//Maneja la UI y los estados del juego (jugando, victoria/derrota)
//Maneja la carga y descarga de recursos compartidos (texturas)
//Se llama desde el main, para mantenerlo limpio y mejorar el encapsulamiento de las clases del proyecto

enum class GameState
{
    Playing,
    GameOver
};

class Game {
private:
    Cannon cannon;
    vector<Seagull> seagulls;
    Basket basket;

    float seagullSpawnTimer;
    float seagullSpawnInterval;
    int seagullsKilled = 0;

    GameState state;

public:
    Game();
    ~Game();

    void Init();
    void Shutdown();

    void Update(float deltaTime);
    void Draw() const;
    void DrawUI() const;

    void UpdateGameOver();
    void DrawGameOver() const;
    void ResetGame();
};
