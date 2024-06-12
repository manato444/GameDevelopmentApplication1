#include"Scene.h"
#include"DxLib.h"

//コンストラクタ
Scene::Scene() :
	objects(),f_image(NULL),
	enemy_popcount(0),
	chara_count(0),
	bx(0),
	c(6000.0f)
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
	chara_count = 0;

	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 50.0f));


	//背景を描画(気分で変える)
	//image = LoadGraph("image/背景/背景1.png"); //	爆撃ハンター用背景
	//f_image = LoadGraph("image/背景/フレーム.png");	//枠(?)
	//image = LoadGraph("image/背景/back1.png");	//?
	image[0] = LoadGraph("image/背景/space.bmp");	//宇宙背景
	//image[0] = LoadGraph("image/背景/背景.png"); //爆撃ハンター着せ替え背景
	image[1] = LoadGraph("image/制限時間/timer.png");
	image[2] = LoadGraph("image/スコア/スコア.png");


	//出現タイプを乱数で取得(スポーン位置の設定)　<--要らない
	//type = GetRand(1) + 1;
}

void Scene::Update()
{
	//背景画像の描画位置を更新
	bx += 1;
	//bx = 0;

	//だいたい２秒ごとに敵を生成
	if (enemy_popcount >= 250){
		//敵の種類をランダムで決めて生成	
		randomchar();
		enemy_popcount = 0;
	}
	else {
		enemy_popcount++;
	}
	for (chara_count = 0; chara_count < MAX_ENEMY_CHARACTOR; chara_count++){
		if (chara_count == NULL)
		{
			break;
		}
	}
	//入力機能：更新処理
	InputControl* input = InputControl::GetInstance();

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
	//スペースキーでBulletを生成
	for (int i = 0; i < objects.size(); i++)
	{
		if (input->GetKeyDown(KEY_INPUT_SPACE) || input->GetButtonDown(12)) {

			if (flg == false)
			{
				flg = true;
				//プレイヤーがいたら位置情報を取得して弾を生成する
				if ((dynamic_cast<Player*>(objects[i]) != nullptr)) {
					//Bulletを生成
					CreateObject<Bullet>(objects[i]->GetLocation());
				}
			}
		}
	}
	//Bullet画面外チェック
	Check_OffScreen();
	c--;

}

//描画処理
void Scene::Draw() const
{
	//背景画像の描画
	DrawGraph(bx % 640, 0, image[0], TRUE);
	DrawGraph(bx % 640 - 640, 0, image[0], TRUE);
	//DrawGraph(0, 0, image[0], TRUE);

	//UIの描画（仮）
	DrawGraph(10, 450, image[1], TRUE); 
	DrawGraph(210, 450, image[2], TRUE);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", c);
	
	//燃料ゲージの描画
	float fx = 100.0f;
	float fy = 460.0f;

	/*DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / player->SetFuel()), fy + 40.0f,
		GetColor(0, 230, 0), TRUE);*/
	//DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f, GetColor(255, 255, 255), TRUE);

	//DrawGraph(0, bx % 480 - 480, image, TRUE);
	//DrawGraph(0, 0, f_image, TRUE);



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
	if (objects.empty()){
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
	int r = rand() % 100 + 1;

	if (num <= 50){
		if (chara_count < MAX_ENEMY_CHARACTOR) {
			//ハネテキを生成
			if (r <= 50){
				CreateObject<Haneteki>(Vector2D(10.0f, 300.0f));
			}
			else{
				CreateObject<Haneteki>(Vector2D(10.0f, 180.0f));
			}
		}		
	}
	else if (num <= 75){
		if (chara_count < MAX_ENEMY_CHARACTOR){
			//ハコテキを生成
			CreateObject<Hakoteki>(Vector2D(620.0f, 370.0f));
		}
	}
	else if (num <= 90){
		if (chara_count < MAX_ENEMY_CHARACTOR){
			//ハーピーを生成
			CreateObject<Harpie>(Vector2D(10.0f, 230.0f));
		}
	}
	else{
		if (chara_count < MAX_ENEMY_CHARACTOR){
			//金のテキを生成
			CreateObject<Kin>(Vector2D(10.0f, 420.0f));
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
		//当たったことをオブジェクトに通知する（判別して消すことを通知）
		a->OnHitCollision(b);
		b->OnHitCollision(a);

		//オブジェクトを削除
		DeleteObject(a);
	}
}
//オブジェクトを削除する
void Scene::DeleteObject(GameObject* hit_object)
{
	for (int i = 0; i < objects.size(); i++){	//オブジェクトを調べる	
		for (GameObject* obj : objects)	//シーンに存在するオブジェクトのデータを調べる
		{	
			//削除通知を受け取ったか
			if (obj->D_Objects() == true)
			{
				//敵を削除する
				if ((dynamic_cast<Haneteki*>(objects[i]) == hit_object) ||
					(dynamic_cast<Hakoteki*>(objects[i]) == hit_object) ||
					(dynamic_cast<Harpie*>(objects[i]) == hit_object) ||
					(dynamic_cast<Kin*>(objects[i]) == hit_object))
				{
					delete objects[i];		//メモリの解放
					objects.erase(objects.begin() + i);	//要素の削除
					DeleteBullet();	//シーンに弾が存在していれば削除
					break;	//ループを抜ける
				}
			}
		}
	}
}
//画面外処理
void Scene::Check_OffScreen()
{
	//変数定義(位置情報)
	Vector2D bl;

/* - - - - - - - - - - - - - - < 弾の削除 > - - - - - - - - - - - - - - - - - -  */

	//配列にBulletがいるかひとつずつチェックする
	for (int i = 0; i < objects.size(); i++){
		//Bulletがいたら位置情報を取得
		if ((dynamic_cast<Bullet*>(objects[i]) != nullptr))
		{
			bl = objects[i]->GetLocation();	//位置情報を取得

			//弾が一番下に落ちたら削除する
			if (bl.y > 460.0f)
			{
				delete objects[i];	//メモリを解放
				this->objects.erase(objects.begin() + i);	//要素の削除
				i--;	//要素の位置を示すインデックスがずれないように防止
				flg = false;	//弾を生成できるようにする
			}
		}

/* - - - - - - - - - - - - - - < 敵の削除 > - - - - - - - - - - - - - - - - - -  */

		//"ハネテキ"＆"ハーピー"＆" 金のテキ " がいたら位置情報を取得 
		if ((dynamic_cast<Haneteki*>(objects[i]) != nullptr) ||
			(dynamic_cast<Harpie*>(objects[i]) != nullptr) ||
			(dynamic_cast<Kin*>(objects[i]) != nullptr))
		{
			bl = objects[i]->GetLocation();	//位置情報を取得

			if (bl.x > 640.0f)
			{
				delete objects[i];	//メモリを解放
				this->objects.erase(objects.begin() + i);	//要素の削除
				i--;	//要素の位置を示すインデックスがずれないように防止
			}
		}
		//"ハコテキ " がいたら位置情報を取得 
		if ((dynamic_cast<Hakoteki*>(objects[i]) != nullptr))
		{
			bl = objects[i]->GetLocation();	//位置情報を取得

			if (bl.x < 0.0f)
			{
				delete objects[i];	//メモリを解放
				this->objects.erase(objects.begin() + i);	//要素の削除
				i--;	//要素の位置を示すインデックスがずれないように防止
			}
		}
	}
}

//弾を消す処理
void Scene::DeleteBullet()
{
	for (int i = 0; i < objects.size(); i++) {

		// " 弾 "がシーンに存在していれば削除
		if ((dynamic_cast<Bullet*>(objects[i]) != nullptr))
		{
			delete objects[i];		//メモリの解放
			objects.erase(objects.begin() + i);	//要素の削除
			flg = false;	//弾を生成できるようにする
			i--;	//要素の位置を示すインデックスがずれないように防止
		}
	}
}

//void Scene::Enemy_Bullet()
//{
//	for (int i = 0; i < objects.size(); i++)
//	{
//		//プレイヤーがいたら位置情報を取得して弾を生成する
//		if ((dynamic_cast<Haneteki*>(objects[i]) != nullptr))
//		{
//			//Bulletを生成x
//			//CreateObject<E_Bullet>(objects[i]->GetLocation())
//			e_position = objects[i]->GetLocation();
//		}
//		if ((dynamic_cast<Player*>(objects[i]) != nullptr))
//		{
//			p_position = objects[i]->GetLocation();
//		}
//
//		direction = p_position - e_position;
//			
//			float bs = 1.5f;
//			Vector2D Bv = direction * bs;
//
//			CreateObject<E_Bullet>(e_position);
//	}
//}

/*--要らない
//出現パターンをセット(タイプ1 : 左から出現させる)
Vector2D Scene::One_Type_Location()
{
	return Vector2D(60, 200);
}
//出現パターンをセット(タイプ2 : 右から出現させる)
Vector2D Scene::Two_Type_Location()
//{
//	return Vector2D(600, 300);
//}
//*/


