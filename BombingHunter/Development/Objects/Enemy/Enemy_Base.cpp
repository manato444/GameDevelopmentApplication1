#include"Hakoteki.h"
#include"Haneteki.h"
#include"Harpie.h"
#include"Kin.h"
#include"DxLib.h"
#include"Enemy_Base.h"

Enemy_B::Enemy_B() :
	enemy_popcount(0),
	charaCount(0)
{
	chara = new GameObject * [MAX_ENEMY_CHARACTOR];
	for (int i = 0; i < MAX_ENEMY_CHARACTOR; i++)
	{
		chara[i] = nullptr;
	}
}

Enemy_B::~Enemy_B()
{
}

//初期化
void Enemy_B::Initialize()
{
	enemy_popcount = 0;
	charaCount = 0;
}

//更新処理
void Enemy_B::Update()
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
		*/
		chara[charaCount]->Update();
	}
}

//描画
void Enemy_B::Draw() const
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
void Enemy_B::Finalize()
{
}

//敵の種類をランダムで決める
void Enemy_B::randomchar()
{


	/*
	if (GetRand(1) + 1 == 1)
	{
		chara[charaCount]->SetType(1);
	}
	else if (GetRand(1) + 1 == 2)
	{
		chara[charaCount]->SetType(2);
	}
	*/
	//1から100までの乱数を取得
	int num = rand() % 100 + 1;

	if (num <= 60)
	{
		if (charaCount < MAX_ENEMY_CHARACTOR && chara[charaCount] == nullptr)
		{
			//ハネテキ
			chara[charaCount] = new Haneteki;
			chara[charaCount]->Initialize();
		}
	}
	else if (num <= 75)
	{
		if (charaCount < MAX_ENEMY_CHARACTOR && chara[charaCount] == nullptr)
		{

			//ハコテキ
			chara[charaCount] = new Hakoteki;
			chara[charaCount]->Initialize();
		}
	}
	else if (num <= 90)
	{
		if (charaCount < MAX_ENEMY_CHARACTOR && chara[charaCount] == nullptr)
		{
			//ハーピー
			chara[charaCount] = new Harpie;
			chara[charaCount]->Initialize();
		}
	}
	else
	{
		if (charaCount < MAX_ENEMY_CHARACTOR && chara[charaCount] == nullptr)
		{
			//金のテキ
			chara[charaCount] = new Kin;
			chara[charaCount]->Initialize();
		}
	}
}

//キャラクター取得
GameObject** Enemy_B::GetCharacter(int count)
{
	return chara;
}