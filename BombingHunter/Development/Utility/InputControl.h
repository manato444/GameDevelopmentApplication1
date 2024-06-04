#pragma once
/*

#define D_KEYCODE_MAX 256

//入力管理機能
class InputControl
{
private:
	static char now_key[D_KEYCODE_MAX];	//現在フレーム入力値
	static char old_key[D_KEYCODE_MAX];	//過去フレーム入力値

public:
	static void Update();	//更新処理

	//キー入力取得処理
	static bool GetKey(int key_code);
	static bool GetKeyDown(int key_code);
	static bool GetKeyUp(int key_code);

private:
	//キー配列範囲チェック
	static bool CheckKeyCodeRange(int key_code);

};
*/

#pragma once
#include"Vector2D.h"

//マクロ定義
#define D_KEYCODE_MAX 256	//キーコード最大数
#define D_BUTTON_MAX 16		//ボタン最大数

//入力制御クラス( キーボード・マウス・コントローラー )
class InputControl
{
private:
	//自クラスのポインタ
	static InputControl* instance;

	//キーボード入力値
	char now_key[D_KEYCODE_MAX];
	char old_key[D_KEYCODE_MAX];

private:
	//自クラスのメンバ関数でしかインスタンス生成を出来ないようにする
	InputControl() = default;

	//コピーガード
	//クラス外でインスタンスを生成して渡すことができないようにする
	InputControl(InputControl& v) = delete;
	InputControl& operator = (const InputControl& v) = delete;
	//~コピーガード

public:
	~InputControl() = default;

public:
	//インスタンス取得する処理
	static InputControl* GetInstance();
	//インスタンス削除する処理
	static void DeleteInstance();

public:
	void Update();	//更新処理
	bool GetKey(int key_code) const;		//押してる間
	bool GetKeyDown(int key_code) const;	//押した瞬間
	bool GetKeyUp(int key_code)const;		//離した瞬間

private:
	//キー入力の範囲を確認する
	bool CheckKeyCodeRange(int key_code) const;

	/* - - - - - - - - - - - - - - - -< XInput >- - - - - - - - - - - - - - - - - - - - - - - */

private:
	bool now_button[D_BUTTON_MAX];		//現在フレーム入力値
	bool old_button[D_BUTTON_MAX];		//過去フレーム入力値

	//スティック入力値 = { stick[0]:左スティック, stick[1]:右スティック }
	Vector2D stick[2];

	//トリガ－入力値 = { trigger[0]:左トリガー, trigger[1]:右トリガー }
	float trigger[2];

public:
	bool GetButton(int button)const;		//押し続けている間
	bool GetButtonDown(int button)const;	//押した瞬間
	bool GetButtonUp(int button)const;	//離した瞬間

	Vector2D GetLeftStick()const;	//左スティックの値を取得する
	Vector2D GetRightStick()const;	//右スティックの値を取得する

	float GetLeftTrigger()const;	//左トリガーの値を取得する
	float GetRightTrigger()const;	//右トリガーの値を取得する


private:
	//ボタン配列範囲チェック
	bool CheckButtonRange(int button)const;

	/* - - - - - - - - - - - - - - - -< マウス入力 >- - - - - - - - - - - - - - - - - - - - - - - */
private:
	int mouse_wheel;

public:

	void GetMousePosition(int& x, int& y);	//マウス座標取得

	bool IsMouseClick_Left();			//左クリック入力値
	bool IsMouseClick_Right();			//右クリック入力値
	bool IsMouseClick_Middle();			//中央クリック入力値

	int GetMouseWheel();

	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/

};
