#include"Hakoteki.h"
#include"DxLib.h"

Hakoteki::Hakoteki():
	animation_count(0), flip_flag(NULL),type(NULL)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Hakoteki::~Hakoteki()
{
}

//����������
void Hakoteki::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("image/�n�R�e�L/�n�R�e�L_1.png");
	animation[1] = LoadGraph("image/�n�R�e�L/�n�R�e�L_2.png");
	//animation[0] = LoadGraph("image/�n�R�e�L/Hako.bmp");
	//animation[1] = LoadGraph("image/�n�R�e�L/Hako.bmp");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�R�e�L�摜������܂���\n");
	}

	//�o���^�C�v�𗐐��Ŏ擾(�X�|�[���ʒu�̐ݒ�)
	type = GetRand(1) + 1;

	if (type == 1)	{
		//�X�|�[���ʒu���y���z�ɐݒ�
		location = One_Type_Location();
	}
	else if (type == 2){
		//�X�|�[���ʒu���y�E�z�ɐݒ�
		location = Two_Type_Location();
	}
	
	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	scale = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];
	
	//�����蔻��̑傫��
	box_size = 64.0f;

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

//�I��������
void Hakoteki::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void Hakoteki::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	velocity = 0.0f;
	location = location;
}

//�ړ�����
void Hakoteki::Movement()
{
	//�ړ��̑���
	velocity = 0.0f;

	if (type == 1) 	//�^�C�v1�Ȃ�E�����Ɉړ�������
	{
		velocity.x += 0.3f;
		flip_flag = FALSE;
	}
	else if (type == 2) //�^�C�v2�Ȃ獶�����Ɉړ�������
	{
		velocity.x -= 0.3f;
		flip_flag = TRUE;
	}
	
	//��ʂ̊O�ɍs�����疳����茩���Ȃ�����(��)
	if (location.x < (scale / scale) - scale / 2.0f)
	{
		velocity.x = 0.0f;	//��~������
		location.x = scale *(-scale);	//��ʊO�ɖ������ǂ����i���j
		DeleteGraph(image);		//�摜�̍폜
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

//�A�j���[�V��������
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
		if (image == animation[0]){

			image = animation[1];
		}
		else{

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

//�L�����^�C�v���Z�b�g
void Hakoteki::SetType(int type)
{
	this->type = type;
}

//�o���p�^�[�����Z�b�g(�^�C�v1 : ������o��������)
Vector2D Hakoteki::One_Type_Location()
{
	return Vector2D(60, 400);
}
//�o���p�^�[�����Z�b�g(�^�C�v2 : �E����o��������)
Vector2D Hakoteki::Two_Type_Location()
{
	return Vector2D(600, 400);
}
