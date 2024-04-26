#include"Haneteki.h"
#include"DxLib.h"

Haneteki::Haneteki() :
	animation_count(0), flip_flag(FALSE), type(NULL)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Haneteki::~Haneteki()
{
}

void Haneteki::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("image/�n�l�e�L/1.png");
	animation[1] = LoadGraph("image/�n�l�e�L/2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�l�e�L�摜������܂���\n");
	}

	
	location.x = 10.0f;
	location.y = 300.0f;
	
	ui = new UI;
	//location = ui->GetEnemyLocation_Type1();

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	scale = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];
}

void Haneteki::Update()
{

	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimeControl();
}

void Haneteki::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

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
}

void Haneteki::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Haneteki::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
}

void Haneteki::Movement()
{

	//�ړ��̑���
	Vector2D velocity = 0.0f;
	
	
	velocity.x += 0.5f;
	flip_flag = FALSE;
	
	/*
	if (type == 1)
	{
		velocity += -2.0f;
		flip_flag = TRUE;
	}
	else if (type == 2)
	{
		velocity += 2.0f;	
		flip_flag = FALSE;
	}
	*/
	

	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;
}

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

Vector2D Haneteki::GetLocation() const
{
	return this->location;
}

void Haneteki::SetLocation(const Vector2D& location)
{
	this->location = location;
}

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