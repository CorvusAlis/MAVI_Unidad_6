#include "CannonBall.h"

static const float GRAVITY = 500.0f;    //para simular la caida de la bala

//al no inicializarlas en el constructor, se evita la carga repetida de la textura (menos uso de memoria)
Texture2D CannonBall::texture = { 0 };

void CannonBall::LoadTextureOnce() {
    if (texture.id == 0) {
        texture = LoadTexture("assets/img/cannon_ball.png");
        TraceLog(LOG_WARNING, "LoadTextureOnce CALLED");
    }
}

void CannonBall::UnloadTextureOnce() {
    if (texture.id != 0) {
        UnloadTexture(texture);
        texture = { 0 };
    }
}

CannonBall::CannonBall(Vector2 startPos, Vector2 initialVelocity)
    : position(startPos), velocity(initialVelocity), active(true) {

}

void CannonBall::Update(float dt) {
    if (!active) return;

    velocity.y += GRAVITY * dt;
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    if (position.y > GetScreenHeight())
        active = false;
}

void CannonBall::Draw() const {
    if (!active) return;

    DrawTextureV(
        texture,
        {
            position.x - texture.width / 2.0f,
            position.y - texture.height / 2.0f
        },
        WHITE
    );
    //debug
    //DrawCircleV(position, 5, RED);
}

bool CannonBall::IsActive() const {
    return active;
}
