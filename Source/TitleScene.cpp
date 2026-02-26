#include "TitleScene.h"
#include <DxLib.h>
#include "TitleStage.h"

TitleScene::TitleScene()
{
	//hImage = LoadGraph("data/image/Stage.jpeg");
	hImage = LoadGraph("data/image/taitoru.jpg");
	
	new TitleStage();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	DrawExtendGraph(0, 0, 1280, 720, hImage, TRUE);
	

	int time = GetNowCount();

	if ((time / 700) % 2 == 0) {
		int fsize = SetFontSize(30);


		DrawString(450, 600, "Push [SPACE]Key To Play", fsize  , GetColor(255, 255, 255));
		//DrawString(490, 300, "Forest Athletics",GetColor(0, 255, 0));
	}
	
}
