#pragma once

#include "../Utility/Vector2D.h"
#include"UI/UI.h"
#include"../Utility/ResourceManager.h"


#define D_PIVOT_CENTER

//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	Vector2D location;	//位置情報
	Vector2D box_size;

	int flip_flag;
	//std::vector<int> object;

	double scale;		//大きさ
	double radian;		//向き
	int image;			//描画する画像
	int sound;			//再生する音源
	int type;

	bool hit_flg;	//ヒットフラグ
	bool e_flg;	//エフェクトフラグ

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();		//初期化処理
	virtual void Update();			//更新処理
	virtual void Draw() const;		//描画処理
	virtual void Finalize();		//終了処理

	//敵のタイプ
	virtual void SetType(int type) {};

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object);

	//位置情報取得処理
	Vector2D GetLocation() const;

	//位置情報変更処理
	void SetLocation(const Vector2D& location);

	//当たり判定の大きさを取得する
	Vector2D GetBoxSize() const;

	//virtual bool C_DeleteObject(bool flg);
	virtual void DeleteObject(GameObject* hit_obj);
	virtual bool D_Objects();
	virtual bool E_Effect();

	//敵の出現タイプ
	virtual Vector2D GetEnemyLocation_Type1() { return Vector2D(); }
	virtual Vector2D GetEnemyLocation_Type2() { return Vector2D(); }

	//int Set_T();
};