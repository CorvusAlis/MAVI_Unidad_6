#pragma once
#include "raylib.h"
#include "cannon.h"
#include "cannonball.h"
#include "seagull.h"
#include "basket.h"

using namespace std;

//Probando clase Game (manager de entidades)
//Esta clase se encargara de hacer todos los draw y updates de la entidades del juego (cañon, balas de cañon, gaviotas, etc)
//Maneja la carga y descarga de recursos compartidos (texturas)
//Se llama desde el main, para mantenerlo limpio y mejorar el encapsulamiento de las clases del proyecto
//Tambien se encargara de dibujar elementos de UI

class Game {
private:
    Cannon cannon;
    vector<Seagull> seagulls;
    Basket basket;

    float seagullSpawnTimer;
    float seagullSpawnInterval;

public:
    Game();
    ~Game();

    void Init();
    void Shutdown();

    void Update(float deltaTime);
    void Draw() const;
    void DrawUI() const;
};
