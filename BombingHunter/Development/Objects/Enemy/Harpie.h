#pragma once

#include"../GameObject.h"
#include"../UI/UI.h"

class Harpie : public GameObject
{
protected:


private:

	Vector2D velocity;
	std::vector<int> animation_data;	//アニメーションデータ
	UI* ui;

	int animation[2];		//アニメーション画像
	int animation_count;	//アニメーション時間
	int flip_flag;			//反転フラグ

	//敵かプレイヤーか{ 1:プレイヤー, 2: 敵 }
	int type;

public:
	Harpie();
	~Harpie();

	virtual void Initialize() override;		//初期化処理
	virtual void Update() override;			//更新処理
	virtual void Draw() const override;		//描画処理
	virtual void Finalize() override;

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//移動処理
	void Movement();

	//アニメーション制御
	void AnimeControl();



};