#include"Bullet.h"
#include"DxLib.h"
#include"../Effect/Effect.h"
#include"../../Scene/Scene.h"
#include"../../Utility/ResourceManager.h"

Bullet::Bullet() :
	animation_count(0), flip_flag(NULL), animation_data()// type(NULL)
{
	animation[0] = NULL;
	//animation[1] = NULL;
}
//デストラクタ
Bullet::~Bullet()
{
}
//初期化処理
void Bullet::Initialize()
{
	//画像の読み込み-----種類別変えたいときに使う
	//animation[0] = LoadGraph("image/爆弾/ミサイル.png");
	//animation[0] = LoadGraph("image/爆弾/meteor.png");
	//animation[0] = LoadGraph("image/爆弾/Bullet.bmp");
	//animation[0] = LoadGraph("image/爆弾/bl1.png");
	//animation[1] = LoadGraph("image/爆弾/bl2.png");

	//ローカル変数定義
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	//アニメーションを読み込む
	tmp = rm->GetImages("image/爆弾/ミサイル.png");
	animation_data.push_back(tmp[0]);	//アニメーション画像を配列に追加
	tmp = rm->GetImages("image/爆弾/ミサイル.png");
	animation_data.push_back(tmp[0]);

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("爆弾の画像がありません\n");
	}
	
	//ui = new UI;
	//location = ui->GetEnemyLocation_Type1();

	//向きの設定
	radian = DX_PI_F / 2;

	//大きさの設定
	scale = 25.0;

	//初期画像の設定
	image = animation_data[0];

	//当たり判定の大きさ
	box_size = Vector2D(25.0f, 28.0f);

	//移動速度の設定
	velocity = Vector2D(0.0f, 1.5f);
}
//更新処理
void Bullet::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimeControl();
}
//描画処理
void Bullet::Draw() const
{

	//Bullet画像の描画
	//DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
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
}
//終了時処理
void Bullet::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation_data[0]);
	DeleteGraph(animation_data[1]);
}
//当たったこと通知(hit_object)
void Bullet::OnHitCollision(GameObject* hit_object)
{
	/* --- 当たった時の処理(判別処理) --- */
	if (dynamic_cast<Haneteki*>(hit_object) != nullptr) {
		//Hanetekiなら削除処理を通知 & エフェクト生成を通知
		d_flg = true;
		e_flg = true;
	}
	else if (dynamic_cast<Hakoteki*>(hit_object) != nullptr) {
		//Hanetekiなら削除処理を通知 & エフェクト生成を通知
		d_flg = true;
		e_flg = true;
	}
	else if (dynamic_cast<Harpie*>(hit_object) != nullptr) {
		//Hanetekiなら削除処理を通知 & エフェクト生成を通知
		d_flg = true;
		e_flg = true;
	}
	else if (dynamic_cast<Kin*>(hit_object) != nullptr) {
		//Hanetekiなら削除処理を通知 & エフェクト生成を通知
		d_flg = true;
		e_flg = true;
	}
	else if (dynamic_cast<Bullet*>(hit_object) != nullptr) {
		//Bulletなら当たり判定を無視
		d_flg = false;
	}
	else if (dynamic_cast<Player*>(hit_object) != nullptr) {
		//Playerなら当たり判定を無視
		d_flg = false;
	}
	else{
		d_flg = false;
		e_flg = false;
	}
}
//消すかチェックして通知
bool Bullet::D_Objects()
{
	return d_flg;
}
//エフェクトを生成するか
bool Bullet::E_Effect()
{
	return e_flg;
}

//移動処理
void Bullet::Movement()
{
	flip_flag = FALSE;
	//現在の位置座標に速さを加算する
	location += velocity;
	//location.x += 1;

	//フレームカウントを加算する
	animation_count++;
	//1フレームごとに回転させる
	if (animation_count >= 3)
	{
		//カウントリセット
		animation_count = 0;
			radian += DX_PI_F / 60;
	}
	
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