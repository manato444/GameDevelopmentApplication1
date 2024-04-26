#include"Scene.h"
#include"DxLib.h"

#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/Enemy_Base.h"

//コンストラクタ
Scene::Scene() : objects(), image(NULL)
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

	//敵を生成
	CreateObject<Enemy_B>(Vector2D(320.0f, 50.0f));

	//背景を描画
	image = LoadGraph("image/背景/背景1.png");
}

void Scene::Update()
{
	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}
}

//描画処理
void Scene::Draw() const
{
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