#pragma once

#include<map>
#include<string>
#include<vector>

/**
	* @param	file_name	ファイルパス
	* @param	all_num		画像の総数
	* @param	num_x		横の総数
	* @param	num_y		縦の総数
	* @param	size_x		横のサイズ(px)
	* @param	size_y		縦のサイズ(px)
 */
struct MaterialParam
{
	std::string file_path;
	int all_num;
	int num_x;
	int num_y;
	int size_x;
	int size_y;
};

//リソース管理クラス
class ResourceManager
{
private:
	//自クラスのポインタ(アドレス先に実体がある)
	static ResourceManager* instance;

	//画像格納コンテナ
	std::map<std::string, std::vector<int>> image_container;

	//音源格納コンテナ
	std::map<std::string, int> sound_container;

private:
	//コンストラクタをプライベートにすることで、
	//自クラスのメンバ関数でしかインスタンスを生成出来ないようにする
	ResourceManager() = default;

	//コピーガード
	//クラス外でインスタンスを生成して渡すことが出来ないようにする
	ResourceManager(ResourceManager& v) = delete;
	ResourceManager& operator = (const ResourceManager& v) = delete;
	//~コピーガード

public:
	~ResourceManager() = default;

public:
	/// <summary>
	/// リソース管理クラスのインスタンス取得処理
	/// </summary>
	/// <returns>クラスのポインタ</returns>
	static ResourceManager* GetInstance();

	/// <summary>
	/// リソース管理クラスのインスタンス削除処理
	/// </summary>
	static void DeleteInstance();

public:

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
	const std::vector<int>& GetImages(std::string file_name, int all_num = 1,
		int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);
	const std::vector<int>& GetImages(const char* file_name, int all_num = 1,
		int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);
	const std::vector<int>& GetImages(MaterialParam element);

	/**
	*全ての画像を削除する
	*@param material_handle 削除したい画像ハンドルのstd::vector配列
	*/
	void UnloadResourcesAll();

private:
	/**
	*画像ハンドルを読み込みリソースを作成する
	*@param file_name ファイルパス
	*/
	void CreateImagesResource(std::string file_name);
	/**
	*画像ハンドルを読み込みリソースを作成する
	*@param file_name ファイルパス
	*@param all_num 画像の総数
	*@param num_x 横の総数
	*@param num_y 縦の総数
	*@param size_x 横のサイズ(px)
	*@param size_y 縦のサイズ(px)
	*/
	void  CreateImagesResource(std::string file_name, int all_num, int num_x, int num_y,
		int size_x, int size_y);

	/* - - - - - - - - - - - - < 音源読み込み機能 > - - - - - - - - - - - - - - - - - - - - */

public:
	/// <summary>
	/// 音源取得処理
	/// </summary>
	/// <param name="ファイルパス"></param>
	/// <returns>読み込んだ音源ハンドルを返却</returns>
	int GetSound(const std::string& file_name);

private:
	/**
	* 音源を読み込んでリソースマップに追加
	*@param file_name ファイルパス
	*/
	void CreateSoundResource(std::string file_name);

public:
	//全ての音源を削除する処理
	void UnloadSoundResouecesAll();
};
