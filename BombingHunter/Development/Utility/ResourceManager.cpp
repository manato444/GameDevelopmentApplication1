#include "ResourceManager.h"
#include"DxLib.h"

//静的メンバ変数定義
ResourceManager* ResourceManager::instance = instance = nullptr;//クラスのインスタンスのポインタ

/// <summary>
/// リソース管理クラスのインスタンス取得
/// </summary>
/// <returns>クラスのポインタ</returns>
ResourceManager* ResourceManager::GetInstance()
{
	//インスタンスが無ければ、生成する
	if (instance == nullptr)
	{
		instance = new ResourceManager();
	}
	//自分自身のポインタを返却
	return instance;
}

/// <summary>
/// リソース管理クラスのインスタンス削除処理
/// </summary>
void ResourceManager::DeleteInstance()
{
	//インスタンスが存在していれば、削除する
	if (instance != nullptr)
	{
		instance->UnloadResourcesAll();	//全ての画像を削除
		instance->UnloadSoundResouecesAll(); //全ての音源を削除
		delete instance;
		instance = nullptr;
	}
}

/**
	/* 画像取得処理
	* @param	file_name	ファイルパス
	* @param	all_num		画像の総数
	* @param	num_x		横の総数
	* @param	num_y		縦の総数
	* @param	size_x		横のサイズ(px)
	* @param	size_y		縦のサイズ(px)
	* @return	読み込んだ画像ハンドルのstd::vector配列
	* */
const std::vector<int>& ResourceManager::GetImages(std::string file_name,
	int all_num, int num_x, int num_y, int size_x, int size_y)
{
	//コンテナ内に画像が無ければ、画像を読み込む
	if (image_container.count(file_name) == NULL)
	{
		//エラーチェック
		if (all_num == 1)
		{
			CreateImagesResource(file_name);
		}
		else
		{
			CreateImagesResource(file_name, all_num, num_x, num_y, size_x, size_y);
		}
	}
	//コンテナ内の画像データを返却
	return image_container[file_name];
}

const std::vector<int>& ResourceManager::GetImages(const char* file_name,
	int all_num, int num_x, int num_y, int size_x, int size_y)
{
	return GetImages(std::string(file_name), all_num, num_x, num_y, size_x, size_y);
}

const std::vector<int>& ResourceManager::GetImages(MaterialParam element)
{
	return GetImages(element.file_path, element.all_num, element.num_x,
		element.num_y, element.size_x, element.size_y);
}

/**
	*全ての画像を削除するメソッド
	*@param material_handle 削除したい画像ハンドルのstd::vector配列
*/
void ResourceManager::UnloadResourcesAll()
{
	//コンテナ内に画像が無ければ、処理を終了する
	if (image_container.size() == NULL)
	{
		return;
	}

	//全ての画像を削除
	for (std::pair<std::string, std::vector<int>> value : image_container)
	{
		//読み込んだ画像の解放
		DeleteSharingGraph(value.second[0]);
		//動的配列の解放
		value.second.clear();
	}

	//コンテナの解放
	image_container.clear();
}

/**
* 画像ハンドルを読み込みリソースを作成する
* @param file_name ファイルパス
*/
void ResourceManager::CreateImagesResource(std::string file_name)
{
	//指定されたファイルを読み込む
	int handle = LoadGraph(file_name.c_str());

	//エラーチェック
	if (handle == -1)
	{
		throw(file_name + "がありません\n");
	}

	//コンテナ内に読み込んだ画像を追加する
	image_container[file_name].push_back(handle);
}

/*
	*画像ハンドルを読み込みリソースを作成する
	*@param file_name ファイルパス
	*@param all_num 画像の総数
	*@param num_x 横の総数
	*@param num_y 縦の総数
	*@param size_x 横のサイズ(px)
	*@param size_y 縦のサイズ(px)
*/
void ResourceManager::CreateImagesResource(std::string file_name, int all_num,
	int num_x, int num_y, int size_x, int size_y)
{
	//指定されたファイルを読み込む
	int* handle = new int[all_num];
	int err = LoadDivGraph(file_name.c_str(), all_num, num_x, num_y, size_x, size_y,
		handle);

	//エラーチェック
	if (err == -1)
	{
		throw(file_name + "がありません\n");
	}

	//コンテナに読み込んだ画像を追加する
	for (int i = 0; i < all_num; i++)
	{
		image_container[file_name].push_back(handle[i]);
	}

	//動的メモリの解放
	delete[] handle;
}


/* - - - - - - - - - - - - < 音源読み込み機能 > - - - - - - - - - - - - - - - - - - - - */


/// <summary>
///	音源取得処理
/// </summary>
/// <param name="ファイルパス"></param>
/// <returns>読み込んだ音源ハンドル</returns>
int ResourceManager::GetSound(const std::string& file_name)
{
	//コンテナ内に音源が無ければ、画像を読み込む
	if (sound_container.count(file_name) == NULL)
	{
		CreateSoundResource(file_name);
	}

	//コンテナ内の音源データを返却
	return sound_container[file_name];
}

/*
	*音源ハンドルを読み込みリソースを作成する
	*@param file_name ファイルパス
*/
void ResourceManager::CreateSoundResource(std::string file_name)
{
	//指定されたファイルを読み込む
	int handle_s = LoadSoundMem(file_name.c_str());

	//エラーチェック
	if (handle_s == -1)
	{
		throw(file_name + "がありません\n");
	}

	//コンテナ内に読み込んだ音源を追加する
	sound_container[file_name] = handle_s;
}

/*
	*全ての音源を削除するメソッド
*/
void ResourceManager::UnloadSoundResouecesAll()
{
	//コンテナ内に音源が無ければ、処理を終了する
	if (sound_container.size() == NULL)
	{
		return;
	}

	//全ての音源を削除
	for (std::pair<std::string, int> s_value : sound_container)
	{
		//読み込んだ音源の解放
		DeleteSoundMem(s_value.second);
	}

	//コンテナの解放
	sound_container.clear();
}
