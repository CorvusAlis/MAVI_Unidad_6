#pragma once
#include "raylib.h"
#include "Hitbox.h"

class Basket {
private:
    Vector2 position;
    int fishes;
    float scale;

    Hitbox hitbox;

    static Texture2D textures[4]; //3,2,1,0 peces
    static bool texturesLoaded;

public:
    Basket(Vector2 pos, float scale = 2.0f);
    //~Basket();

    static void LoadTexturesOnce();
    static void UnloadTexturesOnce();

    void Draw() const;

    void LoseFish();
    bool IsEmpty() const;

    const Hitbox& GetHitbox() const;
};