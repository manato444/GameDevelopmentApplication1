#include"Haneteki.h"
#include"DxLib.h"

//コンストラクタ
Haneteki::Haneteki() :
	animation_count(0), flip_flag(FALSE), type(NULL)
{
	animation[0] = NULL;
	animation[1] = NULL;
}
//デストラクタ
Haneteki::~Haneteki()
{
}
//初期化処理
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
//更新処理
void Haneteki::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();
}
//描画処理
void Haneteki::Draw() const
{
	//ハネテキ画像の描画
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
//終了時処理
void Haneteki::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}
//当たり判定通知処理
void Haneteki::OnHitCollision(GameObject* hit_object)
{
	/* --- 当たった時の処理(判別処理) --- */
	//if (dynamic_cast<Bullet*>(hit_object) != nullptr){
	//	//Bulletなら削除を通知する
	//	d_flg = true;
	//}
	//else if (dynamic_cast<Haneteki*>(hit_object) != nullptr){
	//	//自分なら無視
	//	d_flg = false;
	//}
	//else {
	//	d_flg = false;
	//}
}


//消すかチェックして通知
//bool Haneteki::D_Objects()
//{
//	return d_flg;
//}

//移動処理
void Haneteki::Movement()
{
	flip_flag = TRUE;

	//現在の位置座標に速さを加算する
	location += velocity;
}
//アニメーション制御
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

//無関係
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