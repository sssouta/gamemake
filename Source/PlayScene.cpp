#include "PlayScene.h"
#include <DxLib.h>
#include "Stage.h"
#include "Object2D.h"
#include "Player.h"



PlayScene::PlayScene()
{
	hImage = LoadGraph("data/image/mori5.jpg");

	new Stage();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	Player* player = FindGameObject<Player>();
	if (player && player->GetPosition().y > 1200) {
		SceneManager::ChangeScene("GAMEOVER");
	}
}

void PlayScene::Draw()
{
	DrawExtendGraph(0, 0, 1280, 720, hImage, TRUE);
	//DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	//DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}



//コードメモリー　 Code Memory
//スタックメモリー Stack Memory
//ヒープメモリー   Heap Memory
