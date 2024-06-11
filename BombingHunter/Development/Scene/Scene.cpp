#include"Scene.h"
#include"DxLib.h"

//�R���X�g���N�^
Scene::Scene() :
	objects(),f_image(NULL),
	enemy_popcount(0),
	chara_count(0),
	bx(0)
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
	chara_count = 0;

	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 50.0f));


	//�w�i��`��(�C���ŕς���)
	//image = LoadGraph("image/�w�i/�w�i1.png"); //	�����n���^�[�p�w�i
	//f_image = LoadGraph("image/�w�i/�t���[��.png");	//�g(?)
	//image = LoadGraph("image/�w�i/back1.png");	//?
	image[0] = LoadGraph("image/�w�i/space.bmp");	//�F���w�i
	//image[0] = LoadGraph("image/�w�i/�w�i.png"); //�����n���^�[�����ւ��w�i
	image[1] = LoadGraph("image/��������/timer.png");
	image[2] = LoadGraph("image/�X�R�A/�X�R�A.png");


	//�o���^�C�v�𗐐��Ŏ擾(�X�|�[���ʒu�̐ݒ�)�@<--�v��Ȃ�
	//type = GetRand(1) + 1;
}

void Scene::Update()
{
	//�w�i�摜�̕`��ʒu���X�V
	bx += 2;
	//bx = 0;

	//���������Q�b���ƂɓG�𐶐�
	if (enemy_popcount >= 250){
		//�G�̎�ނ������_���Ō��߂Đ���	
		randomchar();
		enemy_popcount = 0;
	}
	else {
		enemy_popcount++;
	}
	for (chara_count = 0; chara_count < MAX_ENEMY_CHARACTOR; chara_count++){
		if (chara_count == NULL)
		{
			break;
		}
	}
	//���͋@�\�F�X�V����
	InputControl* input = InputControl::GetInstance();

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
	//�X�y�[�X�L�[��Bullet�𐶐�
	for (int i = 0; i < objects.size(); i++)
	{
		if (input->GetKeyDown(KEY_INPUT_SPACE) || input->GetButtonDown(12)) {

			if (flg == false)
			{
				flg = true;
				//�v���C���[��������ʒu�����擾���Ēe�𐶐�����
				if ((dynamic_cast<Player*>(objects[i]) != nullptr)) {
					//Bullet�𐶐�
					CreateObject<Bullet>(objects[i]->GetLocation());
				}
			}
		}
	}
	//Bullet��ʊO�`�F�b�N
	Check_OffScreen();
}

//�`�揈��
void Scene::Draw() const
{
	//�w�i�摜�̕`��
	DrawGraph(bx % 640, 0, image[0], TRUE);
	DrawGraph(bx % 640 - 640, 0, image[0], TRUE);
	//DrawGraph(0, 0, image[0], TRUE);

	//UI�̕`��i���j
	DrawGraph(10, 450, image[1], TRUE); 
	DrawGraph(210, 450, image[2], TRUE);

	
	//DrawGraph(0, bx % 480 - 480, image, TRUE);
	//DrawGraph(0, 0, f_image, TRUE);



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
	if (objects.empty()){
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
	int r = rand() % 100 + 1;

	if (num <= 50){
		if (chara_count < MAX_ENEMY_CHARACTOR) {
			//�n�l�e�L�𐶐�
			if (r <= 50){
				CreateObject<Haneteki>(Vector2D(10.0f, 300.0f));
			}
			else{
				CreateObject<Haneteki>(Vector2D(10.0f, 180.0f));
			}
		}		
	}
	else if (num <= 75){
		if (chara_count < MAX_ENEMY_CHARACTOR){
			//�n�R�e�L�𐶐�
			CreateObject<Hakoteki>(Vector2D(620.0f, 370.0f));
		}
	}
	else if (num <= 90){
		if (chara_count < MAX_ENEMY_CHARACTOR){
			//�n�[�s�[�𐶐�
			CreateObject<Harpie>(Vector2D(10.0f, 230.0f));
		}
	}
	else{
		if (chara_count < MAX_ENEMY_CHARACTOR){
			//���̃e�L�𐶐�
			CreateObject<Kin>(Vector2D(620.0f, 420.0f));
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
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����i���ʂ��ď������Ƃ�ʒm�j
		a->OnHitCollision(b);
		b->OnHitCollision(a);

		//�I�u�W�F�N�g���폜((��������܂�낵���Ȃ��B
		DeleteObject(a);
		//DeleteObject(b);
	}
}
//�I�u�W�F�N�g���폜����
void Scene::DeleteObject(GameObject* hit_object)
{
	for (int i = 0; i < objects.size(); i++){	//�I�u�W�F�N�g�𒲂ׂ�	
		for (GameObject* obj : objects)	//�V�[���ɑ��݂���I�u�W�F�N�g�̃f�[�^�𒲂ׂ�
		{	
			//�폜�ʒm���󂯎������
			if (obj->D_Objects() == true)
			{
				//�����Ăق����I�u�W�F�N�g�� "�n�l�e�L" �ƒʒm�����Ă�����폜
				if ((dynamic_cast<Haneteki*>(objects[i]) == hit_object))
				{
					delete objects[i];		//�������̉��
					objects.erase(objects.begin() + i);	//�v�f�̍폜
					DeleteBullet();	//�V�[���ɒe�����݂��Ă���΍폜
					break;	//���[�v�𔲂���
				}
				//�����Ăق����I�u�W�F�N�g�� "�n�R�e�L" �ƒʒm�����Ă�����폜
				else if ((dynamic_cast<Hakoteki*>(objects[i]) == hit_object))
				{
					delete objects[i];		//�������̉��
					objects.erase(objects.begin() + i);	//�v�f�̍폜
					DeleteBullet();	//�V�[���ɒe�����݂��Ă���΍폜
					break;	//���[�v�𔲂���
				}
				//�����Ăق����I�u�W�F�N�g�� "�n�[�s�[" �ƒʒm�����Ă�����폜
				else if ((dynamic_cast<Harpie*>(objects[i]) == hit_object))
				{
					delete objects[i];		//�������̉��
					objects.erase(objects.begin() + i);	//�v�f�̍폜
					DeleteBullet();	//�V�[���ɒe�����݂��Ă���΍폜
					break;	//���[�v�𔲂���
				}
				//�����Ăق����I�u�W�F�N�g�� "���̃e�L" �ƒʒm�����Ă�����폜
				else if ((dynamic_cast<Kin*>(objects[i]) == hit_object))
				{
					delete objects[i];		//�������̉��
					objects.erase(objects.begin() + i);	//�v�f�̍폜
					DeleteBullet();	//�V�[���ɒe�����݂��Ă���΍폜
					break;	//���[�v�𔲂���
				}
			}
		}
	}
}
//��ʊO����
void Scene::Check_OffScreen()
{
	//�ϐ���`
	Vector2D bl;
	//�z���Bullet�����邩�ЂƂ��`�F�b�N����
	for (int i = 0; i < objects.size(); i++){
		//Bullet��������ʒu�����擾
		if ((dynamic_cast<Bullet*>(objects[i]) != nullptr))
		{
			bl = objects[i]->GetLocation();

			//�e����ԉ��ɗ�������폜����
			if (bl.y > 460.0f)
			{
				delete objects[i];	//�����������
				this->objects.erase(objects.begin() + i);	//�v�f�̍폜
				i--;	//�v�f�̈ʒu�������C���f�b�N�X������Ȃ��悤�ɖh�~
				flg = false;
			}
		}
		//"�n�l�e�L"��"�n�[�s�[" ��������ʒu�����擾 
		if ((dynamic_cast<Haneteki*>(objects[i]) != nullptr) ||
			(dynamic_cast<Harpie*>(objects[i]) != nullptr))
		{
			bl = objects[i]->GetLocation();

			if (bl.x > 640.0f)
			{
				delete objects[i];	//�����������
				this->objects.erase(objects.begin() + i);	//�v�f�̍폜
				i--;	//�v�f�̈ʒu�������C���f�b�N�X������Ȃ��悤�ɖh�~
			}
		}
		//"�n�R�e�L" �� "���̃e�L" ��������ʒu�����擾 
		if ((dynamic_cast<Hakoteki*>(objects[i]) != nullptr) ||
			(dynamic_cast<Kin*>(objects[i]) != nullptr))
		{
			bl = objects[i]->GetLocation();

			if (bl.x < 0.0f)
			{
				delete objects[i];	//�����������
				this->objects.erase(objects.begin() + i);	//�v�f�̍폜
				i--;	//�v�f�̈ʒu�������C���f�b�N�X������Ȃ��悤�ɖh�~
			}
		}
	}
}
//�e����������
void Scene::DeleteBullet()
{
	for (int i = 0; i < objects.size(); i++) {

		// " �e "���V�[���ɑ��݂��Ă���΍폜
		if ((dynamic_cast<Bullet*>(objects[i]) != nullptr))
		{
			delete objects[i];		//�������̉��
			objects.erase(objects.begin() + i);	//�v�f�̍폜
			flg = false;	//�e�𐶐��ł���悤�ɂ���
			i--;	//�v�f�̈ʒu�������C���f�b�N�X������Ȃ��悤�ɖh�~
		}
	}
}

//void Scene::Enemy_Bullet()
//{
//	for (int i = 0; i < objects.size(); i++)
//	{
//		//�v���C���[��������ʒu�����擾���Ēe�𐶐�����
//		if ((dynamic_cast<Haneteki*>(objects[i]) != nullptr))
//		{
//			//Bullet�𐶐�x
//			//CreateObject<E_Bullet>(objects[i]->GetLocation())
//			e_position = objects[i]->GetLocation();
//		}
//		if ((dynamic_cast<Player*>(objects[i]) != nullptr))
//		{
//			p_position = objects[i]->GetLocation();
//		}
//
//		direction = p_position - e_position;
//			
//			float bs = 1.5f;
//			Vector2D Bv = direction * bs;
//
//			CreateObject<E_Bullet>(e_position);
//	}
//}

/*--�v��Ȃ�
//�o���p�^�[�����Z�b�g(�^�C�v1 : ������o��������)
Vector2D Scene::One_Type_Location()
{
	return Vector2D(60, 200);
}
//�o���p�^�[�����Z�b�g(�^�C�v2 : �E����o��������)
Vector2D Scene::Two_Type_Location()
//{
//	return Vector2D(600, 300);
//}
//*/


