#pragma once

#include"../GameObject.h"
#include"../../Scene/Scene.h"
#include"../UI/UI.h"

class Haneteki : public GameObject
{
private:
	Vector2D velocity;
	std::vector<int> animation_data;	//�A�j���[�V�����f�[�^

	int animation[2];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������
	int flip_flag;			//���]�t���O	
	int type;				//�^�C�v
	//int d_flg;				//�폜�t���O

public:
	Haneteki();
	~Haneteki();

	virtual void Initialize() override;		//����������
	virtual void Update() override;			//�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;
	//virtual bool D_Objects() override;

private:
	//�ړ�����
	void Movement();

	//�A�j���[�V��������
	void AnimeControl();

	//Vector2D One_Type_Location();
	//Vector2D Two_Type_Location();

};