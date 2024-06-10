#pragma once


#include"../GameObject.h"
#include"../Bullet/Bullet.h"
#include<vector>

class Effect : public GameObject
{
private:
	Vector2D velocity;	//加速度
	std::vector<int> animation_data;	//アニメーションデータ

private:

	int animation[3];		//アニメーション画像
	int animation_count;	//アニメーション時間
	//int flip_flag;			//反転フラグ
	int img_ch[2];
	int img[12];
	int img_cnt;

public:
	Effect();
	virtual ~Effect();

	//純粋仮想関数(オーバーライドをして上書きする)
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

};