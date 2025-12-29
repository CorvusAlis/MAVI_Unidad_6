#include "basket.h"

//carga y descarga de texturas
Texture2D Basket::textures[4];
bool Basket::texturesLoaded = false;

void Basket::LoadTexturesOnce()
{
    if (texturesLoaded) return;

    textures[3] = LoadTexture("assets/img/basket_3F.png");
    textures[2] = LoadTexture("assets/img/basket_2F.png");
    textures[1] = LoadTexture("assets/img/basket_1F.png");
    textures[0] = LoadTexture("assets/img/basket_empty.png");

    texturesLoaded = true;
}

void Basket::UnloadTexturesOnce()
{
    for (int i = 0; i < 4; ++i)
    {
        if (textures[i].id != 0)
            UnloadTexture(textures[i]);
    }
}

Basket::Basket(Vector2 pos, float sc)
    : position(pos),
    fishes(3),
    scale(sc),
    hitbox()
{
    const Texture2D& tex = textures[3];
}

void Basket::Draw() const
{
    const Texture2D& tex = textures[fishes];

    Rectangle src = {
        0, 0,
        (float)tex.width,
        (float)tex.height
    };

    Rectangle dst = {
        position.x,
        position.y,
        tex.width * scale,
        tex.height * scale
    };

    DrawTexturePro(
        tex,
        src,
        dst,
        { 0, 0 },
        0.0f,
        WHITE
    );

    //hitbox.Draw();
}

void Basket::Init()
{
    const Texture2D& tex = textures[3];

    hitbox = Hitbox(
        tex.width * scale * 0.9f,
        tex.height * scale * 0.9f,
        {
            tex.width * scale * 0.05f,
            tex.height * scale * 0.05f
        },
        true //debug ON
    );

    hitbox.Sincro(position);
}

void Basket::LoseFish() //controlo la cantidad de peces
{
    if (fishes > 0)
        fishes--;
}

bool Basket::IsEmpty() const
{
    return fishes == 0;
}

void Basket::Reset()
{
    fishes = 3;
}

Vector2 Basket::GetPosition() const { return position; }
float Basket::GetWidth() const { return textures[fishes].width * scale; }

const Hitbox& Basket::GetHitbox() const
{
    return hitbox;
}
