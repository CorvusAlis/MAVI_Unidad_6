#include "seagull.h"
#include <raymath.h>

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

void Seagull::UnloadTexturesOnce() {
    if (slowTexture.id != 0) {
        UnloadTexture(slowTexture);
        slowTexture = { 0 };
    }
    if (fastTexture.id != 0) {
        UnloadTexture(fastTexture);
        fastTexture = { 0 };
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
    dest{ startPos.x, startPos.y, 32.0f, 16.0f },
    hasBounced(false),
    velocity(),
    hitbox() //NO TE OLVIDES DE AGREGAR LA HITBOX PANFLINA
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

        //hitbox un poco más chica que el sprite
        hitbox = Hitbox(
            SLOW_FRAME_WIDTH * scale * 0.8f,
            SLOW_FRAME_HEIGHT * scale * 0.8f,
            {
                SLOW_FRAME_WIDTH * scale * 0.1f,
                SLOW_FRAME_HEIGHT * scale * 0.1f
            }
        );
        break;

    case SeagullType::FastFly:
        speed = 350.0f;

        source = {
            0.0f,
            0.0f,
            (float)fastTexture.width,
            (float)fastTexture.height
        };

        hitbox = Hitbox(
            fastTexture.width * scale * 0.8f,
            fastTexture.height * scale * 0.8f,
            {
                fastTexture.width * scale * 0.1f,
                fastTexture.height * scale * 0.1f
            }
        );
        break;
    
    case SeagullType::DiveBounce:
    {
        speed = 0.0f;
        velocity = {
            (GetRandomValue(0, 1) == 0) ? -150.0f : 150.0f,
            250.0f
        };
        hasBounced = false;

        source = {
            0.0f,
            0.0f,
            (float)fastTexture.width,
            (float)fastTexture.height
        };

        dest = {
            position.x,
            position.y,
            source.width * scale,
            source.height * scale
        };

        hitbox = Hitbox(
            fastTexture.width * scale * 0.8f,
            fastTexture.height * scale * 0.8f,
            {
                fastTexture.width * scale * 0.1f,
                fastTexture.height * scale * 0.1f
            }
        );
        break;
    }
    }

    //sinrcro inicial de hitbox
    hitbox.Sincro(position);
}

Seagull::~Seagull() {
}

void Seagull::Update(float dt)
{
    if (!active) return;

    switch (type)
    {
    case SeagullType::SlowFly:
        position.x += speed * dt;

        frameTimer += dt;
        if (frameTimer >= SLOW_FRAME_TIME)
        {
            frameTimer = 0.0f;
            frame = (frame + 1) % SLOW_FRAME_COUNT;
            source.x = frame * SLOW_FRAME_WIDTH;
        }

        if (position.x > GetScreenWidth())
            active = false;
        break;

    case SeagullType::FastFly:
        position.x += speed * dt;

        if (position.x > GetScreenWidth())
            active = false;
        break;

    case SeagullType::DiveBounce:
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;

        // rebote contra el piso
        if (!hasBounced && position.y >= GetScreenHeight() - dest.height)
        {
            position.y = GetScreenHeight() - dest.height;
            velocity.y = -fabs(velocity.y) * 0.7f;  //rebote de salida mas bonito y natural
            hasBounced = true;
        }

        // sale por los costados
        if (position.x < -dest.width || position.x > GetScreenWidth())
            active = false;
        break;
    }

    hitbox.Sincro(position);
}


void Seagull::Draw() const {
    if (!active) return;

    const Texture2D& tex =
        (type == SeagullType::SlowFly) ? slowTexture : fastTexture;

    Rectangle drawSource =
        (type == SeagullType::SlowFly) ? source : Rectangle{ 0, 0, (float)tex.width, (float)tex.height };   //pregunta que tipo de gaviota es y renderiza animacion o dibujo

    Rectangle drawDest = {
        position.x,
        position.y,
        drawSource.width * scale,
        drawSource.height * scale
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

    //hitbox.Draw();
}

bool Seagull::IsActive() const { return active; }

void Seagull::Deactivate() { active = false; }

const Hitbox& Seagull::GetHitbox() const { return hitbox; }
