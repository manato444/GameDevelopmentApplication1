#include"Kin.h"
#include"DxLib.h"

Kin::Kin() :
	animation_count(0), flip_flag(FALSE), type(NULL)
{
	
	for (int i = 0; i < 5; i++)
	{
	animation[i] = NULL;
	}
	

}

Kin::~Kin()
{
}

void Kin::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("image/金のテキ/1.png");
	animation[1] = LoadGraph("image/金のテキ/2.png");
	animation[2] = LoadGraph("image/金のテキ/3.png");
	animation[3] = LoadGraph("image/金のテキ/4.png");
	animation[4] = LoadGraph("image/金のテキ/5.png");


	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1 || animation[4] == -1)
	{
		throw("金のテキ画像がありません\n");
	}

	//ui = new UI;
	//location = ui->GetEnemyLocation();

	location.x = 630.0f;
	location.y = 400.0f;

	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 64.0;

	//初期画像の設定
	image = animation[0];
}

void Kin::Update()
{

	//移動処理
	Movement();

	//アニメーション制御
	AnimeControl();
}

void Kin::Draw() const
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

void Kin::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Kin::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
}

void Kin::Movement()
{

	//移動の速さ
	Vector2D velocity = 0.0f;
	velocity.x -= 1.0f;
	flip_flag = TRUE;

	/*
	if (type == 1)
	{

		SetLocation();

		velocity += -2.0f;
		flip_flag = TRUE;
	}
	else if (type == 2)
	{

		SetLocation();

		velocity += 2.0f;
		flip_flag = FALSE;
	}
	*/
	//現在の位置座標に速さを加算する
	location += velocity;
}

void Kin::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントリセット
		animation_count = 0;

		//画像の切り替え(ゴリ押し)
		if (image == animation[0])
		{
			image = animation[1];
		}
		else if(image == animation[1])
		{
			image = animation[2];
		}
		else if (image == animation[2])
		{
			image = animation[3];
		}
		else if (image == animation[3])
		{
			image = animation[4];
		}
		else
		{
			image = animation[1];
		}
	}
}

Vector2D Kin::GetLocation() const
{
	return this->location;
}

void Kin::SetLocation(const Vector2D& location)
{
	this->location = location;
}

void Kin::SetLocation()
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