#include"Player.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"

//コンストラクタ
Player::Player() : animation_count(0), flip_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//デストラクタ
Player::~Player()
{
}

//初期化処理
void Player::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("");
	animation[1] = LoadGraph("");

	//エラーチェック
	if()
}