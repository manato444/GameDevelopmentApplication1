#include"GameObject.h"
#include"../Utility/ResourceManager.h"
#include"DxLib.h"

//�R���X�g���N�^
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
//�f�X�g���N�^
GameObject::~GameObject()
{
}
//����������
void GameObject::Initialize()
{
	hit_flg = false;
}
//�X�V����
void GameObject::Update()
{
}
//�`�揈��
void GameObject::Draw() const
{
	//�����o�̏�����ɉ摜��`��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	Vector2D tl = location - (box_size / 2.0f);
	Vector2D br = location + (box_size / 2.0f);
	DrawBoxAA(tl.x, tl.y, br.x, br.y, GetColor(255, 0, 0), FALSE);

	//�����蔻��̉���
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

//�I������
void GameObject::Finalize()
{
}
//�����蔻��ʒm����
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//�����������ɍs������
	delete hit_object;
}
//�폜�I�u�W�F�N�g�ʒm
bool GameObject::D_Objects()
{
	return this->hit_flg;
}
//�G�t�F�N�g�����ʒm
bool GameObject::E_Effect()
{
	return this->e_flg;
}

////�q�b�g�I�u�W�F�N�g�폜���ʏ���
//bool GameObject::C_DeleteObject(bool flg)
//{
//	return this->hit_flg;
//}

void GameObject::DeleteObject(GameObject* hit_object)
{
	this-hit_object;
}

//�ʒu���擾����
Vector2D GameObject::GetLocation() const
{
	return this->location;
}
//�ʒu���ݒ菈��
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}
//�����蔻��̑傫���擾
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