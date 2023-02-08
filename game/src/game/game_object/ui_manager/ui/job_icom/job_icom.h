#pragma once
#include "../ui.h"
#include "../../../common_data/common_data_info.h"

class CCommonData;

class CJobIcon : public IUserInterface
{
public:

	CJobIcon(aqua::IGameObject* parent);
	~CJobIcon() = default;

	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Finalize()override;

private:
	static const std::string m_icon_file_pass[(int)JOB_ID::MAX];

	aqua::CSprite m_JobIconSprite[(int)JOB_ID::MAX];

	CCommonData* m_CommonData;
};