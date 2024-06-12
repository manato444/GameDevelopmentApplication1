#include"Harpie.h"
#include"DxLib.h"

Harpie::Harpie() :
	animation_count(0), flip_flag(FALSE), type(NULL), animation_data()
{
	animation[0] = NULL;
	animation[1] = NULL;
}

Harpie::~Harpie()
{
}

void Harpie::Initialize()
{
	//���[�J���ϐ���`
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	//�A�j���[�V������ǂݍ���
	tmp = rm->GetImages("image/�n�[�s�[/�n�[�s�[1.png");
	animation_data.push_back(tmp[0]);	//�A�j���[�V�����摜��z��ɒǉ�
	tmp = rm->GetImages("image/�n�[�s�[/�n�[�s�[2.png");
	animation_data.push_back(tmp[0]);

	//�摜�̓ǂݍ���
	/*animation[0] = LoadGraph("image/�n�[�s�[/�n�[�s�[1.png");
	animation[1] = LoadGraph("image/�n�[�s�[/�n�[�s�[2.png");*/

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�[�s�[�摜������܂���\n");
	}

	//ui = new UI;
	//location = ui->GetEnemyLocation();

	location.x = 10.0f;
	location.y = 200.0f;

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	scale = 64.0;

	//�����摜�̐ݒ�
	//image = animation[0];
	image = animation_data[0];

	//�����蔻��̑傫��
	box_size = Vector2D(54.0f);

	//���x�w��
	velocity = Vector2D(0.3f, 0.0f);
}

void Harpie::Update()
{

	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimeControl();
}

void Harpie::Draw() const
{
	//�n�[�s�[�摜�̕`��
	//DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
	__super::Draw();

//	//�f�o�b�O�p
//#if _DEBUG
//	//�����蔻��̉���
//	Vector2D box_collision_upper_left = location - (Vector2D(1.0f) *
//		(float)scale / 2.0f);
//
//	Vector2D box_collision_lower_right = location + (Vector2D(1.0f) *
//		(float)scale / 2.0f);
//
//	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
//		box_collision_lower_right.x, box_collision_lower_right.y,
//		GetColor(255, 0, 0), FALSE);
//
//#endif
}

void Harpie::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation_data[0]);
	DeleteGraph(animation_data[1]);
}

void Harpie::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
}

void Harpie::Movement()
{
	flip_flag = FALSE;

	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;
}

//�A�j���[�V��������
void Harpie::AnimeControl()
{
	//�J�E���g�̍X�V
	animation_count++;

	//60�t���[���ɓ��B������
	if (animation_count >= 30)
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

//void Harpie::AnimeControl()
//{
//	//�t���[���J�E���g�����Z����
//	animation_count++;
//
//	//60�t���[���ڂɓ��B������
//	if (animation_count >= 60)
//	{
//		//�J�E���g���Z�b�g
//		animation_count = 0;
//
//		//�摜�̐؂�ւ�
//		if (image == animation[0])
//		{
//			image = animation[1];
//		}
//		else
//		{
//			image = animation[0];
//		}
//	}
//}

