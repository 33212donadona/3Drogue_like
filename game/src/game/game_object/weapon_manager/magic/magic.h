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

	aqua::CEffect3D m_MagicEffect;    //���@�̃G�t�F�N�g
	aqua::CSphere   m_MagicSphele;    //���@�̋���
	aqua::CVector3  m_Position;       //���@�̍��W
	aqua::CVector3  m_PrevPosition;   //���@�̑O���W
	int             m_MagicRotationi; //���@�̉�]

protected:

	std::string m_MagicEffectName;    //���@�G�t�F�N�g�̖��O

};