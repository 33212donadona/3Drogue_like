#include "aqua.h"

class CWeaponManager : public aqua::IGameObject
{
public:

	CWeaponManager(aqua::IGameObject* parent);
	~CWeaponManager() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	void SetWeapon();

};