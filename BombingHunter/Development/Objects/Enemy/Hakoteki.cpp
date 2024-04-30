#include"Hakoteki.h"
#include"DxLib.h"

Hakoteki::Hakoteki():
	animation_count(0), flip_flag(FALSE),type(NULL)
{

	animation[0] = NULL;
	animation[1] = NULL;

}

Hakoteki::~Hakoteki()
{
}

void Hakoteki::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("image/�n�R�e�L/�n�R�e�L1.png");
	animation[1] = LoadGraph("image/�n�R�e�L/�n�R�e�L2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�R�e�L�摜������܂���\n");
	}

	ui = new UI;

	//location.x = 30.0f;
	//location.y = 400.0f;

	type = GetRand(1) + 1;

	if (type == 1)
	{
		location = ui->SetEnemyLocation_Type1();
	}
	else if (type == 2)
	{
		location = ui->SetEnemyLocation_Type2();
	}
	
	//�����蔻��̑傫��
	//box_size = 64.0f;

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	scale = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];
}

void Hakoteki::Update()
{

	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimeControl();
}

void Hakoteki::Draw() const
{
	
	//�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//__super::Draw();
	
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

void Hakoteki::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Hakoteki::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
}

void Hakoteki::Movement()
{

	//�ړ��̑���
	Vector2D velocity = 0.0f;
	//velocity.x += 0.5f;
	//flip_flag = TRUE;

	
	if (type == 1)	//�^�C�v1�Ȃ�E�����Ɉړ�������
	{
		velocity.x += GetRand(0.1f)+0.3f;
		flip_flag = FALSE;
	}
	else if (type == 2) //�^�C�v2�Ȃ獶�����Ɉړ�������
	{
		velocity.x += GetRand(-0.1f) + (-0.3f);
		flip_flag = TRUE;	
	}

	//��ʂ̊O�ɍs�����疳����茩���Ȃ�����(��)
	if (location.x < (scale / scale) - scale / 2.0f)
	{
		
		velocity.x = 0.0f;
		location.x = scale *(-scale);
		DeleteGraph(image);
		
	}
	else if ((640.0f + scale) < location.x)
	{
		
		velocity.x = 0.0f;
		location.x = 640.0f + (scale * 2);
		DeleteGraph(image);
		
	}
	
	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;
}

void Hakoteki::AnimeControl()
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

//�ʒu���擾(�Q�b�g)
Vector2D Hakoteki::GetLocation() const
{
	return this->location;
}

//�ʒu�ύX����(�Z�b�g)
void Hakoteki::SetLocation(const Vector2D& location)
{
	this->location = location;
}

void Hakoteki::SetType(int type)
{
	this->type = type;
}

Vector2D Hakoteki::GetEnemyLocation_Type1()
{
	return this->location;
}

Vector2D Hakoteki::GetEnemyLocation_Type2()
{
	return this->location;
}