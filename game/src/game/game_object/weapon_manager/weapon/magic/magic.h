#pragma once
#include "../weapon.h"

class CMagic : public IWeapon
{
public:
	CMagic(aqua::IGameObject* parent);
	~CMagic() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	bool CheckHit(aqua::CVector3 enemy_pos);

	void SetPosition(aqua::CVector3 position);
private:
	static const int m_effect_radius;
	static const int m_enemy_radius;
	aqua::CEffect3D m_MagicEffect;

};