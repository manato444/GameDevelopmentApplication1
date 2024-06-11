#pragma once

#include<vector>
#include<string>
#include"../Objects/GameObject.h"
#include"../Utility/InputControl.h"
#include"../Objects/UI/UI.h"

//プレイヤー
#include"../Objects/Player/Player.h"
#include"../Objects/Bullet/Bullet.h"

//敵
#include"../Objects/Enemy/Hakoteki.h"
#include"../Objects/Enemy/Haneteki.h"
#include"../Objects/Enemy/Harpie.h"
#include"../Objects/Enemy/Kin.h"
#include"../Objects/Bullet/EnemyBullet.h"

//エフェクト
#include"../Objects/Effect/Effect.h"


//敵キャラクターの最大数
#define MAX_ENEMY_CHARACTOR 200

class Scene
{
private:
	//ゲームオブジェクトを動的配列で管理
	std::vector<GameObject*> objects;

	bool flg = false;

	int image[3];		//画像
	int f_image;		//枠
	int e_cnt = 0;			//enemyカウント
	int enemy_popcount;			//出現させるキャラをカウント
	int chara_count;				//キャラ数
	//int type;							//キャラタイプ

	int bx;	//背景の描画位置
	
	//Vector2D One_Type_Location();
	//Vector2D Two_Type_Location();

public:
	Scene();	//コンストラクタ
	~Scene();	//デストラクタ

	void Initialize();	//初期化処理
	void Update();		//更新処理
	void Draw() const;	//描画処理
	void Finalize();	//終了時処理

	//敵の種類をランダムで決める処理
	void randomchar();	

	//void Enemy_Bullet();

	//キャラカウントを取得
	int GetCharaCount() { return this->chara_count; }

	//画面外チェック
	void Check_OffScreen();

	//オブジェクトを削除する処理
	void DeleteObject(GameObject* hit_object);
	
public:

	//当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b);
	//bool IsHitCheck(GameObject* a, GameObject* b);

	//オブジェクト生成処理
	template<class T>
	T* CreateObject(const Vector2D& location)
	{
		//指定したクラスを生成する
		T* new_instance = new T();

		//GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("ゲームオブジェクトが生成できませんでした");
		}

		//初期化処理
		new_object->Initialize();

		//位置情報の設定
		new_object->SetLocation(location);

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}
};