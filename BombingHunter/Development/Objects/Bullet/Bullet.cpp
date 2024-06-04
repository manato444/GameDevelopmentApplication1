#include"Bullet.h"
#include"DxLib.h"

Bullet::Bullet() :
	animation_count(0), flip_flag(NULL)// type(NULL)
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
	animation[0] = LoadGraph("image/爆弾/ミサイル.png");
	//animation[0] = LoadGraph("image/爆弾/Bullet.bmp");
	//animation[0] = LoadGraph("image/爆弾/bl1.png");
	//animation[1] = LoadGraph("image/爆弾/bl2.png");


	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("爆弾の画像がありません\n");
	}
	
	//ui = new UI;
	//location = ui->GetEnemyLocation_Type1();

	//向きの設定
	radian = DX_PI_F;

	//大きさの設定
	scale = 30.0;

	//初期画像の設定
	image = animation[0];

	//当たり判定の大きさ
	box_size = Vector2D(40.0f, 40.0f);
}

void Bullet::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimeControl();
}

void Bullet::Draw() const
{

	//Bullet画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
	//__super::Draw();

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

void Bullet::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Bullet::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	//velocity = 0.0f;
}

void Bullet::Movement()
{
	velocity = 0.0f;

	//radian += DX_PI_F / 2;
	velocity.y += 0.7f;
	flip_flag = FALSE;
	//flip_flag = TRUE;
	//radian = DX_PI_F / 60;

	//フレームカウントを加算する
	animation_count++;

	//1フレームごとに回転させる
	
	if (animation_count >= 3)
	{
		//カウントリセット
		animation_count = 0;
			radian += DX_PI_F / 180;
	}
	

	//現在の位置座標に速さを加算する
	location += velocity;
	/*
	if (flip_flag == FALSE)
	{
	location += velocity.x += 0.5f;
	}
	else if(flip_flag == TRUE)
	{
		location -= velocity.x -= 0.5f;
	}
	*/
}

/*
Vector2D Bullet::GetLocation() const
{
	return this->location;
}

void Bullet::SetLocation(const Vector2D& location)
{
	this->location = location;
}
*/

//アニメーション制御
void Bullet::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 20)
	{
		//カウントリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0]) {

			image = animation[1];
		}
		else {

			image = animation[0];
		}
	}
}