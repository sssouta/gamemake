#include "GameOverScene.h"
#include "Stage.h"

GameOverScene::GameOverScene()
{
	hImage = LoadGraph("data/image/mori4.jpg");
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Update()
{
	if (CheckHitKey(KEY_INPUT_Y)) {
		SceneManager::ChangeScene("TITLE");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void GameOverScene::Draw()
{
	DrawExtendGraph(0, 0, 1280, 720, hImage, TRUE);
	int rsize = SetFontSize(50);
	//DrawString(450, 200, "ゲームオーバー", rsize, GetColor(255, 255, 0));
	int time = GetNowCount();
	if ((time / 700) % 2 == 0) {
		DrawString(500, 300, "Game Over", GetColor(255, 0, 0));
		DrawString(390, 600, "Push [Y]Key To Title", GetColor(140, 10, 10));
	}
	
}
