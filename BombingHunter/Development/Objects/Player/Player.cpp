#include"Player.h"
#include"../../Utility/InputControl.h"
#include"../../Utility/ResourceManager.h"
#include"../../Utility/UserTemplate.h"
#include"DxLib.h"

//�R���X�g���N�^
Player::Player() : animation_count(0),rot(0)
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
	//���[�J���ϐ���`
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	//�A�j���[�V������ǂݍ���
	tmp = rm->GetImages("image/�g���p�C���b�g/���_1.png");
	animation_data.push_back(tmp[0]);	//�A�j���[�V�����摜��z��ɒǉ�
	tmp = rm->GetImages("image/�g���p�C���b�g/���_2.png");
	animation_data.push_back(tmp[0]);

	//�摜�̓ǂݍ���(��)
	//animation[0] = LoadGraph("image/�g���p�C���b�g/���1.png");
	//animation[1] = LoadGraph("image/�g���p�C���b�g/���2.png");
	//animation[0] = LoadGraph("image/�g���p�C���b�g/Player.bmp");
	//animation[1] = LoadGraph("image/�g���p�C���b�g/Player.bmp");

	//LoadDivGraph("image/�g���p�C���b�g/0.png", 12, 4, 3, 73, 73, img);
	//animation[1] = LoadDivGraph("image/�g���p�C���b�g/0.png", 12, 4, 3, 73, 73, img_ch);

	/*
	tmp = rm->GetImages("image/�g���p�C���b�g/0.png", 12, 4, 3, 73, 73);
	for (int i = 0; i < 4; i++)
	{
		animation_data.push_back(tmp[img_cnt]);
		img_cnt++;
	}
	*/
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
	image = animation_data[0];
	//image = animation[0];
	//img[0] = animation[0];

	//�傫���w��
	box_size = Vector2D(64.0f);

	//�}�E�X�z�C�[����]��
	rot = 0;
}

//�X�V����
void Player::Update()
{
	SetMouseWheel();	//�}�E�X�z�C�[����]�ʂ��Z�b�g����
	SetLeftStick();		//���X�e�B�b�N�̒l���Z�b�g����
	SetRightStick();	//�E�X�e�B�b�N�̒l���Z�b�g����
	SetLeftTrigger();	//���g���K�[�̒l���Z�b�g����
	SetRightTrigger();	//�E�g���K�[�̒l���Z�b�g����

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

	//DrawRotaGraphF(location.x, location.y, 1.0, radian, img[img_cnt], TRUE, flip_flag);

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

/* - - - - - - - - - - - - - - - - - - -< XInput >- - - - - - - - - - - - - - - - - - - - - - - - - - - */

	
		//���͏��̎擾
	InputControl* input = InputControl::GetInstance();

	int x, y, fontsize, color;

	//�`����W
	x = 0;
	y = 20;

	//�ϐ���`(�t�H���g�T�C�Y)
	fontsize = 18;
	//�F
	color = 0xf6ff00;// GetColor(255, 255, 255);
	//�t�H���g
	ChangeFont("�l�r ����");

	//�t�H���g�T�C�Y�ݒ�
	SetFontSize(fontsize);

	DrawFormatString(x, y -= 18, color, "�f�W�^�������{�^����... %d", input->GetButton(0));
	DrawFormatString(x, y += fontsize, color, "�f�W�^�������{�^����... %d", input->GetButton(1));
	DrawFormatString(x, y += fontsize, color, "�f�W�^�������{�^����... %d", input->GetButton(2));
	DrawFormatString(x, y += fontsize, color, "�f�W�^�������{�^���E... %d", input->GetButton(3));

	DrawFormatString(x, y += fontsize + 18, color, "START�{�^��... %d", input->GetButton(4));
	DrawFormatString(x, y += fontsize, color, "BACK�{�^��... %d", input->GetButton(5));

	DrawFormatString(x, y += fontsize + 18, color, "���X�e�B�b�N��������... %d", input->GetButton(6));
	DrawFormatString(x, y += fontsize, color, "�E�X�e�B�b�N��������... %d", input->GetButton(7));

	DrawFormatString(x, y += fontsize + 18, color, "LB�{�^��... %d", input->GetButton(8));
	DrawFormatString(x, y += fontsize, color, "RB�{�^��... %d", input->GetButton(9));

	DrawFormatString(x, y += fontsize + 18, color, "A�{�^��... %d", input->GetButton(12));
	DrawFormatString(x, y += fontsize, color, "B�{�^��... %d", input->GetButton(13));
	DrawFormatString(x, y += fontsize, color, "X�{�^��... %d", input->GetButton(14));
	DrawFormatString(x, y += fontsize, color, "Y�{�^��... %d", input->GetButton(15));
	DrawFormatString(x, y += fontsize + 18, color, "���g���K�[... %.1f", trigger[0]);
	DrawFormatString(x, y += fontsize, color, "�E�g���K�[... %.1f", trigger[1]);

	DrawFormatString(x, y += fontsize + 18, color, "���X�e�B�b�NX... %.1f", float(stick[0].x));
	DrawFormatString(x, y += fontsize, color, "���X�e�B�b�NY... %.1f", float(stick[0].y));

	DrawFormatString(x, y += fontsize, color, "�E�X�e�B�b�NX... %.1f", float(stick[1].x));
	DrawFormatString(x, y += fontsize, color, "�E�X�e�B�b�NY... %.1f", float(stick[1].y));
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
	//���͏��̎擾
	InputControl* input = InputControl::GetInstance();

	//�ړ��������(�ϐ���`)
	Vector2D direction = 0.0f;

	//���E�ړ�
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_A) || input->GetButton(XINPUT_BUTTON_DPAD_LEFT)
		|| stick[0].x < -0.1f || stick[1].x < -0.1f)
	{
		direction.x = -1.0f;
		flip_flag = TRUE;
	}
	else if (input->GetKey(KEY_INPUT_RIGHT) || input->GetKey(KEY_INPUT_D) || input->GetButton(XINPUT_BUTTON_DPAD_RIGHT)
		|| stick[0].x > 0.1f || stick[1].x > 0.1f)
	{
		direction.x = 1.0f;
		flip_flag = FALSE;
	}

	//�㉺�ړ�
	if (input->GetKey(KEY_INPUT_UP) || input->GetKey(KEY_INPUT_W) || input->GetButton(XINPUT_BUTTON_DPAD_UP)
		|| stick[0].y > 0.1f || stick[1].y > 0.1f)
	{
		direction.y = -1.0f;
	}
	else if (input->GetKey(KEY_INPUT_DOWN) || input->GetKey(KEY_INPUT_S) || input->GetButton(XINPUT_BUTTON_DPAD_DOWN)
		|| stick[0].y < -0.1f || stick[1].y < -0.1f)
	{
		direction.y = 1.0f;
	}
	else
	{
		direction.y = 0.0f;
	}


	//���X�Ɉړ����x���グ�鏈��(�����ɂ���Ĉړ��ʂ̉����Z���s��)
	if (direction.x != 0.0f)
	{
		float max_speed = Abs<float>((5.0f * 0.5 * direction.x));
		velocity.x += 0.5 * direction.x;
		velocity.x = Min<float>(Max<float>(velocity.x, -max_speed),
			max_speed);
	}
	else
	{
		//���X�Ɍ������Ď~�܂鏈��
		if (velocity.x < -1e-6f)
		{
			float calc_speed = velocity.x + 0.1;
			velocity.x = Min<float>(calc_speed, 0.0f);
		}
		else if (1e-6f < velocity.x)
		{
			float calc_speed = velocity.x - 0.1f;
			velocity.x = Max<float>(calc_speed, 0.0f);
		}
	}
	if (direction.y != 0.0f)
	{
		float max_speed = Abs<float>((5.0f * 0.5 * direction.y));
		velocity.y += 0.5 * direction.y;
		velocity.y = Min<float>(Max<float>(velocity.y, -max_speed),
			max_speed);
	}
	else
	{
		//���X�Ɍ������Ď~�܂鏈��
		if (velocity.y < -1e-6f)
		{
			float calc_speed = velocity.y + 0.1;
			velocity.y = Min<float>(calc_speed, 0.0f);
		}
		else if (1e-6f < velocity.y)
		{
			float calc_speed = velocity.y - 0.1f;
			velocity.y = Max<float>(calc_speed, 0.0f);
		}
	}
	//��ʊO�ɍs���Ȃ��悤�ɂ��鏈��_X
	if (location.x < (box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
		location.x = box_size.x / 2.0f;
	}
	else if ((640.0f - (box_size.x / 2.0f)) < location.x)
	{
		velocity.x = 0.0f;
		location.x = 640.0f - (box_size.x / 2.0f);
	}
	//��ʊO�ɍs���Ȃ��悤�ɂ��鏈��_Y
	if (location.y < (box_size.y / 2.0f))
	{
		velocity.y = 0.0f;
		location.y = box_size.y / 2.0f;
	}
	else if ((480.0f - (box_size.y / 2.0f)) < location.y)
	{
		velocity.y = 0.0f;
		location.y = 480.0f - (box_size.y / 2.0f);
	}


	//�ʒu���ɑ��x�����Z����
	location += velocity;
}

/*
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
		else{
			image = animation[0];
		}
	}
}
*/

//�A�j���[�V��������
void Player::AnimeControl()
{
	//�J�E���g�̍X�V
	animation_count++;

	//60�t���[���ɓ��B������
	if (animation_count >= 60)
	{
		//�J�E���g��0�N���A����
		animation_count = 0;

		//�摜�̐؂�ւ����s��
		if (image == animation_data[0])
		{
			image = animation_data[1];
		}
		else
		{
			image = animation_data[0];
		}
	}
}

/* - - - - - - - - - - - - - - - - - - -< XInput >- - - - - - - - - - - - - - - - - - - - - - - - - - - */

//���X�e�B�b�N�̒l���Z�b�g����
Vector2D Player::SetLeftStick()
{
	//Input���͏��̎擾
	InputControl* input = InputControl::GetInstance();

	//���X�e�B�b�N���͒l���擾
	stick[0] = input->GetLeftStick();

	return stick[0];
}

//�E�X�e�B�b�N�̒l���Z�b�g����
Vector2D Player::SetRightStick()
{
	//Input���͏��̎擾
	InputControl* input = InputControl::GetInstance();

	//�E�X�e�B�b�N���͒l���擾
	stick[1] = input->GetRightStick();

	return stick[1];
}

//���g���K�[�̓��͒l���Z�b�g����
float Player::SetLeftTrigger()
{
	//Input���͏��̎擾
	InputControl* input = InputControl::GetInstance();

	//���g���K�[���͒l���擾
	trigger[0] = input->GetLeftTrigger();

	return trigger[0];
}

//�E�g���K�[�̓��͒l���Z�b�g����
float Player::SetRightTrigger()
{
	//Input���͏��̎擾
	InputControl* input = InputControl::GetInstance();

	//�E�g���K�[���͒l���擾
	trigger[1] = input->GetRightTrigger();

	return trigger[1];
}

//�}�E�X�z�C�[����]�ʂ��Z�b�g����
int Player::SetMouseWheel()
{
	//Input���͏��̎擾
	InputControl* input = InputControl::GetInstance();

	//�}�E�X�z�C�[����]�ʂ����Z
	rot += input->GetMouseWheel();

	return rot;
}