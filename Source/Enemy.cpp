#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy(VECTOR2 pos)
{
    position = pos;
    velocity = VECTOR2(-2, 0);   // ç∂Ç…à⁄ìÆ

    hImage = LoadGraph("data/image/Enemy1.png");
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
    // à⁄ìÆ
    position = velocity;

    // âÊñ í[Ç≈îΩì]Åiä»à’AIÅj
    if (position.x < 0) {
        velocity.x *= -1;
    }

    if (position.x > 1280) {
        velocity.x *= -1;
    }
}

void Enemy::Draw()
{
    DrawGraph(position.x - 32, position.y - 32, hImage, TRUE);
}