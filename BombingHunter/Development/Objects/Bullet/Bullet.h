#pragma once

#include"../GameObject.h"
#include"../Player/Player.h"
#include"../../Scene/Scene.h"

class Bullet : public GameObject
{
private:

	//移動の速さ
	Vector2D velocity;

	int animation[2];		//アニメーション画像
	int animation_count;	//アニメーション時間
	int flip_flag;			//反転フラグ

	int flg;  //オブジェクト削除フラグ
	int type; //なにこれ

public:
	Bullet();
	~Bullet();

	virtual void Initialize() override;	//初期化処理
	virtual void Update() override;		//更新処理
	virtual void Draw() const override;	//描画処理
	virtual void Finalize() override;	//終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;
	virtual bool D_Objects() override;
	//virtual bool C_DeleteObject(bool flg) override;

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