#include"Effect.h"
#include"../../Utility/InputControl.h"
#include"../../Utility/ResourceManager.h"
#include"../../Utility/UserTemplate.h"
#include"DxLib.h"

//コンストラクタ
Effect::Effect() : animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
}
//デストラクタ
Effect::~Effect()
{
}
//初期化処理
void Effect::Initialize()
{
	//ローカル変数定義
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	//アニメーションを読み込む
	tmp = rm->GetImages("image/爆風/爆風1.png");
	animation_data.push_back(tmp[0]);	//アニメーション画像を配列に追加
	tmp = rm->GetImages("image/爆風/爆風2.png");
	animation_data.push_back(tmp[0]);
	tmp = rm->GetImages("image/爆風/爆風3.png");
	animation_data.push_back(tmp[0]);

	//向きの設定
	radian = 0.0f;
	//大きさの設定
	scale = 64.0f;
	//初期画像の設定
	image = animation_data[0];
}
//更新処理
void Effect::Update()
{
	Movement();	//移動

	AnimeControl();	//アニメーション制御
}
//描画処理
void Effect::Draw() const
{
	__super::Draw();
}
//終了時処理
void Effect::Finalize()
{
	//使用した画像を解放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
}
//移動処理
void Effect::Movement()
{
}
//アニメーション制御
void Effect::AnimeControl()
{
	//カウントの更新
	animation_count++;
		//60フレームに到達したら
		if (animation_count >= 60) {
			
			//カウントを0クリアする
			animation_count = 0;

			//画像の切り替えを行う
			if (image == animation_data[0]) {
				image = animation_data[1];
			}
			else if (image == animation_data[1]) {
				image = animation_data[2];
			}
			else {
				image = animation_data[0];
			}
		}
}

//当たり判定通知処理
void Effect::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理

}