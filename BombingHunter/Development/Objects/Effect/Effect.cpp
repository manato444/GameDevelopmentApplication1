#include"Effect.h"
#include"../../Utility/InputControl.h"
#include"../../Utility/ResourceManager.h"
#include"../../Utility/UserTemplate.h"
#include"DxLib.h"

//�R���X�g���N�^
Effect::Effect() : animation_count(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
}
//�f�X�g���N�^
Effect::~Effect()
{
}
//����������
void Effect::Initialize()
{
	//���[�J���ϐ���`
	ResourceManager* rm = ResourceManager::GetInstance();
	std::vector<int> tmp;

	//�A�j���[�V������ǂݍ���
	tmp = rm->GetImages("image/����/����1.png");
	animation_data.push_back(tmp[0]);	//�A�j���[�V�����摜��z��ɒǉ�
	tmp = rm->GetImages("image/����/����2.png");
	animation_data.push_back(tmp[0]);
	tmp = rm->GetImages("image/����/����3.png");
	animation_data.push_back(tmp[0]);

	//�����̐ݒ�
	radian = 0.0f;
	//�傫���̐ݒ�
	scale = 64.0f;
	//�����摜�̐ݒ�
	image = animation_data[0];
}
//�X�V����
void Effect::Update()
{
	Movement();	//�ړ�

	AnimeControl();	//�A�j���[�V��������
}
//�`�揈��
void Effect::Draw() const
{
	__super::Draw();
}
//�I��������
void Effect::Finalize()
{
	//�g�p�����摜���������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
}
//�ړ�����
void Effect::Movement()
{
}
//�A�j���[�V��������
void Effect::AnimeControl()
{
	//�J�E���g�̍X�V
	animation_count++;
		//60�t���[���ɓ��B������
		if (animation_count >= 60) {
			
			//�J�E���g��0�N���A����
			animation_count = 0;

			//�摜�̐؂�ւ����s��
			if (image == animation_data[0]) {
				image = animation_data[1];
			}
			else if (image == animation_data[1]) {
				image = animation_data[2];
			}
			else {
				image = animation_data[0];
			}
		}
}

//�����蔻��ʒm����
void Effect::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���

}