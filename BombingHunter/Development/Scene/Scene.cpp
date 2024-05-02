#include"Scene.h"
#include"DxLib.h"

//プレイヤー
#include"../Objects/Player/Player.h"
#include"../Objects/Bullet/Bullet.h"

//敵
#include"../Objects/Enemy/Hakoteki.h"
#include"../Objects/Enemy/Haneteki.h"
#include"../Objects/Enemy/Harpie.h"
#include"../Objects/Enemy/Kin.h"

Hakoteki* hakoteki;


//コンストラクタ
Scene::Scene() : 
objects(), image(NULL),
enemy_popcount(0),
chara_count(0)
{
}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{

	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 50.0f));

	//背景を描画
	image = LoadGraph("image/背景/背景1.png");
}

void Scene::Update()
{
	//だいたい２秒ごとに敵を生成
	if (enemy_popcount >= 250){

		randomchar();		//敵の種類をランダムで決めて生成	
		enemy_popcount = 0;		
	}
	else{
		enemy_popcount++;
	}

	//スペースキーでBulletを生成
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bullet>(Vector2D(320.0f, 50.0f));	
	}

	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//オブジェクト同士の当たり判定チェック
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//当たり判定チェック処理
			HitCheckObject(objects[i], objects[j]);
		}
	}
}

//描画処理
void Scene::Draw() const
{
	//背景画像の描画
	DrawGraph(0, 0, image, TRUE);

	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//終了処理
void Scene::Finalize()
{
	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の解放
	objects.clear();

}

//敵の種類をランダムで決めて生成する処理
void Scene::randomchar()
{
	

	//1から100までの乱数を取得
	int num = rand() % 100 + 1;

	if (num <= 50)
	{
		if (chara_count < MAX_ENEMY_CHARACTOR)
		{
			//ハネテキを生成
			CreateObject<Haneteki>(Vector2D(0.0f, 0.0f));
		}
	}
	else if (num <= 75)
	{
		if (chara_count < MAX_ENEMY_CHARACTOR)
		{
			//ハコテキを生成
			CreateObject<Hakoteki>(Vector2D(0.0f, 0.0f));
		}
	}
	else if (num <= 90)
	{
		if (chara_count < MAX_ENEMY_CHARACTOR)
		{
			//ハーピーを生成
			CreateObject<Harpie>(Vector2D(0.0f, 0.0f));
		}
	}
	else
	{
		if (chara_count < MAX_ENEMY_CHARACTOR)
		{
			//金のテキを生成
			CreateObject<Kin>(Vector2D(0.0f, 0.0f));
		}
	}
}


//当たり判定チェック処理(矩形の中心で当たり判定をとる)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	if ((fabsf(diff.x) < box_size.x) && (fabs(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}