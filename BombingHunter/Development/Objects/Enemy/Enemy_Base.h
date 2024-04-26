#pragma once

#include"../GameObject.h"

//敵キャラクターの最大数
#define MAX_ENEMY_CHARACTOR 500

//敵を出現させるベースクラス
class Enemy_B : public GameObject 
{
private:

	//キャラ出現
	int enemy_popcount;

	//キャラカウント
	int charaCount;	

	int t;

	GameObject** chara;



public:
	Enemy_B();	//コンストラクタ
	~Enemy_B();	//デストラクタ

	virtual void Initialize() override;		//初期化処理
	virtual void Update() override;			//更新処理
	virtual void Draw() const override;		//描画処理
	virtual void Finalize() override;

	void randomchar();	//敵の種類をランダムで決める処理

	int GetCharaCount() { return this->charaCount; }

	GameObject** GetCharacter(int count);

};