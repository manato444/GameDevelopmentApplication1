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

//Hakoteki* hakoteki;

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
	//image = LoadGraph("image/�w�i/�w�i1.png"); //	�����n���^�[�p�w�i
	f_image = LoadGraph("image/�w�i/�t���[��.png");	//�g(?)
	image = LoadGraph("image/�w�i/space.bmp");	//�F���w�i

	//�o���^�C�v�𗐐��Ŏ擾(�X�|�[���ʒu�̐ݒ�)
	//type = GetRand(1) + 1;

	

}

void Scene::Update()
{
	//�w�i�摜�̕`��ʒu���X�V
	bx += 1;

	//���������Q�b���ƂɓG�𐶐�
	if (enemy_popcount >= 250)
	{
		//�G�̎�ނ������_���Ō��߂Đ���	
		randomchar();
		enemy_popcount = 0;
	}
	else {
		enemy_popcount++;
	}


	//�X�y�[�X�L�[��Bullet�𐶐�
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		//�z���Player�����邩�ЂƂ��`�F�b�N����
		for (int i = 0; i < objects.size(); i++)
		{
			//�v���C���[��������ʒu�����擾���Ēe�𐶐�����
			if (!(dynamic_cast<Player*>(objects[i]) == nullptr))
			{
				//Bullet�𐶐�
				CreateObject<Bullet>(objects[i]->GetLocation());
			}
		}
	}

	//Bullet��ʊO�`�F�b�N
	//Check_OffScreen();

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
			if (!(dynamic_cast<Haneteki*>(objects[i]) == nullptr))
			{
				if (!(dynamic_cast<Bullet*>(objects[j]) == nullptr))
				{
					//�����蔻��`�F�b�N����
					HitCheckObject(objects[i], objects[j]);
				}
			}
		}
	}
	
}

//�`�揈��
void Scene::Draw() const
{
	//�w�i�摜�̕`��
	//DrawGraph(bx % 640, 0, image, TRUE);
	//DrawGraph(bx % 640 - 640, 0, image, TRUE);

	DrawGraph(0, bx % 480, image, TRUE);
	DrawGraph(0, bx % 480 - 480, image, TRUE);

	DrawGraph(0, 0, f_image, TRUE);


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
			CreateObject<Haneteki>(Vector2D(10.0f, 300.0f));

			/*
			if (type == 1) {
				//�X�|�[���ʒu���y���z�ɐݒ�
				CreateObject<Haneteki>(Vector2D(One_Type_Location()));
			}
			else if (type == 2) {
				//�X�|�[���ʒu���y�E�z�ɐݒ�
				CreateObject<Haneteki>(Vector2D(Two_Type_Location()));
			}
			*/
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

		//�v�f�̍폜
		objects.erase(objects.begin() + 1);

	}
}

/*
//��ʊO����
void Scene::Check_OffScreen()
{
	//�ϐ���`
	Vector2D bl;

	//�z���Bullet�����邩�ЂƂ��`�F�b�N����
	for (int i = 0; i < objects.size(); i++)
	{
		//Bullet��������ʒu�����擾
		if (!(dynamic_cast<Bullet*>(objects[i]) == nullptr))
		{
			bl = objects[i]->GetLocation();

			if (bl.y > 380.0f)
			{
				//�v�f�̍폜
				this->objects.erase(objects.begin() + 1);
			}
		}
	}
}
*/


/*
//�o���p�^�[�����Z�b�g(�^�C�v1 : ������o��������)
Vector2D Scene::One_Type_Location()
{
	return Vector2D(60, 200);
}
//�o���p�^�[�����Z�b�g(�^�C�v2 : �E����o��������)
Vector2D Scene::Two_Type_Location()
{
	return Vector2D(600, 300);
}
*/

