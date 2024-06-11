#include"DxLib.h"
#include"Utility/InputControl.h"
#include"Scene/Scene.h"

#include <iostream>
#include <windows.h> // Windows APIのヘッダー

//メイン関数
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	//ウィンドウモードで起動
	ChangeWindowMode(TRUE);

	//ウィンドウサイズ(横：640px, 縦：480px)を設定
	SetGraphMode(640, 480, 32);

	//ウィンドウのタイトルを設定
	SetMainWindowText("爆撃ハンターC++");

	//ウィンドウサイズを手動で変更できる
	SetWindowSizeChangeEnableFlag(TRUE, TRUE);

	//DXライブラリの初期化
	if (DxLib_Init() == -1)
	{
		//異常を通知
		return -1;
	}

	//ローカル変数定義
	Scene* scene = new Scene(); //シーン情報
	int result = 0;				//終了状態情報

	//描画先を裏画面から始めるように指定する
	SetDrawScreen(DX_SCREEN_BACK);

	try
	{
		//シーンの初期化
		scene->Initialize();

		//メインループ
		while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != TRUE)
		{

				//入力機能：更新処理
			InputControl* input = InputControl::GetInstance();

			//オブジェクトの更新処理
			input->Update();

			//シーンの更新処理
			scene->Update();

			//画面の初期化
			ClearDrawScreen();

			//シーンの描画処理
			scene->Draw();

			//裏画面の内容を表画面に反映する
			ScreenFlip();
		}
	}
	catch (const char* error_log)
	{
		//エラー情報をLog.txtに出力する
		OutputDebugString(error_log);

		//異常状態に変更する
		result = -1;
	}
	//シーン情報を削除する
	if (scene != nullptr)
	{
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}

	//DXライブラリの終了時処理
	DxLib_End();

	//終了状態を通知
	return result;
}