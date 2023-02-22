#pragma once
#include "aqua.h"
class IObject :public aqua::IGameObject
{
public:
	IObject(aqua::IGameObject* parent,std::string name);
	~IObject() = default;

	virtual void Initialize(aqua::CVector3 position) {};
	virtual void Update() override;
	virtual void Finalize() override;

protected:
	aqua::CModel  m_Model;
};

