#pragma once
#include "raylib.h"
#include "hitbox.h"

//tipos de gaviota - definen el comportamiento
enum class SeagullType {
    SlowFly,
    FastFly,
    DiveBounce  //cae y rebota
};

class Seagull {
private:

    SeagullType type;

    Vector2 position;
    Vector2 velocity;
    float scale;
    float speed;
    bool active;
    bool hasBounced;

    int frame;
    float frameTimer;

    Rectangle source;
    Rectangle dest;

    static Texture2D slowTexture;
    static Texture2D fastTexture;
    static bool texturesLoaded;

    Hitbox hitbox;

public:
    Seagull(Vector2 startPos, SeagullType type);
    ~Seagull();

    static void LoadTexturesOnce();
    static void UnloadTexturesOnce();

    void Update(float dt);
    void Draw() const;

    bool IsActive() const;
    void Deactivate();
    const Hitbox& GetHitbox() const;
};