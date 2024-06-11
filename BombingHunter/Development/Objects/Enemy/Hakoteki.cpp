#include"Hakoteki.h"
#include"DxLib.h"

Hakoteki::Hakoteki():
	animation_count(0), flip_flag(NULL),type(NULL), d_flg(false)
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
	if (animation[0] == -1 || animation[1] == -1){
		throw("�n�R�e�L�摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0;
	//�傫���̐ݒ�
	scale = 45.0;
	//�����摜�̐ݒ�
	image = animation[0];
	//�����蔻��̑傫��
	box_size = Vector2D(45.0f);
	//�ړ����x
	velocity = Vector2D(-0.4f, 0.0f);
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
	//�n�R�e�L�̕`��
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
void Hakoteki::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void Hakoteki::OnHitCollision(GameObject* hit_object)
{
	/* --- �����������̏���(���ʏ���) --- */
	//if (dynamic_cast<Kin*>(hit_object) != nullptr) {
	//	//����
	//	d_flg = false;
	//}
	//else {
	//	d_flg = false;
	//}
}

//�������`�F�b�N���Ēʒm
bool Hakoteki::D_Objects()
{
	return d_flg;
}

//�ړ�����
void Hakoteki::Movement()
{
	flip_flag = TRUE;

	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;
}

//�A�j���[�V��������
void Hakoteki::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 60){
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

