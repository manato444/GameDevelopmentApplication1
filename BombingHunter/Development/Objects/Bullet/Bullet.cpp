#include"Bullet.h"
#include"DxLib.h"
#include"../Effect/Effect.h"
#include"../../Scene/Scene.h"

Bullet::Bullet() :
	animation_count(0), flip_flag(NULL)// type(NULL)
{
	animation[0] = NULL;
	//animation[1] = NULL;
}
//�f�X�g���N�^
Bullet::~Bullet()
{
}
//����������
void Bullet::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("image/���e/�~�T�C��.png");
	//animation[0] = LoadGraph("image/���e/meteor.png");
	//animation[0] = LoadGraph("image/���e/Bullet.bmp");
	//animation[0] = LoadGraph("image/���e/bl1.png");
	//animation[1] = LoadGraph("image/���e/bl2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("���e�̉摜������܂���\n");
	}
	
	//ui = new UI;
	//location = ui->GetEnemyLocation_Type1();

	//�����̐ݒ�
	radian = DX_PI_F / 2;

	//�傫���̐ݒ�
	scale = 30.0;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����蔻��̑傫��
	box_size = Vector2D(40.0f, 40.0f);

	//�ړ����x�̐ݒ�
	velocity = Vector2D(0.0f, 0.7f);
}
//�X�V����
void Bullet::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimeControl();
}
//�`�揈��
void Bullet::Draw() const
{

	//Bullet�摜�̕`��
	//DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
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
//�I��������
void Bullet::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}
//�����������ƒʒm(hit_object)
void Bullet::OnHitCollision(GameObject* hit_object)
{
	/* --- �����������̏���(���ʏ���) --- */
	if (dynamic_cast<Haneteki*>(hit_object) != nullptr) {
		//Haneteki�Ȃ�폜������ʒm
		flg = true;
	}
	else if (dynamic_cast<Bullet*>(hit_object) != nullptr) {
		//Bullet�Ȃ瓖���蔻��𖳎�
		flg = false;
	}
	else if (dynamic_cast<Player*>(hit_object) != nullptr) {
		//Player�Ȃ瓖���蔻��𖳎�
		flg = false;
	}
	else{
		flg = false;
	}
	//�G�t�F�N�g����(��)
	//CreateEffect(hit_object->GetLocation());
}
//�������`�F�b�N���Ēʒm
bool Bullet::D_Objects()
{
	return flg;
}

//�ړ�����
void Bullet::Movement()
{
	flip_flag = FALSE;

	//�t���[���J�E���g�����Z����
	animation_count++;
	//1�t���[�����Ƃɉ�]������
	if (animation_count >= 3)
	{
		//�J�E���g���Z�b�g
		animation_count = 0;
			//radian += DX_PI_F / 180;
	}
	//���݂̈ʒu���W�ɑ��������Z����
	location += velocity;
	/*
	if (flip_flag == FALSE)
	{
	location += velocity.x += 0.5f;
	}
	else if(flip_flag == TRUE)
	{
		location -= velocity.x -= 0.5f;
	}
	*/
}

/*
Vector2D Bullet::GetLocation() const
{
	return this->location;
}

void Bullet::SetLocation(const Vector2D& location)
{
	this->location = location;
}
*/

//�A�j���[�V��������
void Bullet::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 20)
	{
		//�J�E���g���Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0]) {

			image = animation[1];
		}
		else {

			image = animation[0];
		}
	}
}