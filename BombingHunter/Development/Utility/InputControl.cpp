#include"InputControl.h"
#include "DxLib.h"

/*
//静的メンバ変数定義
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

//静的メンバ変数定義
InputControl* InputControl::instance = nullptr;

//入力制御クラスのインスタンス取得する処理
InputControl* InputControl::GetInstance()
{
	//インスタンスが無ければ、生成する
	if (instance == nullptr)
	{
		instance = new InputControl();
	}

	//自分自身のポインタを返却する
	return instance;
}

//入力制御クラスのインスタンス削除する処理
void InputControl::DeleteInstance()
{
	//インスタンスが存在していれば、削除する
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

//更新処理
void InputControl::Update()
{

	//前回入力値の更新
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));

	//現在入力値の更新
	GetHitKeyStateAll(now_key);


	//XInputコントローラーの入力値を取得する
	XINPUT_STATE input_state = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &input_state);


	//ボタンの入力値の更新
	for (int i = 0; i < D_BUTTON_MAX; i++)
	{
		old_button[i] = now_button[i];
		now_button[i] = (bool)input_state.Buttons[i];
	}

	//左スティックの横・縦軸値( -32768 ～ 32767 ) -> SHRT_MAXで割ることで最大値を{-1.0f, 1.0f}にする
	stick[0].x = input_state.ThumbLX / (float)SHRT_MAX;
	stick[0].y = input_state.ThumbLY / (float)SHRT_MAX;

	//右スティックの横・縦軸値( -32768 ～ 32767 ) -> SHRT_MAXで割ることで最大値を{-1.0, 1.0f}にする
	stick[1].x = input_state.ThumbRX / (float)SHRT_MAX;
	stick[1].y = input_state.ThumbRY / (float)SHRT_MAX;

	//トリガーの入力値を設定(0 ～ 255) -> 最大値を1.0fに設定
	trigger[0] = (float)input_state.LeftTrigger / (float)UCHAR_MAX;
	trigger[1] = (float)input_state.RightTrigger / (float)UCHAR_MAX;


	//マウスホイール回転
	mouse_wheel = GetMouseWheelRotVol();
}

//キーが押されているか確認
bool InputControl::GetKey(int key_code) const
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) &&
		(old_key[key_code] == TRUE));
}

//キーが押された瞬間か確認
bool InputControl::GetKeyDown(int key_code) const
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) &&
		(old_key[key_code] == FALSE));
}

//キーが離された瞬間か確認
bool InputControl::GetKeyUp(int key_code) const
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) &&
		(old_key[key_code] == TRUE));
}

//キーコードの範囲内か確認
bool InputControl::CheckKeyCodeRange(int key_code) const
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}

/* - - - - - - - - - - - - - - - -< XInput >- - - - - - - - - - - - - - - - - - - - - - - */

//ボタン取得：押している間
bool InputControl::GetButton(int button) const
{
	return CheckButtonRange(button) && (now_button[button] && old_button[button]);
}

//ボタン取得：押した瞬間
bool InputControl::GetButtonDown(int button) const
{
	return CheckButtonRange(button) && (now_button[button] && !old_button[button]);
}

//ボタン取得：離した瞬間
bool InputControl::GetButtonUp(int button)const
{
	return CheckButtonRange(button) && (!now_button[button] && old_button[button]);
}

//ボタン配列範囲チェック
bool InputControl::CheckButtonRange(int button)const
{
	return (0 <= button && button < 16);
}

//左スティックの値を取得する処理
Vector2D InputControl::GetLeftStick()const
{
	return stick[0];
}
//右スティックの値を取得する処理
Vector2D InputControl::GetRightStick()const
{
	return stick[1];
}

//左トリガーの値を取得する
float InputControl::GetLeftTrigger() const
{
	return trigger[0];
}

//右トリガーの値を取得する
float InputControl::GetRightTrigger() const
{
	return trigger[1];
}

/* - - - - - - - - - - - - - - - -< マウス入力 >- - - - - - - - - - - - - - - - - - - - - - - */

//マウスカーソル座標取得
void InputControl::GetMousePosition(int& x, int& y)
{

	GetMousePoint(&x, &y);
}

//マウス右ボタン入力(左クリック)
bool InputControl::IsMouseClick_Left()
{
	return GetMouseInput() & MOUSE_INPUT_LEFT;
}

//マウス右ボタン入力(右クリック)
bool InputControl::IsMouseClick_Right()
{
	return GetMouseInput() & MOUSE_INPUT_RIGHT;
}

//マウス中央ボタン入力(中央クリック)
bool InputControl::IsMouseClick_Middle()
{
	return GetMouseInput() & MOUSE_INPUT_MIDDLE;
}

//マウスホイール回転量を取得
int InputControl::GetMouseWheel()
{
	return mouse_wheel;
}