#pragma once
#include "../weapon.h"

class CSword : public IWeapon
{
public:
	CSword(aqua::IGameObject* parent);
	~CSword() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;

	bool CheckHit(aqua::CVector3 first_pos, aqua::CVector3 end_pos);

	void SetMatrix(aqua::CMatrix& matrix);

private:
	static const std::string m_file_pass;
	aqua::CModel m_SwordModel;
	aqua::CMatrix* m_ModelMatrix;
};