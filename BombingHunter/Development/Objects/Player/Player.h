#pragma once


#include"../GameObject.h"
#include"../Bullet/Bullet.h"

class Player : public GameObject
{
private:

	int animation[2];		//アニメーション画像
	int animation_count;	//アニメーション時間
	int flip_flag;			//反転フラグ

public:
	Player();
	~Player();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//移動処理
	void Movement();

	//アニメーション制御
	void AnimeControl();

	//Vector2D GetLocation();
};