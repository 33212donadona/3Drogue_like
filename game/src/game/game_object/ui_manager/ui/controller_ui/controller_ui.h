#pragma once
#include "../ui.h"

class CCommonData;

class CControllerUI :public IUserInterface
{
public:

	CControllerUI(aqua::IGameObject* parent);
	~CControllerUI() = default;

	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Finalize()override;

private:
	aqua::CSprite  m_ControllerSprite;
};