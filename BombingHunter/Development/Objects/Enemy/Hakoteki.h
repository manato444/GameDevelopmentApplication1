#pragma once
#include"../GameObject.h"
#include"../UI/UI.h"
#include"../../Scene/Scene.h"

class Hakoteki : public GameObject
{
protected:


private:
	Vector2D velocity;

	int animation[2];		//アニメーション画像
	int animation_count;	//アニメーション時間
	int flip_flag;			//反転フラグ
	int type;				//出現タイプ
	int d_flg;				//削除フラグ


public:
	Hakoteki();		//コンストラクタ
	~Hakoteki();	//デストラクタ

	virtual void Initialize() override;		//初期化処理
	virtual void Update() override;			//更新処理
	virtual void Draw() const override;		//描画処理
	virtual void Finalize() override;

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;
	virtual bool D_Objects() override;

	Vector2D One_Type_Location();
	Vector2D Two_Type_Location();

private:
	//移動処理
	void Movement();

	//アニメーション制御
	void AnimeControl();

};