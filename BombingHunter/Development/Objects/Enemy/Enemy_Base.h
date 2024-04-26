#pragma once

#include"../GameObject.h"

//�G�L�����N�^�[�̍ő吔
#define MAX_ENEMY_CHARACTOR 500

//�G���o��������x�[�X�N���X
class Enemy_B : public GameObject 
{
private:

	//�L�����o��
	int enemy_popcount;

	//�L�����J�E���g
	int charaCount;	

	int t;

	GameObject** chara;



public:
	Enemy_B();	//�R���X�g���N�^
	~Enemy_B();	//�f�X�g���N�^

	virtual void Initialize() override;		//����������
	virtual void Update() override;			//�X�V����
	virtual void Draw() const override;		//�`�揈��
	virtual void Finalize() override;

	void randomchar();	//�G�̎�ނ������_���Ō��߂鏈��

	int GetCharaCount() { return this->charaCount; }

	GameObject** GetCharacter(int count);

};