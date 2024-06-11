#pragma once

#include"../GameObject.h"
#include"../Player/Player.h"
#include"../../Scene/Scene.h"

class Bullet : public GameObject
{
private:

	std::vector<int> animation_data;	//�A�j���[�V�����f�[�^

	//�ړ��̑���
	Vector2D velocity;

	int animation[2];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������
	int flip_flag;			//���]�t���O

	int d_flg;  //�I�u�W�F�N�g�폜�t���O
	int e_flg;	//�G�t�F�N�g�����t���O
	int type; //�Ȃɂ���

public:
	Bullet();
	~Bullet();

	virtual void Initialize() override;	//����������
	virtual void Update() override;		//�X�V����
	virtual void Draw() const override;	//�`�揈��
	virtual void Finalize() override;	//�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;
	virtual bool D_Objects() override;
	virtual bool E_Effect() override;
	//virtual bool C_DeleteObject(bool flg) override;

private:
	//�ړ�����
	void Movement();

	//�A�j���[�V��������
	void AnimeControl();

	//�ʒu���擾����
	//Vector2D GetLocation() const;

	//�ʒu���ύX����
	//void SetLocation(const Vector2D& locartion);

};