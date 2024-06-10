#pragma once


#include"../GameObject.h"
#include"../Bullet/Bullet.h"
#include<vector>

class Effect : public GameObject
{
private:
	Vector2D velocity;	//�����x
	std::vector<int> animation_data;	//�A�j���[�V�����f�[�^

private:

	int animation[3];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������
	//int flip_flag;			//���]�t���O
	int img_ch[2];
	int img[12];
	int img_cnt;

public:
	Effect();
	virtual ~Effect();

	//�������z�֐�(�I�[�o�[���C�h�����ď㏑������)
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();

	//�A�j���[�V��������
	void AnimeControl();

};