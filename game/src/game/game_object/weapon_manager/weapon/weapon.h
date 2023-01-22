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
	*  @param[in] mm   行列
	*/
	void SetMatrix(aqua::CMatrix model_matrix);

	/*!
	*  @brief 武器との衝突検知
	* 
	*  @param[in] first_pos   線分の初め
	*  @param[in] end_pos     線分の終わり
	* 
	*  @retval true    武器と衝突した
	*  @retval false   武器と衝突しなかった
	*/
	bool CheckHitWeapon(aqua::CVector3 first_pos, aqua::CVector3 end_pos);

private:

	aqua::CMatrix m_ModelMatrix;       //! 武器モデルの行列
	aqua::CModel  m_WeaponModel;       //! 武器のモデル

protected:

	aqua::CMatrix m_RotationMatrix;    //! 武器モデルの回転行列
	aqua::CMatrix m_RotationMatrix2;   //! 武器モデルの回転行列
	std::string m_WeaponFileName;      //! 武器のファイル名

};