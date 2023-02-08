#pragma once
#include "aqua.h"

class CUIManager : public aqua::IGameObject
{
public:

	CUIManager(aqua::IGameObject* parent);
	~CUIManager() = default;

	void Initialize() override;
	void Update() override;
	void Draw()override;
	void Finalize() override;

private:


};