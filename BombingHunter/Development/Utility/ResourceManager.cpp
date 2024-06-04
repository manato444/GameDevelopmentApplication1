#include "ResourceManager.h"
#include"DxLib.h"

//�ÓI�����o�ϐ���`
ResourceManager* ResourceManager::instance = instance = nullptr;//�N���X�̃C���X�^���X�̃|�C���^

/// <summary>
/// ���\�[�X�Ǘ��N���X�̃C���X�^���X�擾
/// </summary>
/// <returns>�N���X�̃|�C���^</returns>
ResourceManager* ResourceManager::GetInstance()
{
	//�C���X�^���X��������΁A��������
	if (instance == nullptr)
	{
		instance = new ResourceManager();
	}
	//�������g�̃|�C���^��ԋp
	return instance;
}

/// <summary>
/// ���\�[�X�Ǘ��N���X�̃C���X�^���X�폜����
/// </summary>
void ResourceManager::DeleteInstance()
{
	//�C���X�^���X�����݂��Ă���΁A�폜����
	if (instance != nullptr)
	{
		instance->UnloadResourcesAll();	//�S�Ẳ摜���폜
		instance->UnloadSoundResouecesAll(); //�S�Ẳ������폜
		delete instance;
		instance = nullptr;
	}
}

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
const std::vector<int>& ResourceManager::GetImages(std::string file_name,
	int all_num, int num_x, int num_y, int size_x, int size_y)
{
	//�R���e�i���ɉ摜��������΁A�摜��ǂݍ���
	if (image_container.count(file_name) == NULL)
	{
		//�G���[�`�F�b�N
		if (all_num == 1)
		{
			CreateImagesResource(file_name);
		}
		else
		{
			CreateImagesResource(file_name, all_num, num_x, num_y, size_x, size_y);
		}
	}
	//�R���e�i���̉摜�f�[�^��ԋp
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
	*�S�Ẳ摜���폜���郁�\�b�h
	*@param material_handle �폜�������摜�n���h����std::vector�z��
*/
void ResourceManager::UnloadResourcesAll()
{
	//�R���e�i���ɉ摜��������΁A�������I������
	if (image_container.size() == NULL)
	{
		return;
	}

	//�S�Ẳ摜���폜
	for (std::pair<std::string, std::vector<int>> value : image_container)
	{
		//�ǂݍ��񂾉摜�̉��
		DeleteSharingGraph(value.second[0]);
		//���I�z��̉��
		value.second.clear();
	}

	//�R���e�i�̉��
	image_container.clear();
}

/**
* �摜�n���h����ǂݍ��݃��\�[�X���쐬����
* @param file_name �t�@�C���p�X
*/
void ResourceManager::CreateImagesResource(std::string file_name)
{
	//�w�肳�ꂽ�t�@�C����ǂݍ���
	int handle = LoadGraph(file_name.c_str());

	//�G���[�`�F�b�N
	if (handle == -1)
	{
		throw(file_name + "������܂���\n");
	}

	//�R���e�i���ɓǂݍ��񂾉摜��ǉ�����
	image_container[file_name].push_back(handle);
}

/*
	*�摜�n���h����ǂݍ��݃��\�[�X���쐬����
	*@param file_name �t�@�C���p�X
	*@param all_num �摜�̑���
	*@param num_x ���̑���
	*@param num_y �c�̑���
	*@param size_x ���̃T�C�Y(px)
	*@param size_y �c�̃T�C�Y(px)
*/
void ResourceManager::CreateImagesResource(std::string file_name, int all_num,
	int num_x, int num_y, int size_x, int size_y)
{
	//�w�肳�ꂽ�t�@�C����ǂݍ���
	int* handle = new int[all_num];
	int err = LoadDivGraph(file_name.c_str(), all_num, num_x, num_y, size_x, size_y,
		handle);

	//�G���[�`�F�b�N
	if (err == -1)
	{
		throw(file_name + "������܂���\n");
	}

	//�R���e�i�ɓǂݍ��񂾉摜��ǉ�����
	for (int i = 0; i < all_num; i++)
	{
		image_container[file_name].push_back(handle[i]);
	}

	//���I�������̉��
	delete[] handle;
}


/* - - - - - - - - - - - - < �����ǂݍ��݋@�\ > - - - - - - - - - - - - - - - - - - - - */


/// <summary>
///	�����擾����
/// </summary>
/// <param name="�t�@�C���p�X"></param>
/// <returns>�ǂݍ��񂾉����n���h��</returns>
int ResourceManager::GetSound(const std::string& file_name)
{
	//�R���e�i���ɉ�����������΁A�摜��ǂݍ���
	if (sound_container.count(file_name) == NULL)
	{
		CreateSoundResource(file_name);
	}

	//�R���e�i���̉����f�[�^��ԋp
	return sound_container[file_name];
}

/*
	*�����n���h����ǂݍ��݃��\�[�X���쐬����
	*@param file_name �t�@�C���p�X
*/
void ResourceManager::CreateSoundResource(std::string file_name)
{
	//�w�肳�ꂽ�t�@�C����ǂݍ���
	int handle_s = LoadSoundMem(file_name.c_str());

	//�G���[�`�F�b�N
	if (handle_s == -1)
	{
		throw(file_name + "������܂���\n");
	}

	//�R���e�i���ɓǂݍ��񂾉�����ǉ�����
	sound_container[file_name] = handle_s;
}

/*
	*�S�Ẳ������폜���郁�\�b�h
*/
void ResourceManager::UnloadSoundResouecesAll()
{
	//�R���e�i���ɉ�����������΁A�������I������
	if (sound_container.size() == NULL)
	{
		return;
	}

	//�S�Ẳ������폜
	for (std::pair<std::string, int> s_value : sound_container)
	{
		//�ǂݍ��񂾉����̉��
		DeleteSoundMem(s_value.second);
	}

	//�R���e�i�̉��
	sound_container.clear();
}
