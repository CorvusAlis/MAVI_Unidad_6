#include "Cannon.h"
#include "raymath.h"
#include <cmath>


Cannon::Cannon(Vector2 pos)
    : position(pos), angle(-PI / 4), power(600.0f) {

    texture = LoadTexture("assets/cannon.png");
    origin = { 0.0f, texture.height / 2.0f };
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

    power = Clamp(power, 200.0f, 900.0f);   //funcion Clamp de raymath - limita el valor que se le puede dar al poder de disparo

    if (IsKeyPressed(KEY_SPACE)) {
        Vector2 velocity = {
            power * cosf(angle),
            power * sinf(angle)
        };

        Vector2 spawnPos = {
            position.x + cosf(angle) * texture.width,
            position.y + sinf(angle) * texture.width
        };

        //probando uso de vectores: emplace_back coloca un objeto "cannonball" en el vector cannonballs (ver cannon.h)
        //usando los parametros pasados para construir el una bala de cañon
        cannonballs.emplace_back(spawnPos, velocity);
    }

    for (auto& ball : cannonballs)
        ball.Update(dt);
}

void Cannon::Draw() const {
    Rectangle src = { 0, 0, (float)texture.width, (float)texture.height };
    Rectangle dst = { position.x, position.y, texture.width, texture.height };

    DrawTexturePro(
        texture,
        src,
        dst,
        origin,
        angle * RAD2DEG,
        WHITE
    );

    for (const auto& ball : balls)
        ball.Draw();
}
