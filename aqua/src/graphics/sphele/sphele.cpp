#include "sphele.h"

void aqua::CSphele::Create(int div_num, unsigned int dif_color, unsigned int spc_color, bool fill_flag)
{
	SpheleData sd;

	sd.DivNum = div_num;
	sd.DifColor = dif_color;
	sd.SpcColor = spc_color;
	sd.FillFlag = fill_flag;

	Create(sd);
}

void aqua::CSphele::Create(SpheleData sphele_data)
{
	m_SpheleData = sphele_data;
}

void aqua::CSphele::Delete()
{

}

void aqua::CSphele::Updata(VECTOR CenterPosition, float r)
{
	m_Position = CenterPosition;
	m_Radius = r;
}

void aqua::CSphele::Draw()
{
	DrawSphere3D
	(
		m_Position,
		m_Radius,
		m_SpheleData.DivNum,
		m_SpheleData.DifColor,
		m_SpheleData.SpcColor,
		m_SpheleData.FillFlag
	);

	DrawObject3D::Draw();
}
