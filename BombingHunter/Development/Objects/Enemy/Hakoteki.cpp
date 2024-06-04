#include"Hakoteki.h"
#include"DxLib.h"

Hakoteki::Hakoteki():
	animation_count(0), flip_flag(NULL),type(NULL)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Hakoteki::~Hakoteki()
{
}

//初期化処理
void Hakoteki::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("image/ハコテキ/ハコテキ_1.png");
	animation[1] = LoadGraph("image/ハコテキ/ハコテキ_2.png");
	//animation[0] = LoadGraph("image/ハコテキ/Hako.bmp");
	//animation[1] = LoadGraph("image/ハコテキ/Hako.bmp");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハコテキ画像がありません\n");
	}

	//出現タイプを乱数で取得(スポーン位置の設定)
	type = GetRand(1) + 1;

	if (type == 1)	{
		//スポーン位置を【左】に設定
		location = One_Type_Location();
	}
	else if (type == 2){
		//スポーン位置を【右】に設定
		location = Two_Type_Location();
	}
	
	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 64.0;

	//初期画像の設定
	image = animation[0];
	
	//当たり判定の大きさ
	box_size = 64.0f;

}

void Hakoteki::Update()
{

	//移動処理
	Movement();

	//アニメーション制御
	AnimeControl();
}

void Hakoteki::Draw() const
{
	
	//画像の描画	
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//__super::Draw();
	
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

//終了時処理
void Hakoteki::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Hakoteki::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	velocity = 0.0f;
	location = location;
}

//移動処理
void Hakoteki::Movement()
{
	//移動の速さ
	velocity = 0.0f;

	if (type == 1) 	//タイプ1なら右方向に移動させる
	{
		velocity.x += 0.3f;
		flip_flag = FALSE;
	}
	else if (type == 2) //タイプ2なら左方向に移動させる
	{
		velocity.x -= 0.3f;
		flip_flag = TRUE;
	}
	
	//画面の外に行ったら無理やり見えなくする(仮)
	if (location.x < (scale / scale) - scale / 2.0f)
	{
		velocity.x = 0.0f;	//停止させる
		location.x = scale *(-scale);	//画面外に無理やりどかす（仮）
		DeleteGraph(image);		//画像の削除
	}
	else if ((640.0f + scale) < location.x)
	{
		velocity.x = 0.0f;
		location.x = 640.0f + (scale * 2);
		DeleteGraph(image);	
	}
	
	//現在の位置座標に速さを加算する
	location += velocity;
}

//アニメーション制御
void Hakoteki::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0]){

			image = animation[1];
		}
		else{

			image = animation[0];
		}
	}
}

//位置情報取得(ゲット)
Vector2D Hakoteki::GetLocation() const
{
	return this->location;
}

//位置変更処理(セット)
void Hakoteki::SetLocation(const Vector2D& location)
{
	this->location = location;
}

//キャラタイプをセット
void Hakoteki::SetType(int type)
{
	this->type = type;
}

//出現パターンをセット(タイプ1 : 左から出現させる)
Vector2D Hakoteki::One_Type_Location()
{
	return Vector2D(60, 400);
}
//出現パターンをセット(タイプ2 : 右から出現させる)
Vector2D Hakoteki::Two_Type_Location()
{
	return Vector2D(600, 400);
}
