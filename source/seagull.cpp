#include "seagull.h"

//para animacion de gaviota lenta
static constexpr int SLOW_FRAME_WIDTH = 32;
static constexpr int SLOW_FRAME_HEIGHT = 16;
static constexpr int SLOW_FRAME_COUNT = 4;
static constexpr float SLOW_FRAME_TIME = 0.1f;

Texture2D Seagull::slowTexture;
Texture2D Seagull::fastTexture;
bool Seagull::texturesLoaded = false;

void Seagull::LoadTexturesOnce() {
    if (!texturesLoaded) {
        slowTexture = LoadTexture("assets/img/seagull_slowfly.png");
        fastTexture = LoadTexture("assets/img/seagull_fastfly.png");
        texturesLoaded = true;
    }
}

Seagull::Seagull(Vector2 startPos, SeagullType t)
    : type(t),
    position(startPos),
    scale(2.0f),
    speed(0.0f),
    active(true),
    frame(0),
    frameTimer(0.0f),
    source{ 0.0f, 0.0f, 32.0f, 16.0f },
    dest{ startPos.x, startPos.y, 32.0f, 16.0f }
{
    //segun que tipo de gaviota sea, usa los parametros para animacion o img estatica
    switch (type) {
    case SeagullType::SlowFly:
        speed = 150.0f;
        source = {
            0.0f,
            0.0f,
            (float)SLOW_FRAME_WIDTH,
            (float)SLOW_FRAME_HEIGHT
        };

        dest = {
            position.x,
            position.y,
            (float)SLOW_FRAME_WIDTH * scale,
            (float)SLOW_FRAME_HEIGHT * scale
        };
        break;

    case SeagullType::FastFly:
        speed = 350.0f;
        source = {
            0.0f,
            0.0f,
            (float)fastTexture.width,
            (float)fastTexture.height
        };

        dest = {
            position.x,
            position.y,
            (float)fastTexture.width * scale,
            (float)fastTexture.height * scale
        };
        break;
    }

    source = { 0, 0, 32, 16 };
    dest = { position.x, position.y, 32, 16 };
}

Seagull::~Seagull() {
}

void Seagull::Update(float dt) {
    if (!active) return;

    position.x += speed * dt;

    //si sale completamente de la pantalla, se desactiva - implementacion a futuro: mejorar rendimiento
    if (position.x > GetScreenWidth())
        active = false;

    if (type == SeagullType::SlowFly) {
        frameTimer += dt;
        if (frameTimer >= SLOW_FRAME_TIME) {
            frameTimer = 0.0f;
            frame = (frame + 1) % SLOW_FRAME_COUNT;
            source.x = frame * SLOW_FRAME_WIDTH;
        }
    }
    
    dest.x = position.x * scale;
    dest.y = position.y * scale;

}

void Seagull::Draw() const {
    if (!active) return;

    const Texture2D& tex =
        (type == SeagullType::SlowFly) ? slowTexture : fastTexture;

    Rectangle drawSource;

    if (type == SeagullType::SlowFly) {
        drawSource = source; // spritesheet animado
    }
    else {
        drawSource = {
            0.0f,
            0.0f,
            (float)tex.width,
            (float)tex.height
        };
    }

    Rectangle drawDest = {
        position.x,
        position.y,
        dest.width * scale,
        dest.height * scale
    };

    DrawTexturePro(
        tex,
        drawSource,
        drawDest,
        { 0.0f, 0.0f },
        0.0f,
        WHITE
    );

    //debug
    //DrawRectangleLines(
    //    (int)position.x,
    //    (int)position.y,
    //    (int)dest.width,
    //    (int)dest.height,
    //    RED
    //);
}


bool Seagull::IsActive() const {
    return active;
}
