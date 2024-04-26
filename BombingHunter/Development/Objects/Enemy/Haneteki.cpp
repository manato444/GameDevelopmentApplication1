#include"Haneteki.h"
#include"DxLib.h"

Haneteki::Haneteki() :
	animation_count(0), flip_flag(FALSE), type(NULL)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Haneteki::~Haneteki()
{
}

void Haneteki::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("image/ハネテキ/1.png");
	animation[1] = LoadGraph("image/ハネテキ/2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハネテキ画像がありません\n");
	}

	
	location.x = 10.0f;
	location.y = 300.0f;
	
	ui = new UI;
	//location = ui->GetEnemyLocation_Type1();

	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 64.0;

	//初期画像の設定
	image = animation[0];
}

void Haneteki::Update()
{

	//移動処理
	Movement();

	//アニメーション制御
	AnimeControl();
}

void Haneteki::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//デバッグ用
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
}

void Haneteki::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Haneteki::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
}

void Haneteki::Movement()
{

	//移動の速さ
	Vector2D velocity = 0.0f;
	
	
	velocity.x += 0.5f;
	flip_flag = FALSE;
	
	/*
	if (type == 1)
	{
		velocity += -2.0f;
		flip_flag = TRUE;
	}
	else if (type == 2)
	{
		velocity += 2.0f;	
		flip_flag = FALSE;
	}
	*/
	

	//現在の位置座標に速さを加算する
	location += velocity;
}

void Haneteki::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントリセット
		animation_count = 0;

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

Vector2D Haneteki::GetLocation() const
{
	return this->location;
}

void Haneteki::SetLocation(const Vector2D& location)
{
	this->location = location;
}

void Haneteki::SetLocation()
{
	if (type == 1)
	{
		location.x = 10.0f;
		location.y = 400.0f;
	}
	else if (type == 2)
	{
		location.x = 600.0f;
		location.y = 400.0f;
	}
}