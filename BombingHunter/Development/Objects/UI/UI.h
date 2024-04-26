#pragma once

#include"../../Utility/Vector2D.h"

class UI
{
private:


public:
	UI();	//コンストラクタ
	~UI();	//デストラクタ

	void Initialize();	//初期化
	void Update();		//更新処理
	void Draw() const;	//描画
	void Finalize();	//終了

	Vector2D SetEnemyLocation_Type1();	//敵の位置情報取得
	Vector2D SetEnemyLocation_Type2();	//敵の位置情報取得


};