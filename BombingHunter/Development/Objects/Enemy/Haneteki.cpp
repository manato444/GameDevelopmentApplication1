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
	animation[0] = LoadGraph("image/ハネテキ/ハネテキ1.png");
	animation[1] = LoadGraph("image/ハネテキ/ハネテキ2.png");
	//animation[0] = LoadGraph("image/ハネテキ/Hane.bmp");
	//animation[1] = LoadGraph("image/ハネテキ/Hane.bmp");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハネテキ画像がありません\n");
	}

	
	//location.x = 10.0f;
	//location.y = 300.0f;
	//location = ui->GetEnemyLocation_Type1();

	ui = new UI;
	/*
	type = GetRand(1) + 1;
	if (type == 1)
	{
		//location = ui->SetEnemyLocation_Type1();
		location = One_Type_Location();
	}
	else if (type == 2)
	{
		//location = ui->SetEnemyLocation_Type2();
		location = Two_Type_Location();
	}
	*/
	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 45.0;

	//初期画像の設定
	image = animation[0];

	//移動速度の設定
	velocity = Vector2D(0.5f, 0.0f);

	//当たり判定の大きさ設定
	box_size = Vector2D(45.0f);
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
	__super::Draw();

	/*
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
*/
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
	velocity = 0.0f;
	// Finalize();

	//delete hit_object;
}

void Haneteki::Movement()
{

	//移動の速さ
	//velocity = 0.0f; 
	
	
	//velocity.x += 0.5f;
	flip_flag = FALSE;
	

	/*
	if (type == 1)
	{
		velocity.x += 0.8f;
		flip_flag = FALSE;
	}
	else if (type == 2)
	{
		velocity.x -= 0.8f;	
		flip_flag = TRUE;
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
/*
Vector2D Haneteki::GetLocation() const
{
	return this->location;
}
*/

/*
void Haneteki::SetLocation(const Vector2D& location)
{
	this->location = location;
}
*/
/*
Vector2D Haneteki::One_Type_Location()
{
	return Vector2D(60, 300);
}
Vector2D Haneteki::Two_Type_Location()
{
	return Vector2D(600, 300);
}
*/
/*
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
*/