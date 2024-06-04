#pragma once
/*

#define D_KEYCODE_MAX 256

//���͊Ǘ��@�\
class InputControl
{
private:
	static char now_key[D_KEYCODE_MAX];	//���݃t���[�����͒l
	static char old_key[D_KEYCODE_MAX];	//�ߋ��t���[�����͒l

public:
	static void Update();	//�X�V����

	//�L�[���͎擾����
	static bool GetKey(int key_code);
	static bool GetKeyDown(int key_code);
	static bool GetKeyUp(int key_code);

private:
	//�L�[�z��͈̓`�F�b�N
	static bool CheckKeyCodeRange(int key_code);

};
*/

#pragma once
#include"Vector2D.h"

//�}�N����`
#define D_KEYCODE_MAX 256	//�L�[�R�[�h�ő吔
#define D_BUTTON_MAX 16		//�{�^���ő吔

//���͐���N���X( �L�[�{�[�h�E�}�E�X�E�R���g���[���[ )
class InputControl
{
private:
	//���N���X�̃|�C���^
	static InputControl* instance;

	//�L�[�{�[�h���͒l
	char now_key[D_KEYCODE_MAX];
	char old_key[D_KEYCODE_MAX];

private:
	//���N���X�̃����o�֐��ł����C���X�^���X�������o���Ȃ��悤�ɂ���
	InputControl() = default;

	//�R�s�[�K�[�h
	//�N���X�O�ŃC���X�^���X�𐶐����ēn�����Ƃ��ł��Ȃ��悤�ɂ���
	InputControl(InputControl& v) = delete;
	InputControl& operator = (const InputControl& v) = delete;
	//~�R�s�[�K�[�h

public:
	~InputControl() = default;

public:
	//�C���X�^���X�擾���鏈��
	static InputControl* GetInstance();
	//�C���X�^���X�폜���鏈��
	static void DeleteInstance();

public:
	void Update();	//�X�V����
	bool GetKey(int key_code) const;		//�����Ă��
	bool GetKeyDown(int key_code) const;	//�������u��
	bool GetKeyUp(int key_code)const;		//�������u��

private:
	//�L�[���͈͂̔͂��m�F����
	bool CheckKeyCodeRange(int key_code) const;

	/* - - - - - - - - - - - - - - - -< XInput >- - - - - - - - - - - - - - - - - - - - - - - */

private:
	bool now_button[D_BUTTON_MAX];		//���݃t���[�����͒l
	bool old_button[D_BUTTON_MAX];		//�ߋ��t���[�����͒l

	//�X�e�B�b�N���͒l = { stick[0]:���X�e�B�b�N, stick[1]:�E�X�e�B�b�N }
	Vector2D stick[2];

	//�g���K�|���͒l = { trigger[0]:���g���K�[, trigger[1]:�E�g���K�[ }
	float trigger[2];

public:
	bool GetButton(int button)const;		//���������Ă����
	bool GetButtonDown(int button)const;	//�������u��
	bool GetButtonUp(int button)const;	//�������u��

	Vector2D GetLeftStick()const;	//���X�e�B�b�N�̒l���擾����
	Vector2D GetRightStick()const;	//�E�X�e�B�b�N�̒l���擾����

	float GetLeftTrigger()const;	//���g���K�[�̒l���擾����
	float GetRightTrigger()const;	//�E�g���K�[�̒l���擾����


private:
	//�{�^���z��͈̓`�F�b�N
	bool CheckButtonRange(int button)const;

	/* - - - - - - - - - - - - - - - -< �}�E�X���� >- - - - - - - - - - - - - - - - - - - - - - - */
private:
	int mouse_wheel;

public:

	void GetMousePosition(int& x, int& y);	//�}�E�X���W�擾

	bool IsMouseClick_Left();			//���N���b�N���͒l
	bool IsMouseClick_Right();			//�E�N���b�N���͒l
	bool IsMouseClick_Middle();			//�����N���b�N���͒l

	int GetMouseWheel();

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

};
