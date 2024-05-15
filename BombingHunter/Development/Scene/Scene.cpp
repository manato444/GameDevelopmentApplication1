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

//Hakoteki* hakoteki;

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
	//image = LoadGraph("image/背景/背景1.png"); //	爆撃ハンター用背景
	f_image = LoadGraph("image/背景/フレーム.png");	//枠(?)
	image = LoadGraph("image/背景/space.bmp");	//宇宙背景

	//出現タイプを乱数で取得(スポーン位置の設定)
	//type = GetRand(1) + 1;

	

}

void Scene::Update()
{
	//背景画像の描画位置を更新
	bx += 1;

	//だいたい２秒ごとに敵を生成
	if (enemy_popcount >= 250)
	{
		//敵の種類をランダムで決めて生成	
		randomchar();
		enemy_popcount = 0;
	}
	else {
		enemy_popcount++;
	}


	//スペースキーでBulletを生成
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		//配列にPlayerがいるかひとつずつチェックする
		for (int i = 0; i < objects.size(); i++)
		{
			//プレイヤーがいたら位置情報を取得して弾を生成する
			if (!(dynamic_cast<Player*>(objects[i]) == nullptr))
			{
				//Bulletを生成
				CreateObject<Bullet>(objects[i]->GetLocation());
			}
		}
	}

	//Bullet画面外チェック
	//Check_OffScreen();

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
			if (!(dynamic_cast<Haneteki*>(objects[i]) == nullptr))
			{
				if (!(dynamic_cast<Bullet*>(objects[j]) == nullptr))
				{
					//当たり判定チェック処理
					HitCheckObject(objects[i], objects[j]);
				}
			}
		}
	}
	
}

//描画処理
void Scene::Draw() const
{
	//背景画像の描画
	//DrawGraph(bx % 640, 0, image, TRUE);
	//DrawGraph(bx % 640 - 640, 0, image, TRUE);

	DrawGraph(0, bx % 480, image, TRUE);
	DrawGraph(0, bx % 480 - 480, image, TRUE);

	DrawGraph(0, 0, f_image, TRUE);


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
			CreateObject<Haneteki>(Vector2D(10.0f, 300.0f));

			/*
			if (type == 1) {
				//スポーン位置を【左】に設定
				CreateObject<Haneteki>(Vector2D(One_Type_Location()));
			}
			else if (type == 2) {
				//スポーン位置を【右】に設定
				CreateObject<Haneteki>(Vector2D(Two_Type_Location()));
			}
			*/
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

		//要素の削除
		objects.erase(objects.begin() + 1);

	}
}

/*
//画面外処理
void Scene::Check_OffScreen()
{
	//変数定義
	Vector2D bl;

	//配列にBulletがいるかひとつずつチェックする
	for (int i = 0; i < objects.size(); i++)
	{
		//Bulletがいたら位置情報を取得
		if (!(dynamic_cast<Bullet*>(objects[i]) == nullptr))
		{
			bl = objects[i]->GetLocation();

			if (bl.y > 380.0f)
			{
				//要素の削除
				this->objects.erase(objects.begin() + 1);
			}
		}
	}
}
*/


/*
//出現パターンをセット(タイプ1 : 左から出現させる)
Vector2D Scene::One_Type_Location()
{
	return Vector2D(60, 200);
}
//出現パターンをセット(タイプ2 : 右から出現させる)
Vector2D Scene::Two_Type_Location()
{
	return Vector2D(600, 300);
}
*/

