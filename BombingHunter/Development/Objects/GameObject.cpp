#include"GameObject.h"
#include"../Utility/ResourceManager.h"
#include"DxLib.h"

//コンストラクタ
GameObject::GameObject() :
	location(0.0f),
	scale(0.0f),
	radian(0.0f),
	image(0),
	sound(0),
	type(NULL),
	box_size(0.0f),
	flip_flag(FALSE),
	hit_flg(false),
	e_flg(false)
{
}
//デストラクタ
GameObject::~GameObject()
{
}
//初期化処理
void GameObject::Initialize()
{
	hit_flg = false;
}
//更新処理
void GameObject::Update()
{
}
//描画処理
void GameObject::Draw() const
{
	//メンバの情報を基に画像を描画
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	Vector2D tl = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);
	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);

	//当たり判定の可視化
	/*
#ifdef D_PIVOT_CENTER

	Vector2D tl = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);

#else
	Vector2D tl = location;
	Vector2D br = location + box_size;

	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);

#endif  D_PIVOT_CENTER
*/
}

//終了処理
void GameObject::Finalize()
{
}
//当たり判定通知処理
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//当たった時に行う処理
	delete hit_object;
}
//削除オブジェクト通知
bool GameObject::D_Objects()
{
	return this->hit_flg;
}
//エフェクト生成通知
bool GameObject::E_Effect()
{
	return this->e_flg;
}

////ヒットオブジェクト削除判別処理
//bool GameObject::C_DeleteObject(bool flg)
//{
//	return this->hit_flg;
//}

void GameObject::DeleteObject(GameObject* hit_object)
{
	this-hit_object;
}

//位置情報取得処理
Vector2D GameObject::GetLocation() const
{
	return this->location;
}
//位置情報設定処理
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}
//当たり判定の大きさ取得
Vector2D GameObject::GetBoxSize() const
{
	return box_size;
}
/*
int GameObject::Set_T()
{
	type = GetRand(1) + 1;
	return type;
}
*/