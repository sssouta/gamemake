#pragma once
#include "Object2D.h"

class Enemy : public Object2D
{
public:

    Enemy(VECTOR2 pos);
    ~Enemy();

    void Update();
    void Draw(int scrollX);

private:

    VECTOR2 position;
    VECTOR2 velocity;

    int hImage;
};