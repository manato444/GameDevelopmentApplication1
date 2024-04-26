#pragma once

#include "../Utility/Vector2D.h"
#include"UI/UI.h"

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D location;	//�ʒu���
	double scale;		//�傫��
	double radian;		//����
	int image;			//�`�悷��摜
	int sound;			//�Đ����鉹��
	int type;

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();		//����������
	virtual void Update();			//�X�V����
	virtual void Draw() const;		//�`�揈��
	virtual void Finalize();		//�I������

	//�G�̃^�C�v
	virtual void SetType(int type) {};

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	//�ʒu���擾����
	Vector2D GetLocation() const;

	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

	virtual Vector2D GetEnemyLocation_Type1() { return Vector2D(); }
	virtual Vector2D GetEnemyLocation_Type2() { return Vector2D(); }

	//void SetLocation();
};