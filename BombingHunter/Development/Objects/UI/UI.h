#pragma once

#include"../../Utility/Vector2D.h"

class UI
{
private:


public:
	UI();	//�R���X�g���N�^
	~UI();	//�f�X�g���N�^

	void Initialize();	//������
	void Update();		//�X�V����
	void Draw() const;	//�`��
	void Finalize();	//�I��

	Vector2D SetEnemyLocation_Type1();	//�G�̈ʒu���擾
	Vector2D SetEnemyLocation_Type2();	//�G�̈ʒu���擾


};