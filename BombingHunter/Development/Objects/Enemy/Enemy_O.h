/*
#pragma once

#include"../GameObject.h"

//敵キャラクターの最大数
#define MAX_ENEMY_CHARACTOR 20

//敵を出現させるベースクラス
class Enemy_O : public GameObject 
{
private:

	//キャラ出現
	int enemy_popcount;

	//キャラカウント
	int charaCount;	

	int t;

	GameObject** chara;
	class Scene* scene;


public:
	Enemy_O();	//コンストラクタ
	~Enemy_O();	//デストラクタ

	virtual void Initialize() override;		//初期化処理
	virtual void Initialize(class Scene* scene);		//初期化処理
	virtual void Update() override;			//更新処理
	virtual void Draw() const override;		//描画処理
	virtual void Finalize() override;

	void randomchar();	//敵の種類をランダムで決める処理

	int GetCharaCount() { return this->charaCount; }

	GameObject** GetCharacter(int count);

};
*/