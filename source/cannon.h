#pragma once
#include "raylib.h"
#include <vector>
#include "cannonball.h"

using namespace std;

class Cannon {
private:
    Vector2 position;
    float scale;
    float angle;
    float power;

    Texture2D texture;
    Vector2 origin;

    vector<CannonBall> cannonballs;

public:
    Cannon(Vector2 pos);
    ~Cannon();

    void Update(float deltaTime);
    void Draw() const;
};
