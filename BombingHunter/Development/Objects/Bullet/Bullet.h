#pragma once

#include"../GameObject.h"
#include"../Player/Player.h"


class Bullet : public GameObject
{
private:

	//�ړ��̑���
	Vector2D velocity;

	int animation[2];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������
	int flip_flag;			//���]�t���O

	int type;

public:
	Bullet();
	~Bullet();

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
	//void AnimeControl();

	//�ʒu���擾����
	//Vector2D GetLocation() const;

	//�ʒu���ύX����
	//void SetLocation(const Vector2D& locartion);

};