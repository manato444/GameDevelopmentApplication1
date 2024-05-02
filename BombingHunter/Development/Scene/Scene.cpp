#include"Scene.h"
#include"DxLib.h"

//�v���C���[
#include"../Objects/Player/Player.h"
#include"../Objects/Bullet/Bullet.h"

//�G
#include"../Objects/Enemy/Hakoteki.h"
#include"../Objects/Enemy/Haneteki.h"
#include"../Objects/Enemy/Harpie.h"
#include"../Objects/Enemy/Kin.h"

Hakoteki* hakoteki;


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
	if (enemy_popcount >= 250){

		randomchar();		//�G�̎�ނ������_���Ō��߂Đ���	
		enemy_popcount = 0;		
	}
	else{
		enemy_popcount++;
	}

	//�X�y�[�X�L�[��Bullet�𐶐�
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		CreateObject<Bullet>(Vector2D(320.0f, 50.0f));	
	}

	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
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

	if (num <= 50)
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
			CreateObject<Hakoteki>(Vector2D(0.0f, 0.0f));
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


//�����蔻��`�F�b�N����(��`�̒��S�œ����蔻����Ƃ�)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	if ((fabsf(diff.x) < box_size.x) && (fabs(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}