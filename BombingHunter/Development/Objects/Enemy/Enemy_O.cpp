/********************************
	要らないかも

#include"Hakoteki.h"
#include"Haneteki.h"
#include"Harpie.h"
#include"Kin.h"
#include"DxLib.h"
#include"Enemy_O.h"
#include"../../Scene/Scene.h"

Enemy_O::Enemy_O() :
	enemy_popcount(0),
	charaCount(0)
{
}

Enemy_O::~Enemy_O()
{
}

//初期化
void Enemy_O::Initialize()
{
	enemy_popcount = 0;
	charaCount = 0;
	
	chara = new GameObject * [MAX_ENEMY_CHARACTOR];
	for (int i = 0; i < MAX_ENEMY_CHARACTOR; i++)
	{
		chara[i] = nullptr;
	}
	
}

void Enemy_O::Initialize(Scene* scene) 
{
	this->scene = scene;
}

//更新処理
void Enemy_O::Update()
{
	//だいたい2秒ごとに出現させる
	if (enemy_popcount >= 250)
	{
		t = GetRand(1)+ 1;
		randomchar();//敵の種類をランダムで決める
		enemy_popcount = 0;	
	}
	else
	{
		enemy_popcount++;
	}

	for (charaCount = 0; charaCount < MAX_ENEMY_CHARACTOR; charaCount++)
	{
		if (chara[charaCount] == nullptr)
		{
			break;
		}
		//敵の出現位置をタイプで取得 :(例){type = 1 : 左端出現　type = 2 : 右端出現}
		
		/*
		if (t == 1)
		{
			chara[charaCount]->SetType(1);
		}
		else if (t == 2)
		{
			chara[charaCount]->SetType(2);
		}
		*//*
		chara[charaCount]->Update();
	}
}

//描画
void Enemy_O::Draw() const
{
	//最大数までキャラを描画させる
	for (int i = 0; i < MAX_ENEMY_CHARACTOR; i++)
	{
		if (chara[i] == nullptr)
		{
			break;
		}
		chara[i]->Draw();
	}
}

//終了
void Enemy_O::Finalize()
{
}

//敵の種類をランダムで決める
void Enemy_O::randomchar()
{

	//1から100までの乱数を取得
	int num = rand() % 100 + 1;

	if (num <= 60)
	{
		if (charaCount < MAX_ENEMY_CHARACTOR && chara[charaCount] == nullptr)
		{
			//ハネテキ
			chara[charaCount] = this->scene->CreateObject<Haneteki>(Vector2D());
			chara[charaCount]->Initialize();
		}
	}
	else if (num <= 75)
	{
		if (charaCount < MAX_ENEMY_CHARACTOR && chara[charaCount] == nullptr)
		{

			//ハコテキ
			chara[charaCount] = this->scene->CreateObject<Hakoteki>(Vector2D());
			chara[charaCount]->Initialize();
		}
	}
	else if (num <= 90)
	{
		if (charaCount < MAX_ENEMY_CHARACTOR && chara[charaCount] == nullptr)
		{
			//ハーピー
			chara[charaCount] = this->scene->CreateObject<Harpie>(Vector2D());
			chara[charaCount]->Initialize();
		}
	}
	else
	{
		if (charaCount < MAX_ENEMY_CHARACTOR && chara[charaCount] == nullptr)
		{
			//金のテキ
			chara[charaCount] = this->scene->CreateObject<Kin>(Vector2D());
			chara[charaCount]->Initialize();
		}
	}
}

//キャラクター取得
GameObject** Enemy_O::GetCharacter(int count)
{
	return chara;
}
*********************************/