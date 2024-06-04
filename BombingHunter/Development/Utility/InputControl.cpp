#include"InputControl.h"
#include "DxLib.h"

/*
//�ÓI�����o�ϐ���`
char InputControl::now_key[D_KEYCODE_MAX] = {};
char InputControl::old_key[D_KEYCODE_MAX] = {};

void InputControl::Update()
{
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));

	GetHitKeyStateAll(now_key);
}

bool InputControl::GetKey(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) &&
		(old_key[key_code] == TRUE));
}

bool InputControl::GetKeyDown(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) &&
		(old_key[key_code] == FALSE));
}

bool InputControl::GetKeyUp(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == FALSE) &&
		(old_key[key_code] == TRUE));
}

bool InputControl::CheckKeyCodeRange(int key_code)
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}
*/


#include"InputControl.h"
#include"DxLib.h"

//�ÓI�����o�ϐ���`
InputControl* InputControl::instance = nullptr;

//���͐���N���X�̃C���X�^���X�擾���鏈��
InputControl* InputControl::GetInstance()
{
	//�C���X�^���X��������΁A��������
	if (instance == nullptr)
	{
		instance = new InputControl();
	}

	//�������g�̃|�C���^��ԋp����
	return instance;
}

//���͐���N���X�̃C���X�^���X�폜���鏈��
void InputControl::DeleteInstance()
{
	//�C���X�^���X�����݂��Ă���΁A�폜����
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

//�X�V����
void InputControl::Update()
{

	//�O����͒l�̍X�V
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));

	//���ݓ��͒l�̍X�V
	GetHitKeyStateAll(now_key);


	//XInput�R���g���[���[�̓��͒l���擾����
	XINPUT_STATE input_state = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &input_state);


	//�{�^���̓��͒l�̍X�V
	for (int i = 0; i < D_BUTTON_MAX; i++)
	{
		old_button[i] = now_button[i];
		now_button[i] = (bool)input_state.Buttons[i];
	}

	//���X�e�B�b�N�̉��E�c���l( -32768 �` 32767 ) -> SHRT_MAX�Ŋ��邱�Ƃōő�l��{-1.0f, 1.0f}�ɂ���
	stick[0].x = input_state.ThumbLX / (float)SHRT_MAX;
	stick[0].y = input_state.ThumbLY / (float)SHRT_MAX;

	//�E�X�e�B�b�N�̉��E�c���l( -32768 �` 32767 ) -> SHRT_MAX�Ŋ��邱�Ƃōő�l��{-1.0, 1.0f}�ɂ���
	stick[1].x = input_state.ThumbRX / (float)SHRT_MAX;
	stick[1].y = input_state.ThumbRY / (float)SHRT_MAX;

	//�g���K�[�̓��͒l��ݒ�(0 �` 255) -> �ő�l��1.0f�ɐݒ�
	trigger[0] = (float)input_state.LeftTrigger / (float)UCHAR_MAX;
	trigger[1] = (float)input_state.RightTrigger / (float)UCHAR_MAX;


	//�}�E�X�z�C�[����]
	mouse_wheel = GetMouseWheelRotVol();
}

//�L�[��������Ă��邩�m�F
bool InputControl::GetKey(int key_code) const
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) &&
		(old_key[key_code] == TRUE));
}

//�L�[�������ꂽ�u�Ԃ��m�F
bool InputControl::GetKeyDown(int key_code) const
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) &&
		(old_key[key_code] == FALSE));
}

//�L�[�������ꂽ�u�Ԃ��m�F
bool InputControl::GetKeyUp(int key_code) const
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) &&
		(old_key[key_code] == TRUE));
}

//�L�[�R�[�h�͈͓̔����m�F
bool InputControl::CheckKeyCodeRange(int key_code) const
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}

/* - - - - - - - - - - - - - - - -< XInput >- - - - - - - - - - - - - - - - - - - - - - - */

//�{�^���擾�F�����Ă����
bool InputControl::GetButton(int button) const
{
	return CheckButtonRange(button) && (now_button[button] && old_button[button]);
}

//�{�^���擾�F�������u��
bool InputControl::GetButtonDown(int button) const
{
	return CheckButtonRange(button) && (now_button[button] && !old_button[button]);
}

//�{�^���擾�F�������u��
bool InputControl::GetButtonUp(int button)const
{
	return CheckButtonRange(button) && (!now_button[button] && old_button[button]);
}

//�{�^���z��͈̓`�F�b�N
bool InputControl::CheckButtonRange(int button)const
{
	return (0 <= button && button < 16);
}

//���X�e�B�b�N�̒l���擾���鏈��
Vector2D InputControl::GetLeftStick()const
{
	return stick[0];
}
//�E�X�e�B�b�N�̒l���擾���鏈��
Vector2D InputControl::GetRightStick()const
{
	return stick[1];
}

//���g���K�[�̒l���擾����
float InputControl::GetLeftTrigger() const
{
	return trigger[0];
}

//�E�g���K�[�̒l���擾����
float InputControl::GetRightTrigger() const
{
	return trigger[1];
}

/* - - - - - - - - - - - - - - - -< �}�E�X���� >- - - - - - - - - - - - - - - - - - - - - - - */

//�}�E�X�J�[�\�����W�擾
void InputControl::GetMousePosition(int& x, int& y)
{

	GetMousePoint(&x, &y);
}

//�}�E�X�E�{�^������(���N���b�N)
bool InputControl::IsMouseClick_Left()
{
	return GetMouseInput() & MOUSE_INPUT_LEFT;
}

//�}�E�X�E�{�^������(�E�N���b�N)
bool InputControl::IsMouseClick_Right()
{
	return GetMouseInput() & MOUSE_INPUT_RIGHT;
}

//�}�E�X�����{�^������(�����N���b�N)
bool InputControl::IsMouseClick_Middle()
{
	return GetMouseInput() & MOUSE_INPUT_MIDDLE;
}

//�}�E�X�z�C�[����]�ʂ��擾
int InputControl::GetMouseWheel()
{
	return mouse_wheel;
}