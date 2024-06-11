#pragma once


#include"../GameObject.h"
#include"../Bullet/Bullet.h"
#include<vector>

class Player : public GameObject
{
private:
	Vector2D velocity;	//�����x
	std::vector<int> animation_data;	//�A�j���[�V�����f�[�^

private:

	int animation[2];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������
	//int flip_flag;			//���]�t���O
	int img_ch[2];
	int img[12];
	int img_cnt;
	//int d_flg;
	//Vector2D locaiton;

public:
	Player();
	virtual ~Player();

	//�������z�֐�(�I�[�o�[���C�h�����ď㏑������)
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;
	
	//virtual bool D_Objects() override;

private:
	Vector2D stick[2];	//�X�e�B�b�N���͒l = { stick[0]:���X�e�B�b�N, stick[1]:�E�X�e�B�b�N }
	float trigger[2];	//�g���K�|���͒l = { trigger[0]:���g���K�[, trigger[1]:�E�g���K�[ }

	int rot;

public:

	Vector2D SetLeftStick(); //���X�e�B�b�N�̒l���Z�b�g����
	Vector2D SetRightStick();//�E�X�e�B�b�N�̒l���Z�b�g����

	float SetLeftTrigger();	//���g���K�[�̓��͒l���Z�b�g����
	float SetRightTrigger();//�E�g���K�[�̓��͒l���Z�b�g����

	int SetMouseWheel();	//�}�E�X�z�C�[����]�ʂ��Z�b�g����


private:
	//�ړ�����
	void Movement();

	//�A�j���[�V��������
	void AnimeControl();

};