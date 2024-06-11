#include"Harpie.h"
#include"DxLib.h"

Harpie::Harpie() :
	animation_count(0), flip_flag(FALSE), type(NULL)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Harpie::~Harpie()
{
}

void Harpie::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("image/ハーピー/ハーピー1.png");
	animation[1] = LoadGraph("image/ハーピー/ハーピー2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハーピー画像がありません\n");
	}

	//ui = new UI;
	//location = ui->GetEnemyLocation();

	location.x = 10.0f;
	location.y = 200.0f;

	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 64.0;

	//初期画像の設定
	image = animation[0];

	//当たり判定の大きさ
	box_size = Vector2D(54.0f);

	//速度指定
	velocity = Vector2D(0.3f, 0.0f);
}

void Harpie::Update()
{

	//移動処理
	Movement();

	//アニメーション制御
	AnimeControl();
}

void Harpie::Draw() const
{
	//ハーピー画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
	__super::Draw();

//	//デバッグ用
//#if _DEBUG
//	//当たり判定の可視化
//	Vector2D box_collision_upper_left = location - (Vector2D(1.0f) *
//		(float)scale / 2.0f);
//
//	Vector2D box_collision_lower_right = location + (Vector2D(1.0f) *
//		(float)scale / 2.0f);
//
//	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
//		box_collision_lower_right.x, box_collision_lower_right.y,
//		GetColor(255, 0, 0), FALSE);
//
//#endif
}

void Harpie::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Harpie::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
}

void Harpie::Movement()
{
	flip_flag = FALSE;

	//現在の位置座標に速さを加算する
	location += velocity;
}

void Harpie::AnimeControl()
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

