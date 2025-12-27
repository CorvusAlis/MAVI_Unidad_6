#pragma once
#include "raylib.h"

using namespace std;

class CannonBall {
private:
    Vector2 position;
    Vector2 velocity;
    bool active;    //controla si esta en pantalla

    //probando static: la textura pertenece a la clase, no a cada instancia particular
    //la textura es un recurso usado por la clase, no cada instancia
    static Texture2D texture;
    static bool textureLoaded;

public:
    CannonBall(Vector2 startPos, Vector2 initialVelocity);
    ~CannonBall();

    void Update(float deltaTime);
    void Draw() const;

    bool IsActive() const;
};
