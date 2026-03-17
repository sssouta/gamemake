#include "Player.h"
#include <assert.h>
#include "Stage.h"
#include "../ImGui/imgui.h"
#include "CsvReader.h"
#include <time.h>
#include <windows.h>

Player::Player() : Player(VECTOR2(100, 200))
{
}

Player::Player(VECTOR2 pos)
{
	CsvReader* csv = new CsvReader("data/playerParam.csv");
	for (int i = 0; i < csv->GetLines(); i++) {
		std::string tag = csv->GetString(i, 0);
		if (tag == "Gravity") {
			Gravity = csv->GetFloat(i, 1);
		}
		else if (tag == "JumpHeight") {
			JumpHeight = csv->GetFloat(i, 1);
		}
		else if (tag == "MoveSpeed") {
			moveSpeed = csv->GetFloat(i, 1);
		}
		else if (tag == "HP") {
			maxHp = csv->GetFloat(i, 1);
			hp = maxHp;
		}
	}

	JumpV0 = -sqrtf(2.0f * Gravity * JumpHeight);

	hImage = LoadGraph("data/image/tamadot.png");
	assert(hImage > 0);

	imageSize = VECTOR2(64, 64);
	anim = 1;
	animY = 1;
	animTimer = 0.0f;
	animInterval = 0.1f;

	position = pos;
	velocityY = 0.0f;
}

Player::~Player()
{
	DeleteGraph(hImage);
}

void Player::Update()
{
	if (damageTimer > 0) {
		damageTimer--;
	}
	Stage* st = FindGameObject<Stage>();

	if (CheckHitKey(KEY_INPUT_D)) {

		position.x += moveSpeed;

		int push = st->CheckRight(position + VECTOR2(24, -31));
		position.x -= push;

		push = st->CheckRight(position + VECTOR2(24, 31));
		position.x -= push;

		// ===== アニメーション =====
		animTimer += 1.0f / 150.0f;

		if (animTimer >= animInterval) {
			animTimer = 0;
			anim = (anim + 1) % 4; // 4コマ歩き
		}

		animY =3; // 右向き
	}

	if (CheckHitKey(KEY_INPUT_A)) {

		position.x -= moveSpeed;

		int push = st->CheckLeft(position + VECTOR2(-24, -31));
		position.x += push;

		push = st->CheckLeft(position + VECTOR2(-24, 31));
		position.x += push;

		// ===== アニメーション =====
		animTimer += 1.0f / 150.0f;

		if (animTimer >= animInterval) {
			animTimer = 0;
			anim = (anim + 1) % 4;
		}

		animY = 1; // 左向き
	}

	if (onGround) {
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			if (prevPushed == false) {
				velocityY = JumpV0;
			}
			prevPushed = true;
		}
		else {
			prevPushed = false;
		}
	}

	position.y += velocityY;
	velocityY += Gravity;
	onGround = false;

	if (velocityY < 0.0f) {
		int push = st->CheckUp(position + VECTOR2(-24, -31));
		if (push > 0) {
			velocityY = 0.0f;
			position.y += push;
		}
		push = st->CheckUp(position + VECTOR2(24, -31));
		if (push > 0) {
			velocityY = 0.0f;
			position.y += push;
		}
	}
	else {
		int push = st->CheckDown(position + VECTOR2(-24, 32 + 1));
		if (push > 0) {
			velocityY = 0.0f;
			onGround = true;
			position.y -= push - 1;
		}
		push = st->CheckDown(position + VECTOR2(24, 32 + 1));
		if (push > 0) {
			velocityY = 0.0f;
			onGround = true;
			position.y -= push - 1;
		}
	}

	// プレイヤーの表示位置が、400よりも右だったら、スクロールする
	if (st != nullptr) {
		float drawX = position.x - st->ScrollX(); // これが表示座標
		static const int RightLimit = 400;
		static const int LeftLimit = 400;
		if (drawX > RightLimit) {
			st->SetScrollX(position.x - RightLimit);
		}
		else if (drawX < LeftLimit) {
			st->SetScrollX(position.x - LeftLimit);
		}
	}

	VECTOR2 offsets[] = {
VECTOR2(-24, -32),
VECTOR2(0,   -40),
VECTOR2(24,  -32),

VECTOR2(-40, 0),
VECTOR2(40,  0),

VECTOR2(-24, 40),
VECTOR2(0,   40),
VECTOR2(24,  40),
	};

VECTOR2 spikeOffsets[] = {
	VECTOR2(-10, 20),
	VECTOR2(10, 20)
};

	// === チップ8：トゲ（罠）===
	for (const auto& offset : spikeOffsets) {
		VECTOR2 checkPos = position + offset;
		int chip = st->GetChip(checkPos);

		if (chip == 8) {

			if (damageTimer <= 0) {

				hp -= 5;
				damageTimer = 60;

				if (hp <= 0) {
					SceneManager::ChangeScene("GAMEOVER");
					return;
				}
			}

			break;
		}
	}

	// === チップ10：ゲームクリア ===
	for (const auto& offset : offsets) {
		VECTOR2 checkPos = position + offset;
		int chip = st->GetChip(checkPos);

		if (chip == 10) {
			st->RemoveChip(checkPos);
			SceneManager::ChangeScene("GAMECLEAR");
			return;
		}
	}
}

void Player::Draw()
{
	Object2D::Draw();
	Stage* st = FindGameObject<Stage>();

	float x = position.x - st->ScrollX();

	int srcX = anim * (int)imageSize.x;
	int srcY = animY * (int)imageSize.y;

	DrawRectGraph(
		(int)(x - imageSize.x / 2),
		(int)(position.y - imageSize.y / 2),
		srcX, srcY,
		(int)imageSize.x, (int)imageSize.y,
		hImage, TRUE);

	float hpRate = hp / maxHp;

	DrawBox(50, 50, 50 + 200 * hpRate, 70, GetColor(255, 0, 0), TRUE);
	DrawBox(50, 50, 250, 70, GetColor(255, 255, 255), FALSE);

	if (damageTimer > 0) {
		if ((damageTimer / 5) % 2 == 0) {
			return;
		}
	}
}

VECTOR2 Player::GetPosition() const
{
	return position;
}
