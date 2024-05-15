#include"Player.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"

//�R���X�g���N�^
Player::Player() : animation_count(0), flip_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//�f�X�g���N�^
Player::~Player()
{
}

//����������
void Player::Initialize()
{
	//�摜�̓ǂݍ���
	//animation[0] = LoadGraph("image/�g���p�C���b�g/���1.png");
	//animation[1] = LoadGraph("image/�g���p�C���b�g/���2.png");
	//animation[0] = LoadGraph("image/�g���p�C���b�g/Player.bmp");
	//animation[1] = LoadGraph("image/�g���p�C���b�g/Player.bmp");

	LoadDivGraph("image/�g���p�C���b�g/0.png", 12, 4, 3, 73, 73, img);
	//animation[1] = LoadDivGraph("image/�g���p�C���b�g/0.png", 12, 4, 3, 73, 73, img_ch);

	img_cnt = 0;

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�g���p�C���b�g�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	scale = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//img[0] = animation[0];

	box_size = Vector2D(64.0f);
}

//�X�V����
void Player::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimeControl();
}

//�`�揈��
void Player::Draw()const
{
	//DrawExtendGraph(1, 1, 1, 1, image, FALSE);
	
	//�v���C���[�摜�̕`��
	//DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	DrawRotaGraphF(location.x, location.y, 1.0, radian, img[img_cnt], TRUE, flip_flag);

	__super::Draw();

	//�f�o�b�O�p
	/*
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

//�I������
void Player::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);

	DeleteGraph(img[4]);
}

//�����蔻��ʒm����
void Player::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
}

//�ړ�����
void Player::Movement()
{
	//�ړ��̑���
	Vector2D velocity = 0.0f;

	//���E�ړ�
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		velocity.x += -2.0f;
		flip_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x += 2.0f;
		flip_flag = FALSE;
	}
	else if (InputControl::GetKey(KEY_INPUT_UP))
	{
		velocity.y -= 2.0f;
		//flip_flag = FALSE;
	}
	else if (InputControl::GetKey(KEY_INPUT_DOWN))
	{
		velocity.y += 2.0f;
		//flip_flag = FALSE;
	}
	else
	{
		velocity.x = 0.0f;
	}

	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;

	//��ʊO�ɍs���Ȃ��悤�ɂ��鏈��
	if (location.x < (scale / 2.0f + 15))
	{
		velocity.x = 0.0f;
		location.x = scale / 2.0f + 15;
	}
	else if ((416.0f - (scale / 2.0f)) < location.x)
	{
		velocity.x = 0.0f;
		location.x = 416.0f - (scale / 2.0f);
	}
}

//�A�j���[�V��������
void Player::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//10�t���[���ڂɓ��B������
	if (animation_count >= 20)
	{
		//�J�E���g���Z�b�g
		animation_count = 0;

		img_cnt++;
		if (img_cnt == 4)
		{
			img_cnt = 0;
		}

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