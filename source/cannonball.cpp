#include "CannonBall.h"

//al no inicializarlas en el constructor, se evita la carga repetida de la textura (menos uso de memoria)
Texture2D CannonBall::texture;
bool CannonBall::textureLoaded = false;

static const float GRAVITY = 500.0f;    //para simular la caida de la bala

CannonBall::CannonBall(Vector2 startPos, Vector2 initialVelocity)
    : position(startPos), velocity(initialVelocity), active(true) {

    if (!textureLoaded) {
        texture = LoadTexture("assets/cannonball.png");
        textureLoaded = true;
    }
}

CannonBall::~CannonBall() {
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
}

bool CannonBall::IsActive() const {
    return active;
}
