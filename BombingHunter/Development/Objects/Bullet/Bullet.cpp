#include"Bullet.h"
#include"DxLib.h"

Bullet::Bullet() :
	animation_count(0), flip_flag(FALSE)// type(NULL)
{
	animation[0] = NULL;
	//animation[1] = NULL;
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("image/爆弾/爆弾.png");
	//animation[1] = LoadGraph("image/爆弾/爆弾.png");

	//エラーチェック
	if (animation[0] == -1)//|| animation[1] == -1)
	{
		throw("爆弾の画像がありません\n");
	}


	location.x = 320.0f;
	location.y = 10.0f;

	//ui = new UI;
	//location = ui->GetEnemyLocation_Type1();

	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 64.0;

	//初期画像の設定
	image = animation[0];
}

void Bullet::Update()
{

	//移動処理
	Movement();

	//アニメーション制御
	//AnimeControl();
}

void Bullet::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, PI / 2, image, TRUE, flip_flag);

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

void Bullet::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	//DeleteGraph(animation[1]);
}

void Bullet::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
}

void Bullet::Movement()
{

	//移動の速さ
	Vector2D velocity = 0.0f;


	velocity.y += 0.5f;
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


/*
void Bullet::AnimeControl()
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
*/

Vector2D Bullet::GetLocation() const
{
	return this->location;
}

void Bullet::SetLocation(const Vector2D& location)
{
	this->location = location;
}

void Bullet::SetLocation()
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