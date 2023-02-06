#pragma once
#include "aqua.h"

class CBagData;
struct WEAPON_STATE;

class CBag : public aqua::IGameObject
{
public:

	CBag(aqua::IGameObject* parent);
	~CBag() = default;

	void Initialize() override;
	void Update() override;
	void Draw()override;
	void Finalize() override;

private:
	/*!
	*  @brief      �A�C�e���I��
	*/
	void SelectInventory();
	/*!
	*  @brief      �I�����Ă���g�ԍ�
	*/
	void SelectNumber();
	/*!
	*  @brief      �A�C�e���I��
	*/
	void ScaleInventoryScale(int bag_num);

private:
	static const int         m_max_item;
	static const int         m_flash_speed;
	static const int         m_back_ground_alpha;
	static const float       m_scale_time;
	static const float       m_scale_bag_sprite;
	static const float       m_bag_sprite_space;
	static const std::string m_file_name[3];

	aqua::CSprite* m_BagSprite;                            //! �o�b�N�̒�
	std::vector<std::vector<aqua::CSprite>> m_ItemSprite;  //! �A�C�e���̉摜
	aqua::CBoxPrimitive m_BackGraund;                      //! �w�i
	aqua::CBoxPrimitive m_SelectBox;                       //! �_��
	aqua::CVector2  m_BagSpriteSize;                       //! �C���x���g���̑傫��
	aqua::CTimer    m_EsingTime;                           //! �g�厞��
	CBagData*       m_BagData;
	WEAPON_STATE*   m_ItemData;

	int m_BagCapacity;
	int m_SelectTime;
	int m_SelectNumber;
	float m_EsingScale;
	bool  m_KeybordFlag;
};