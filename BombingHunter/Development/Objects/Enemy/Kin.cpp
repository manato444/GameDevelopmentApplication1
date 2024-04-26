#include"Kin.h"
#include"DxLib.h"

Kin::Kin() :
	animation_count(0), flip_flag(FALSE), type(NULL)
{
	
	for (int i = 0; i < 5; i++)
	{
	animation[i] = NULL;
	}
	

}

Kin::~Kin()
{
}

void Kin::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("image/���̃e�L/1.png");
	animation[1] = LoadGraph("image/���̃e�L/2.png");
	animation[2] = LoadGraph("image/���̃e�L/3.png");
	animation[3] = LoadGraph("image/���̃e�L/4.png");
	animation[4] = LoadGraph("image/���̃e�L/5.png");


	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1 || animation[2] == -1 || animation[3] == -1 || animation[4] == -1)
	{
		throw("���̃e�L�摜������܂���\n");
	}

	//ui = new UI;
	//location = ui->GetEnemyLocation();

	location.x = 630.0f;
	location.y = 400.0f;

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	scale = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];
}

void Kin::Update()
{

	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimeControl();
}

void Kin::Draw() const
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

void Kin::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Kin::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
}

void Kin::Movement()
{

	//�ړ��̑���
	Vector2D velocity = 0.0f;
	velocity.x -= 1.0f;
	flip_flag = TRUE;

	/*
	if (type == 1)
	{

		SetLocation();

		velocity += -2.0f;
		flip_flag = TRUE;
	}
	else if (type == 2)
	{

		SetLocation();

		velocity += 2.0f;
		flip_flag = FALSE;
	}
	*/
	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;
}

void Kin::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//�J�E���g���Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�(�S������)
		if (image == animation[0])
		{
			image = animation[1];
		}
		else if(image == animation[1])
		{
			image = animation[2];
		}
		else if (image == animation[2])
		{
			image = animation[3];
		}
		else if (image == animation[3])
		{
			image = animation[4];
		}
		else
		{
			image = animation[1];
		}
	}
}

Vector2D Kin::GetLocation() const
{
	return this->location;
}

void Kin::SetLocation(const Vector2D& location)
{
	this->location = location;
}

void Kin::SetLocation()
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