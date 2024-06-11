#include"Haneteki.h"
#include"DxLib.h"

//�R���X�g���N�^
Haneteki::Haneteki() :
	animation_count(0), flip_flag(FALSE), type(NULL)
{
	animation[0] = NULL;
	animation[1] = NULL;
}
//�f�X�g���N�^
Haneteki::~Haneteki()
{
}
//����������
void Haneteki::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("image/�n�l�e�L/�n�l�e�L1.png");
	animation[1] = LoadGraph("image/�n�l�e�L/�n�l�e�L2.png");
	//animation[0] = LoadGraph("image/�n�l�e�L/Hane.bmp");
	//animation[1] = LoadGraph("image/�n�l�e�L/Hane.bmp");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�l�e�L�摜������܂���\n");
	}
	//�����̐ݒ�
	radian = 0.0;
	//�傫���̐ݒ�
	scale = 45.0;
	//�����摜�̐ݒ�
	image = animation[0];
	//�ړ����x�̐ݒ�
	velocity = Vector2D(0.5f, 0.0f);
	//�����蔻��̑傫���ݒ�
	box_size = Vector2D(45.0f);
}
//�X�V����
void Haneteki::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimeControl();
}
//�`�揈��
void Haneteki::Draw() const
{
	//�n�l�e�L�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
	__super::Draw();

	/*
	//�f�o�b�O�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D box_collision_upper_left = location - (Vector2D(1.0f) *
		(float)scale / 2.0f);

	Vector2D box_collision_lower_right = location + (Vector2D(1.0f) *
		(float)scale / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y,
		GetColor(255, 0, 0), FALSE);

#endif
*/
}
//�I��������
void Haneteki::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}
//�����蔻��ʒm����
void Haneteki::OnHitCollision(GameObject* hit_object)
{
	/* --- �����������̏���(���ʏ���) --- */
	//if (dynamic_cast<Bullet*>(hit_object) != nullptr){
	//	//Bullet�Ȃ�폜��ʒm����
	//	d_flg = true;
	//}
	//else if (dynamic_cast<Haneteki*>(hit_object) != nullptr){
	//	//�����Ȃ疳��
	//	d_flg = false;
	//}
	//else {
	//	d_flg = false;
	//}
}


//�������`�F�b�N���Ēʒm
//bool Haneteki::D_Objects()
//{
//	return d_flg;
//}

//�ړ�����
void Haneteki::Movement()
{
	flip_flag = TRUE;

	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;
}
//�A�j���[�V��������
void Haneteki::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//�J�E���g���Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}

//���֌W
/*
Vector2D Haneteki::GetLocation() const
{
	return this->location;
}
*/

/*
void Haneteki::SetLocation(const Vector2D& location)
{
	this->location = location;
}
*/
/*
Vector2D Haneteki::One_Type_Location()
{
	return Vector2D(60, 300);
}
Vector2D Haneteki::Two_Type_Location()
{
	return Vector2D(600, 300);
}
*/
/*
void Haneteki::SetLocation()
{
	if (type == 1)
	{
		location.x = 10.0f;
		location.y = 400.0f;
	}
	else if (type == 2)
	{
		location.x = 600.0f;
		location.y = 400.0f;
	}
}
*/