#include"Hakoteki.h"
#include"DxLib.h"

Hakoteki::Hakoteki():
	animation_count(0), flip_flag(NULL),type(NULL), d_flg(false)
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
	if (animation[0] == -1 || animation[1] == -1){
		throw("ハコテキ画像がありません\n");
	}

	//向きの設定
	radian = 0.0;
	//大きさの設定
	scale = 45.0;
	//初期画像の設定
	image = animation[0];
	//当たり判定の大きさ
	box_size = Vector2D(45.0f);
	//移動速度
	velocity = Vector2D(-0.4f, 0.0f);
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
	//ハコテキの描画
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
void Hakoteki::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Hakoteki::OnHitCollision(GameObject* hit_object)
{
	/* --- 当たった時の処理(判別処理) --- */
	//if (dynamic_cast<Kin*>(hit_object) != nullptr) {
	//	//無視
	//	d_flg = false;
	//}
	//else {
	//	d_flg = false;
	//}
}

//消すかチェックして通知
bool Hakoteki::D_Objects()
{
	return d_flg;
}

//移動処理
void Hakoteki::Movement()
{
	flip_flag = TRUE;

	//現在の位置座標に速さを加算する
	location += velocity;
}

//アニメーション制御
void Hakoteki::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 60){
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

