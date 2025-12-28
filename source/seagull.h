#pragma once
#include "raylib.h"

//tipos de gaviota - definen el comportamiento
enum class SeagullType {
    SlowFly,
    FastFly
};

class Seagull {
private:

    SeagullType type;

    Vector2 position;
    float scale;
    float speed;
    bool active;

    int frame;
    float frameTimer;

    Rectangle source;
    Rectangle dest;

    static Texture2D slowTexture;
    static Texture2D fastTexture;
    static bool texturesLoaded;

public:
    Seagull(Vector2 startPos, SeagullType type);
    ~Seagull();

    static void LoadTexturesOnce();
    static void UnloadTexturesOnce();

    void Update(float dt);
    void Draw() const;

    bool IsActive() const;
};