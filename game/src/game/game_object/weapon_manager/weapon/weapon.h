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

	aqua::CVector3 m_ModelPosition;   //! ���탂�f���̍��W
	aqua::CVector3 m_ModelScale;      //! ���탂�f���̊g�嗦
	aqua::CMatrix  m_ModelMatrix; //! ���탂�f���̉�]�s��

private:

	aqua::CModel m_WeaponModel;       //! ����̃��f��

protected:

	std::string m_WeaponFileName;     //! ����̃t�@�C����

};