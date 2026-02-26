#pragma once
#include "Object2D.h"

class Player : public Object2D {
public:
	Player();
	Player(VECTOR2 pos);
	~Player();
	void Update() override;
	void Draw() override;
	VECTOR2 GetPosition() const;
	

	
private:
	
	float velocityY;
	bool onGround;
	bool prevPushed;

	float Gravity;
	float JumpHeight;
	float JumpV0;
	float moveSpeed;
	float animTimer;         // アニメーション時間用タイマー
	float animInterval;      // フレームの切り替え間隔（秒）
	int prevTime = GetNowCount();
	

	
	
};