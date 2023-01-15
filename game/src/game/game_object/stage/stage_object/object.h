#pragma once
#include "aqua.h"
class IObject :public aqua::IGameObject
{
public:
	IObject(aqua::IGameObject* parent);
	~IObject() = default;

	void Initialize(aqua::CVector3 position);
	void Update() override;
	void Finalize() override;

private:
	aqua::CSphere m_Object;
	aqua::CModel  m_Model;
};

