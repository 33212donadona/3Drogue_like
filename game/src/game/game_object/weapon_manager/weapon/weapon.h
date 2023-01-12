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
	*  @brief 行列設定
	* 
	* @param[in] mm   行列
	*/
	void SetMatrix(aqua::CMatrix model_matrix);

private:

	aqua::CMatrix m_ModelMatrix;       //! 武器モデルの行列
	aqua::CModel  m_WeaponModel;       //! 武器のモデル

protected:

	aqua::CMatrix m_RotationMatrix;    //! 武器モデルの回転行列
	aqua::CMatrix m_RotationMatrix2;   //! 武器モデルの回転行列
	std::string m_WeaponFileName;      //! 武器のファイル名

};