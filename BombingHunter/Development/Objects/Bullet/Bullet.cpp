#include"Bullet.h"
#include"DxLib.h"

Bullet::Bullet() :
	animation_count(0), flip_flag(FALSE)// type(NULL)
{
	animation[0] = NULL;
	//animation[1] = NULL;
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("image/���e/���e.png");
	//animation[1] = LoadGraph("image/���e/���e.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1)//|| animation[1] == -1)
	{
		throw("���e�̉摜������܂���\n");
	}


	location.x = 320.0f;
	location.y = 10.0f;

	//ui = new UI;
	//location = ui->GetEnemyLocation_Type1();

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	scale = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];
}

void Bullet::Update()
{

	//�ړ�����
	Movement();

	//�A�j���[�V��������
	//AnimeControl();
}

void Bullet::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, PI / 2, image, TRUE, flip_flag);

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

void Bullet::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	//DeleteGraph(animation[1]);
}

void Bullet::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
}

void Bullet::Movement()
{

	//�ړ��̑���
	Vector2D velocity = 0.0f;


	velocity.y += 0.5f;
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


/*
void Bullet::AnimeControl()
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
*/

Vector2D Bullet::GetLocation() const
{
	return this->location;
}

void Bullet::SetLocation(const Vector2D& location)
{
	this->location = location;
}

void Bullet::SetLocation()
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