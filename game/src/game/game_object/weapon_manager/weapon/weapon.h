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

	aqua::CVector3 m_ModelPosition;   //! 武器モデルの座標
	aqua::CVector3 m_ModelScale;      //! 武器モデルの拡大率
	aqua::CMatrix  m_ModelMatrix; //! 武器モデルの回転行列

private:

	aqua::CModel m_WeaponModel;       //! 武器のモデル

protected:

	std::string m_WeaponFileName;     //! 武器のファイル名

};