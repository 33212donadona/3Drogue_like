#pragma once
#include "aqua.h"

class IMagic : public aqua::IGameObject
{
public:

	IMagic(aqua::IGameObject* parent, std::string name);
	~IMagic() = default;

	virtual void Initialize() override;
	virtual void Update() override;
	void Draw()override;
	virtual void Finalize() override;

	void SetPosition(aqua::CVector3 position);

private:

	aqua::CEffect3D m_MagicEffect;    //魔法のエフェクト
	aqua::CSphere   m_MagicSphele;    //魔法の球体
	aqua::CVector3  m_Position;       //魔法の座標
	aqua::CVector3  m_PrevPosition;   //魔法の前座標
	int             m_MagicRotationi; //魔法の回転

protected:

	std::string m_MagicEffectName;    //魔法エフェクトの名前

};