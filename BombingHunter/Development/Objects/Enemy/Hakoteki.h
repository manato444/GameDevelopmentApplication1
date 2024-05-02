#pragma once
#include"../GameObject.h"
#include"../UI/UI.h"

class Hakoteki : public GameObject
{
protected:


private:
	Vector2D velocity;
	Vector2D location;	//位置情報
	//UI* ui;				//UI

	int animation[2];		//アニメーション画像
	int animation_count;	//アニメーション時間
	int flip_flag;			//反転フラグ
	int type;				//出現タイプ


public:
	Hakoteki();		//コンストラクタ
	~Hakoteki();	//デストラクタ

	virtual void Initialize() override;		//初期化処理
	virtual void Update() override;			//更新処理
	virtual void Draw() const override;		//描画処理
	virtual void Finalize() override;

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

	Vector2D One_Type_Location();
	Vector2D Two_Type_Location();

private:
	//移動処理
	void Movement();

	//アニメーション制御
	void AnimeControl();

	//位置情報取得処理
	Vector2D GetLocation() const;

	//位置情報変更処理
	void SetLocation(const Vector2D& locartion);

	virtual void SetType(int type) override;

};