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
	* @param[in] mm   �s��
	*/
	void SetMatrix(aqua::CMatrix model_matrix);

private:

	aqua::CMatrix m_ModelMatrix;       //! ���탂�f���̍s��
	aqua::CModel  m_WeaponModel;       //! ����̃��f��

protected:

	aqua::CMatrix m_RotationMatrix;    //! ���탂�f���̉�]�s��
	aqua::CMatrix m_RotationMatrix2;   //! ���탂�f���̉�]�s��
	std::string m_WeaponFileName;      //! ����̃t�@�C����

};