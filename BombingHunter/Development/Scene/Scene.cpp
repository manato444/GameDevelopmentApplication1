#include"Scene.h"
#include"DxLib.h"

#include"../Objects/Player/Player.h"
#include"../Objects/Bullet/Bullet.h"
//#include"../Objects/Enemy/Enemy_O.h"

#include"../Objects/Enemy/Hakoteki.h"
#include"../Objects/Enemy/Haneteki.h"
#include"../Objects/Enemy/Harpie.h"
#include"../Objects/Enemy/Kin.h"

//�R���X�g���N�^
Scene::Scene() : 
				objects(), image(NULL),
				enemy_popcount(0),
				chara_count(0)
{
}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{

	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 50.0f));

	//�w�i��`��
	image = LoadGraph("image/�w�i/�w�i1.png");
}

void Scene::Update()
{
	//���������Q�b���ƂɓG�𐶐�
	if (enemy_popcount >= 250)
	{
		//�G�̏o���^�C�v�𗐐��Ŏ擾
		t = GetRand(1) + 1;

		//�G�̎�ނ������_���Ō��߂Đ���
		randomchar();

		enemy_popcount = 0;
	}
	else
	{
		enemy_popcount++;
	}

	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bullet>(Vector2D(320.0f, 50.0f));
	}

	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}
}

//�`�揈��
void Scene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(0, 0, image, TRUE);

	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�I������
void Scene::Finalize()
{
	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�z��̉��
	objects.clear();

}

//�G�̎�ނ������_���Ō��߂Đ������鏈��
void Scene::randomchar()
{

	//1����100�܂ł̗������擾
	int num = rand() % 100 + 1;

	if (num <= 60)
	{
		if (chara_count < MAX_ENEMY_CHARACTOR)
		{
			//�n�l�e�L�𐶐�
			CreateObject<Haneteki>(Vector2D(0.0f, 0.0f));
		}
	}
	else if (num <= 75)
	{
		if (chara_count < MAX_ENEMY_CHARACTOR)
		{
			//�n�R�e�L�𐶐�
			CreateObject<Hakoteki>(Vector2D(0.0f, 00.0f));
		}
	}
	else if (num <= 90)
	{
		if (chara_count < MAX_ENEMY_CHARACTOR)
		{
			//�n�[�s�[�𐶐�
			CreateObject<Harpie>(Vector2D(0.0f, 0.0f));
		}
	}
	else
	{
		if (chara_count < MAX_ENEMY_CHARACTOR)
		{
			//���̃e�L�𐶐�
			CreateObject<Kin>(Vector2D(0.0f, 0.0f));
		}
	}
}
