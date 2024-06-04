#include"Player.h"
#include"../../Utility/InputControl.h"
#include"../../Utility/ResourceManager.h"
#include"../../Utility/UserTemplate.h"
#include"DxLib.h"

//コンストラクタ
Player::Player() : animation_count(0),rot(0)
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
	//ローカル変数定義
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	//アニメーションを読み込む
	tmp = rm->GetImages("image/トリパイロット/飛ぶ_1.png");
	animation_data.push_back(tmp[0]);	//アニメーション画像を配列に追加
	tmp = rm->GetImages("image/トリパイロット/飛ぶ_2.png");
	animation_data.push_back(tmp[0]);

	//画像の読み込み(仮)
	//animation[0] = LoadGraph("image/トリパイロット/飛ぶ1.png");
	//animation[1] = LoadGraph("image/トリパイロット/飛ぶ2.png");
	//animation[0] = LoadGraph("image/トリパイロット/Player.bmp");
	//animation[1] = LoadGraph("image/トリパイロット/Player.bmp");

	//LoadDivGraph("image/トリパイロット/0.png", 12, 4, 3, 73, 73, img);
	//animation[1] = LoadDivGraph("image/トリパイロット/0.png", 12, 4, 3, 73, 73, img_ch);

	/*
	tmp = rm->GetImages("image/トリパイロット/0.png", 12, 4, 3, 73, 73);
	for (int i = 0; i < 4; i++)
	{
		animation_data.push_back(tmp[img_cnt]);
		img_cnt++;
	}
	*/
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
	image = animation_data[0];
	//image = animation[0];
	//img[0] = animation[0];

	//大きさ指定
	box_size = Vector2D(64.0f);

	//マウスホイール回転数
	rot = 0;
}

//更新処理
void Player::Update()
{
	SetMouseWheel();	//マウスホイール回転量をセットする
	SetLeftStick();		//左スティックの値をセットする
	SetRightStick();	//右スティックの値をセットする
	SetLeftTrigger();	//左トリガーの値をセットする
	SetRightTrigger();	//右トリガーの値をセットする

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

	//DrawRotaGraphF(location.x, location.y, 1.0, radian, img[img_cnt], TRUE, flip_flag);

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

/* - - - - - - - - - - - - - - - - - - -< XInput >- - - - - - - - - - - - - - - - - - - - - - - - - - - */

	
		//入力情報の取得
	InputControl* input = InputControl::GetInstance();

	int x, y, fontsize, color;

	//描画座標
	x = 0;
	y = 20;

	//変数定義(フォントサイズ)
	fontsize = 18;
	//色
	color = 0xf6ff00;// GetColor(255, 255, 255);
	//フォント
	ChangeFont("ＭＳ 明朝");

	//フォントサイズ設定
	SetFontSize(fontsize);

	DrawFormatString(x, y -= 18, color, "デジタル方向ボタン上... %d", input->GetButton(0));
	DrawFormatString(x, y += fontsize, color, "デジタル方向ボタン下... %d", input->GetButton(1));
	DrawFormatString(x, y += fontsize, color, "デジタル方向ボタン左... %d", input->GetButton(2));
	DrawFormatString(x, y += fontsize, color, "デジタル方向ボタン右... %d", input->GetButton(3));

	DrawFormatString(x, y += fontsize + 18, color, "STARTボタン... %d", input->GetButton(4));
	DrawFormatString(x, y += fontsize, color, "BACKボタン... %d", input->GetButton(5));

	DrawFormatString(x, y += fontsize + 18, color, "左スティック押し込み... %d", input->GetButton(6));
	DrawFormatString(x, y += fontsize, color, "右スティック押し込み... %d", input->GetButton(7));

	DrawFormatString(x, y += fontsize + 18, color, "LBボタン... %d", input->GetButton(8));
	DrawFormatString(x, y += fontsize, color, "RBボタン... %d", input->GetButton(9));

	DrawFormatString(x, y += fontsize + 18, color, "Aボタン... %d", input->GetButton(12));
	DrawFormatString(x, y += fontsize, color, "Bボタン... %d", input->GetButton(13));
	DrawFormatString(x, y += fontsize, color, "Xボタン... %d", input->GetButton(14));
	DrawFormatString(x, y += fontsize, color, "Yボタン... %d", input->GetButton(15));
	DrawFormatString(x, y += fontsize + 18, color, "左トリガー... %.1f", trigger[0]);
	DrawFormatString(x, y += fontsize, color, "右トリガー... %.1f", trigger[1]);

	DrawFormatString(x, y += fontsize + 18, color, "左スティックX... %.1f", float(stick[0].x));
	DrawFormatString(x, y += fontsize, color, "左スティックY... %.1f", float(stick[0].y));

	DrawFormatString(x, y += fontsize, color, "右スティックX... %.1f", float(stick[1].x));
	DrawFormatString(x, y += fontsize, color, "右スティックY... %.1f", float(stick[1].y));
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
	//入力情報の取得
	InputControl* input = InputControl::GetInstance();

	//移動する方向(変数定義)
	Vector2D direction = 0.0f;

	//左右移動
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_A) || input->GetButton(XINPUT_BUTTON_DPAD_LEFT)
		|| stick[0].x < -0.1f || stick[1].x < -0.1f)
	{
		direction.x = -1.0f;
		flip_flag = TRUE;
	}
	else if (input->GetKey(KEY_INPUT_RIGHT) || input->GetKey(KEY_INPUT_D) || input->GetButton(XINPUT_BUTTON_DPAD_RIGHT)
		|| stick[0].x > 0.1f || stick[1].x > 0.1f)
	{
		direction.x = 1.0f;
		flip_flag = FALSE;
	}

	//上下移動
	if (input->GetKey(KEY_INPUT_UP) || input->GetKey(KEY_INPUT_W) || input->GetButton(XINPUT_BUTTON_DPAD_UP)
		|| stick[0].y > 0.1f || stick[1].y > 0.1f)
	{
		direction.y = -1.0f;
	}
	else if (input->GetKey(KEY_INPUT_DOWN) || input->GetKey(KEY_INPUT_S) || input->GetButton(XINPUT_BUTTON_DPAD_DOWN)
		|| stick[0].y < -0.1f || stick[1].y < -0.1f)
	{
		direction.y = 1.0f;
	}
	else
	{
		direction.y = 0.0f;
	}


	//徐々に移動速度を上げる処理(向きによって移動量の加減算を行う)
	if (direction.x != 0.0f)
	{
		float max_speed = Abs<float>((5.0f * 0.5 * direction.x));
		velocity.x += 0.5 * direction.x;
		velocity.x = Min<float>(Max<float>(velocity.x, -max_speed),
			max_speed);
	}
	else
	{
		//徐々に減速して止まる処理
		if (velocity.x < -1e-6f)
		{
			float calc_speed = velocity.x + 0.1;
			velocity.x = Min<float>(calc_speed, 0.0f);
		}
		else if (1e-6f < velocity.x)
		{
			float calc_speed = velocity.x - 0.1f;
			velocity.x = Max<float>(calc_speed, 0.0f);
		}
	}
	if (direction.y != 0.0f)
	{
		float max_speed = Abs<float>((5.0f * 0.5 * direction.y));
		velocity.y += 0.5 * direction.y;
		velocity.y = Min<float>(Max<float>(velocity.y, -max_speed),
			max_speed);
	}
	else
	{
		//徐々に減速して止まる処理
		if (velocity.y < -1e-6f)
		{
			float calc_speed = velocity.y + 0.1;
			velocity.y = Min<float>(calc_speed, 0.0f);
		}
		else if (1e-6f < velocity.y)
		{
			float calc_speed = velocity.y - 0.1f;
			velocity.y = Max<float>(calc_speed, 0.0f);
		}
	}
	//画面外に行かないようにする処理_X
	if (location.x < (box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
		location.x = box_size.x / 2.0f;
	}
	else if ((640.0f - (box_size.x / 2.0f)) < location.x)
	{
		velocity.x = 0.0f;
		location.x = 640.0f - (box_size.x / 2.0f);
	}
	//画面外に行かないようにする処理_Y
	if (location.y < (box_size.y / 2.0f))
	{
		velocity.y = 0.0f;
		location.y = box_size.y / 2.0f;
	}
	else if ((480.0f - (box_size.y / 2.0f)) < location.y)
	{
		velocity.y = 0.0f;
		location.y = 480.0f - (box_size.y / 2.0f);
	}


	//位置情報に速度を加算する
	location += velocity;
}

/*
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
		else{
			image = animation[0];
		}
	}
}
*/

//アニメーション制御
void Player::AnimeControl()
{
	//カウントの更新
	animation_count++;

	//60フレームに到達したら
	if (animation_count >= 60)
	{
		//カウントを0クリアする
		animation_count = 0;

		//画像の切り替えを行う
		if (image == animation_data[0])
		{
			image = animation_data[1];
		}
		else
		{
			image = animation_data[0];
		}
	}
}

/* - - - - - - - - - - - - - - - - - - -< XInput >- - - - - - - - - - - - - - - - - - - - - - - - - - - */

//左スティックの値をセットする
Vector2D Player::SetLeftStick()
{
	//Input入力情報の取得
	InputControl* input = InputControl::GetInstance();

	//左スティック入力値を取得
	stick[0] = input->GetLeftStick();

	return stick[0];
}

//右スティックの値をセットする
Vector2D Player::SetRightStick()
{
	//Input入力情報の取得
	InputControl* input = InputControl::GetInstance();

	//右スティック入力値を取得
	stick[1] = input->GetRightStick();

	return stick[1];
}

//左トリガーの入力値をセットする
float Player::SetLeftTrigger()
{
	//Input入力情報の取得
	InputControl* input = InputControl::GetInstance();

	//左トリガー入力値を取得
	trigger[0] = input->GetLeftTrigger();

	return trigger[0];
}

//右トリガーの入力値をセットする
float Player::SetRightTrigger()
{
	//Input入力情報の取得
	InputControl* input = InputControl::GetInstance();

	//右トリガー入力値を取得
	trigger[1] = input->GetRightTrigger();

	return trigger[1];
}

//マウスホイール回転量をセットする
int Player::SetMouseWheel()
{
	//Input入力情報の取得
	InputControl* input = InputControl::GetInstance();

	//マウスホイール回転量を加算
	rot += input->GetMouseWheel();

	return rot;
}