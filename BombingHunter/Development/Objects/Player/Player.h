#pragma once


#include"../GameObject.h"
#include"../Bullet/Bullet.h"
#include<vector>

class Player : public GameObject
{
private:
	Vector2D velocity;	//加速度
	std::vector<int> animation_data;	//アニメーションデータ

private:

	int animation[2];		//アニメーション画像
	int animation_count;	//アニメーション時間
	//int flip_flag;			//反転フラグ
	int img_ch[2];
	int img[12];
	int img_cnt;
	//int d_flg;
	//Vector2D locaiton;

public:
	Player();
	virtual ~Player();

	//純粋仮想関数(オーバーライドをして上書きする)
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;
	
	//virtual bool D_Objects() override;

private:
	Vector2D stick[2];	//スティック入力値 = { stick[0]:左スティック, stick[1]:右スティック }
	float trigger[2];	//トリガ－入力値 = { trigger[0]:左トリガー, trigger[1]:右トリガー }

	int rot;

public:

	Vector2D SetLeftStick(); //左スティックの値をセットする
	Vector2D SetRightStick();//右スティックの値をセットする

	float SetLeftTrigger();	//左トリガーの入力値をセットする
	float SetRightTrigger();//右トリガーの入力値をセットする

	int SetMouseWheel();	//マウスホイール回転量をセットする


private:
	//移動処理
	void Movement();

	//アニメーション制御
	void AnimeControl();

};