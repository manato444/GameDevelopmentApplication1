#pragma once

#include<vector>
#include<string>
#include"../Objects/GameObject.h"
#include"../Utility/InputControl.h"
#include"../Objects/UI/UI.h"

//�v���C���[
#include"../Objects/Player/Player.h"
#include"../Objects/Bullet/Bullet.h"

//�G
#include"../Objects/Enemy/Hakoteki.h"
#include"../Objects/Enemy/Haneteki.h"
#include"../Objects/Enemy/Harpie.h"
#include"../Objects/Enemy/Kin.h"
#include"../Objects/Bullet/EnemyBullet.h"

//�G�t�F�N�g
#include"../Objects/Effect/Effect.h"


//�G�L�����N�^�[�̍ő吔
#define MAX_ENEMY_CHARACTOR 200

class Scene
{
private:
	//�Q�[���I�u�W�F�N�g�𓮓I�z��ŊǗ�
	std::vector<GameObject*> objects;

	bool flg = false;

	int image[3];		//�摜
	int f_image;		//�g
	int e_cnt = 0;			//enemy�J�E���g
	int enemy_popcount;			//�o��������L�������J�E���g
	int chara_count;				//�L������
	//int type;							//�L�����^�C�v

	int bx;	//�w�i�̕`��ʒu
	
	//Vector2D One_Type_Location();
	//Vector2D Two_Type_Location();

public:
	Scene();	//�R���X�g���N�^
	~Scene();	//�f�X�g���N�^

	void Initialize();	//����������
	void Update();		//�X�V����
	void Draw() const;	//�`�揈��
	void Finalize();	//�I��������

	//�G�̎�ނ������_���Ō��߂鏈��
	void randomchar();	

	//void Enemy_Bullet();

	//�L�����J�E���g���擾
	int GetCharaCount() { return this->chara_count; }

	//��ʊO�`�F�b�N
	void Check_OffScreen();

	//�I�u�W�F�N�g���폜���鏈��
	void DeleteObject(GameObject* hit_object);
	
public:

	//�����蔻��`�F�b�N����
	void HitCheckObject(GameObject* a, GameObject* b);
	//bool IsHitCheck(GameObject* a, GameObject* b);

	//�I�u�W�F�N�g��������
	template<class T>
	T* CreateObject(const Vector2D& location)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();

		//GameObject�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
		}

		//����������
		new_object->Initialize();

		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}
};