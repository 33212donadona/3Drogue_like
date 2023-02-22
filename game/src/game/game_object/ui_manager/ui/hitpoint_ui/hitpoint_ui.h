#pragma once
#include "../ui.h"

class CCommonData;

class CHitPointUI :public IUserInterface
{
public:

	CHitPointUI(aqua::IGameObject* parent);
	~CHitPointUI() = default;

	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Finalize()override;

private:
	int            m_HitPointPositionZero;
	int            m_HitPointMaskHandle;

	aqua::CVector2 m_MaskPosition;
	aqua::CPoint   m_MaskSize;
	aqua::CSprite  m_HitPointSprite;
	aqua::CSprite  m_HitPointFrameSprite;

	CCommonData* m_CommonData;
};