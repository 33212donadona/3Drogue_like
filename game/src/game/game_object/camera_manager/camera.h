#pragma once
#include "aqua.h"
class ICamera : public aqua::IGameObject
{
public:

	ICamera(aqua::IGameObject* parent, std::string name);
	~ICamera() = default;

	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Draw()override;
	virtual void Finalize()override;

protected:
	aqua::CCamera m_Camera;

};