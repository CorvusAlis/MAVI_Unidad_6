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

    vector<CannonBall>& GetBullets();   //esta version permite modificar las balas - en este caso para manejar que pasa cuando colisiona
    const vector<CannonBall>& GetBullets() const;   //esta version con const se usa solo para ver el estado de las balas
    void CleanBullets();

    void Reset();

    float GetPower() const;
    float GetAngle() const;

};
