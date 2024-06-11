#pragma once

#include"../GameObject.h"
#include"../UI/UI.h"
#include"../../Scene/Scene.h"

class Kin : public GameObject
{
private:

	Vector2D velocity;
	UI* ui;

	int animation[5];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������
	int flip_flag;			//���]�t���O

	//�G���v���C���[��{ 1:�v���C���[, 2: �G }
	int type;

	bool d_flg;

public:
	Kin();
	~Kin();

	virtual void Initialize() override;		//����������
	virtual void Update() override;			//�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;
	virtual bool D_Objects() override;

private:
	//�ړ�����
	void Movement();

	//�A�j���[�V��������
	void AnimeControl();

};