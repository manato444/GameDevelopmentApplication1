#pragma once
#include"../GameObject.h"
#include"../UI/UI.h"

class Hakoteki : public GameObject
{
protected:


private:
	Vector2D velocity;
	Vector2D location;	//�ʒu���
	//UI* ui;				//UI

	int animation[2];		//�A�j���[�V�����摜
	int animation_count;	//�A�j���[�V��������
	int flip_flag;			//���]�t���O
	int type;				//�o���^�C�v


public:
	Hakoteki();		//�R���X�g���N�^
	~Hakoteki();	//�f�X�g���N�^

	virtual void Initialize() override;		//����������
	virtual void Update() override;			//�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

	Vector2D One_Type_Location();
	Vector2D Two_Type_Location();

private:
	//�ړ�����
	void Movement();

	//�A�j���[�V��������
	void AnimeControl();

	//�ʒu���擾����
	Vector2D GetLocation() const;

	//�ʒu���ύX����
	void SetLocation(const Vector2D& locartion);

	virtual void SetType(int type) override;

};