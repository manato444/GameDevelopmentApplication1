#pragma once

#include"../GameObject.h"
#include"../Player/Player.h"
#include"../Enemy/Haneteki.h"
#include"../Enemy/Hakoteki.h"
#include"../Bullet/Bullet.h"

class E_Bullet : public GameObject
{
private:

	//移動の速さ
	Vector2D velocity;

	int animation[2];		//アニメーション画像
	int animation_count;	//アニメーション時間
	int flip_flag;			//反転フラグ

	int type;

public:
	E_Bullet();
	~E_Bullet();

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

	//位置情報取得処理
	//Vector2D GetLocation() const;

	//位置情報変更処理
	//void SetLocation(const Vector2D& locartion);

};