#pragma once

#include<map>
#include<string>
#include<vector>

/**
	* @param	file_name	�t�@�C���p�X
	* @param	all_num		�摜�̑���
	* @param	num_x		���̑���
	* @param	num_y		�c�̑���
	* @param	size_x		���̃T�C�Y(px)
	* @param	size_y		�c�̃T�C�Y(px)
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

//���\�[�X�Ǘ��N���X
class ResourceManager
{
private:
	//���N���X�̃|�C���^(�A�h���X��Ɏ��̂�����)
	static ResourceManager* instance;

	//�摜�i�[�R���e�i
	std::map<std::string, std::vector<int>> image_container;

	//�����i�[�R���e�i
	std::map<std::string, int> sound_container;

private:
	//�R���X�g���N�^���v���C�x�[�g�ɂ��邱�ƂŁA
	//���N���X�̃����o�֐��ł����C���X�^���X�𐶐��o���Ȃ��悤�ɂ���
	ResourceManager() = default;

	//�R�s�[�K�[�h
	//�N���X�O�ŃC���X�^���X�𐶐����ēn�����Ƃ��o���Ȃ��悤�ɂ���
	ResourceManager(ResourceManager& v) = delete;
	ResourceManager& operator = (const ResourceManager& v) = delete;
	//~�R�s�[�K�[�h

public:
	~ResourceManager() = default;

public:
	/// <summary>
	/// ���\�[�X�Ǘ��N���X�̃C���X�^���X�擾����
	/// </summary>
	/// <returns>�N���X�̃|�C���^</returns>
	static ResourceManager* GetInstance();

	/// <summary>
	/// ���\�[�X�Ǘ��N���X�̃C���X�^���X�폜����
	/// </summary>
	static void DeleteInstance();

public:

	/**
	/* �摜�擾����
	* @param	file_name	�t�@�C���p�X
	* @param	all_num		�摜�̑���
	* @param	num_x		���̑���
	* @param	num_y		�c�̑���
	* @param	size_x		���̃T�C�Y(px)
	* @param	size_y		�c�̃T�C�Y(px)
	* @return	�ǂݍ��񂾉摜�n���h����std::vector�z��
	* */
	const std::vector<int>& GetImages(std::string file_name, int all_num = 1,
		int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);
	const std::vector<int>& GetImages(const char* file_name, int all_num = 1,
		int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);
	const std::vector<int>& GetImages(MaterialParam element);

	/**
	*�S�Ẳ摜���폜����
	*@param material_handle �폜�������摜�n���h����std::vector�z��
	*/
	void UnloadResourcesAll();

private:
	/**
	*�摜�n���h����ǂݍ��݃��\�[�X���쐬����
	*@param file_name �t�@�C���p�X
	*/
	void CreateImagesResource(std::string file_name);
	/**
	*�摜�n���h����ǂݍ��݃��\�[�X���쐬����
	*@param file_name �t�@�C���p�X
	*@param all_num �摜�̑���
	*@param num_x ���̑���
	*@param num_y �c�̑���
	*@param size_x ���̃T�C�Y(px)
	*@param size_y �c�̃T�C�Y(px)
	*/
	void  CreateImagesResource(std::string file_name, int all_num, int num_x, int num_y,
		int size_x, int size_y);

	/* - - - - - - - - - - - - < �����ǂݍ��݋@�\ > - - - - - - - - - - - - - - - - - - - - */

public:
	/// <summary>
	/// �����擾����
	/// </summary>
	/// <param name="�t�@�C���p�X"></param>
	/// <returns>�ǂݍ��񂾉����n���h����ԋp</returns>
	int GetSound(const std::string& file_name);

private:
	/**
	* ������ǂݍ���Ń��\�[�X�}�b�v�ɒǉ�
	*@param file_name �t�@�C���p�X
	*/
	void CreateSoundResource(std::string file_name);

public:
	//�S�Ẳ������폜���鏈��
	void UnloadSoundResouecesAll();
};
