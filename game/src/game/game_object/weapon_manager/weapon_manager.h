#include "aqua.h"

enum class WEAPON_ID;
class IWeapon;

class CWeaponManager : public aqua::IGameObject
{
public:

	CWeaponManager(aqua::IGameObject* parent);
	~CWeaponManager() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	void SetWeapon(WEAPON_ID weapon_id);
	bool CheckHit(aqua::CVector3 first_pos, aqua::CVector3 end_pos);
	void SetHandMatrix(aqua::CModel& model,const std::string hand_name);

private:
	IWeapon* m_Weapon;
	WEAPON_ID m_NowWeapon;
};