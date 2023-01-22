#pragma once
#include "aqua.h"

class IWeapon : public aqua::IGameObject
{
public:

	IWeapon(aqua::IGameObject* parent,std::string name);
	~IWeapon() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Finalize() override;

	/*!
	*  @brief �s��ݒ�
	* 
	*  @param[in] mm   �s��
	*/
	void SetMatrix(aqua::CMatrix model_matrix);

	/*!
	*  @brief ����Ƃ̏Փˌ��m
	* 
	*  @param[in] first_pos   �����̏���
	*  @param[in] end_pos     �����̏I���
	* 
	*  @retval true    ����ƏՓ˂���
	*  @retval false   ����ƏՓ˂��Ȃ�����
	*/
	bool CheckHitWeapon(aqua::CVector3 first_pos, aqua::CVector3 end_pos);

private:

	aqua::CMatrix m_ModelMatrix;       //! ���탂�f���̍s��
	aqua::CModel  m_WeaponModel;       //! ����̃��f��

protected:

	aqua::CMatrix m_RotationMatrix;    //! ���탂�f���̉�]�s��
	aqua::CMatrix m_RotationMatrix2;   //! ���탂�f���̉�]�s��
	std::string m_WeaponFileName;      //! ����̃t�@�C����

};