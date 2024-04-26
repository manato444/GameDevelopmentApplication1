#pragma once

#include"../GameObject.h"
#include"../UI/UI.h"

class Harpie : public GameObject
{
protected:


private:

	Vector2D location;
	UI* ui;

	int animation[2];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������
	int flip_flag;			//���]�t���O

	//�G���v���C���[��{ 1:�v���C���[, 2: �G }
	int type;

public:
	Harpie();
	~Harpie();

	virtual void Initialize() override;		//����������
	virtual void Update() override;			//�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();

	//�A�j���[�V��������
	void AnimeControl();

	//�ʒu���擾����
	Vector2D GetLocation() const;

	//�ʒu���ύX����
	void SetLocation(const Vector2D& locartion);

	void SetLocation();

};