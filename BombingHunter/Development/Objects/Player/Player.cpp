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
	//animation[0] = LoadGraph("image/トリパイロット/飛ぶ1.png");
	//animation[1] = LoadGraph("image/トリパイロット/飛ぶ2.png");
	//animation[0] = LoadGraph("image/トリパイロット/Player.bmp");
	//animation[1] = LoadGraph("image/トリパイロット/Player.bmp");

	LoadDivGraph("image/トリパイロット/0.png", 12, 4, 3, 73, 73, img);
	//animation[1] = LoadDivGraph("image/トリパイロット/0.png", 12, 4, 3, 73, 73, img_ch);

	img_cnt = 0;

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("トリパイロットの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//大きさの設定
	scale = 64.0f;

	//初期画像の設定
	image = animation[0];

	//img[0] = animation[0];

	box_size = Vector2D(64.0f);
}

//更新処理
void Player::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimeControl();
}

//描画処理
void Player::Draw()const
{
	//DrawExtendGraph(1, 1, 1, 1, image, FALSE);
	
	//プレイヤー画像の描画
	//DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	DrawRotaGraphF(location.x, location.y, 1.0, radian, img[img_cnt], TRUE, flip_flag);

	__super::Draw();

	//デバッグ用
	/*
#if _DEBUG
	//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (Vector2D(1.0f) *
		(float)scale / 2.0f);

	Vector2D box_collision_lower_right = location + (Vector2D(1.0f) *
		(float)scale / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y,
		GetColor(255, 0, 0), FALSE);

#endif
*/
}

//終了処理
void Player::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);

	DeleteGraph(img[4]);
}

//当たり判定通知処理
void Player::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
}

//移動処理
void Player::Movement()
{
	//移動の速さ
	Vector2D velocity = 0.0f;

	//左右移動
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		velocity.x += -2.0f;
		flip_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x += 2.0f;
		flip_flag = FALSE;
	}
	else if (InputControl::GetKey(KEY_INPUT_UP))
	{
		velocity.y -= 2.0f;
		//flip_flag = FALSE;
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN))
	{
		velocity.y += 2.0f;
		//flip_flag = FALSE;
	}
	else
	{
		velocity.x = 0.0f;
	}

	//現在の位置座標に速さを加算する
	location += velocity;

	//画面外に行かないようにする処理
	if (location.x < (scale / 2.0f + 15))
	{
		velocity.x = 0.0f;
		location.x = scale / 2.0f + 15;
	}
	else if ((416.0f - (scale / 2.0f)) < location.x)
	{
		velocity.x = 0.0f;
		location.x = 416.0f - (scale / 2.0f);
	}
}

//アニメーション制御
void Player::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//10フレーム目に到達したら
	if (animation_count >= 20)
	{
		//カウントリセット
		animation_count = 0;

		img_cnt++;
		if (img_cnt == 4)
		{
			img_cnt = 0;
		}

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
		
	}
}