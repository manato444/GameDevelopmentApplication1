/********************************
	�v��Ȃ�����

#include"Hakoteki.h"
#include"Haneteki.h"
#include"Harpie.h"
#include"Kin.h"
#include"DxLib.h"
#include"Enemy_O.h"
#include"../../Scene/Scene.h"

Enemy_O::Enemy_O() :
	enemy_popcount(0),
	charaCount(0)
{
}

Enemy_O::~Enemy_O()
{
}

//������
void Enemy_O::Initialize()
{
	enemy_popcount = 0;
	charaCount = 0;
	
	chara = new GameObject * [MAX_ENEMY_CHARACTOR];
	for (int i = 0; i < MAX_ENEMY_CHARACTOR; i++)
	{
		chara[i] = nullptr;
	}
	
}

void Enemy_O::Initialize(Scene* scene) 
{
	this->scene = scene;
}

//�X�V����
void Enemy_O::Update()
{
	//��������2�b���Ƃɏo��������
	if (enemy_popcount >= 250)
	{
		t = GetRand(1)+ 1;
		randomchar();//�G�̎�ނ������_���Ō��߂�
		enemy_popcount = 0;	
	}
	else
	{
		enemy_popcount++;
	}

	for (charaCount = 0; charaCount < MAX_ENEMY_CHARACTOR; charaCount++)
	{
		if (chara[charaCount] == nullptr)
		{
			break;
		}
		//�G�̏o���ʒu���^�C�v�Ŏ擾 :(��){type = 1 : ���[�o���@type = 2 : �E�[�o��}
		
		/*
		if (t == 1)
		{
			chara[charaCount]->SetType(1);
		}
		else if (t == 2)
		{
			chara[charaCount]->SetType(2);
		}
		*//*
		chara[charaCount]->Update();
	}
}

//�`��
void Enemy_O::Draw() const
{
	//�ő吔�܂ŃL������`�悳����
	for (int i = 0; i < MAX_ENEMY_CHARACTOR; i++)
	{
		if (chara[i] == nullptr)
		{
			break;
		}
		chara[i]->Draw();
	}
}

//�I��
void Enemy_O::Finalize()
{
}

//�G�̎�ނ������_���Ō��߂�
void Enemy_O::randomchar()
{

	//1����100�܂ł̗������擾
	int num = rand() % 100 + 1;

	if (num <= 60)
	{
		if (charaCount < MAX_ENEMY_CHARACTOR && chara[charaCount] == nullptr)
		{
			//�n�l�e�L
			chara[charaCount] = this->scene->CreateObject<Haneteki>(Vector2D());
			chara[charaCount]->Initialize();
		}
	}
	else if (num <= 75)
	{
		if (charaCount < MAX_ENEMY_CHARACTOR && chara[charaCount] == nullptr)
		{

			//�n�R�e�L
			chara[charaCount] = this->scene->CreateObject<Hakoteki>(Vector2D());
			chara[charaCount]->Initialize();
		}
	}
	else if (num <= 90)
	{
		if (charaCount < MAX_ENEMY_CHARACTOR && chara[charaCount] == nullptr)
		{
			//�n�[�s�[
			chara[charaCount] = this->scene->CreateObject<Harpie>(Vector2D());
			chara[charaCount]->Initialize();
		}
	}
	else
	{
		if (charaCount < MAX_ENEMY_CHARACTOR && chara[charaCount] == nullptr)
		{
			//���̃e�L
			chara[charaCount] = this->scene->CreateObject<Kin>(Vector2D());
			chara[charaCount]->Initialize();
		}
	}
}

//�L�����N�^�[�擾
GameObject** Enemy_O::GetCharacter(int count)
{
	return chara;
}
*********************************/