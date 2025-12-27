#include "Cannon.h"
#include "raymath.h"
#include <cmath>

//para evitar rotar el cañon de mas o de menos - se mueve entre 0 y 90 grados (raylib maneja radianes)
static const float MIN_ANGLE = -PI / 2.0f;
static const float MAX_ANGLE = 0.0f;

Cannon::Cannon(Vector2 pos)
    : position(pos), angle(0.0f), power(600.0f), scale(2.5f) {

    texture = LoadTexture("assets/img/cannon.png");

    origin = {
        0.0f, //borde izquierdo
        texture.height * scale / 2.0f //centro vertical - se escala para mover el pivote con la textura
    };
}

Cannon::~Cannon() {
    UnloadTexture(texture);
}

void Cannon::Update(float dt) {

    //control del angulo de tiro y el poder de disparo
    if (IsKeyDown(KEY_UP)) angle -= 1.5f * dt;
    if (IsKeyDown(KEY_DOWN)) angle += 1.5f * dt;

    if (IsKeyDown(KEY_RIGHT)) power += 200.0f * dt;
    if (IsKeyDown(KEY_LEFT)) power -= 200.0f * dt;
    
    //funcion Clamp de raymath - limite entre dos valores
    power = Clamp(power, 200.0f, 900.0f);
    angle = Clamp(angle, MIN_ANGLE, MAX_ANGLE);

    if (IsKeyPressed(KEY_SPACE)) {
        Vector2 velocity = {
            power * cosf(angle),
            power * sinf(angle)
        };

        //para que las balas salgan desde la punta del cañon
        float barrelLength = texture.width * scale;

        //spawn de las balas
        Vector2 spawnPos = {
            position.x + cosf(angle) * barrelLength,
            position.y + sinf(angle) * barrelLength
        };

        //probando uso de vectores: emplace_back coloca un objeto "cannonball" en el vector cannonballs (ver cannon.h)
        //usando los parametros pasados para construir el una bala de cañon
        cannonballs.emplace_back(spawnPos, velocity);
    }

    for (auto& ball : cannonballs)
        ball.Update(dt);
}

void Cannon::Draw() const {

    Rectangle src = {
        0, 0,
        (float)texture.width,
        (float)texture.height
    };

    Rectangle dst = {
        position.x,
        position.y,
        (float)texture.width * scale,
        (float)texture.height * scale
    };

    DrawTexturePro(
        texture,
        src,
        dst,
        origin,
        angle * RAD2DEG,
        WHITE
    );

    //debug pivote de cañon
    //DrawCircleV(position, 4, RED);

    for (const auto& ball : cannonballs)
        ball.Draw();
}
