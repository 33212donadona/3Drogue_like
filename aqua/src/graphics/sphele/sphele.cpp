#include "sphele.h"

aqua::CSphere::CSphere()
	:radius(1.0f)
{
}

void aqua::CSphere::Create(int div_num, unsigned int dif_color, unsigned int spc_color, bool fill_flag)
{
	SphereData sd;

	sd.DivNum = div_num;
	sd.DifColor = dif_color;
	sd.SpcColor = spc_color;
	sd.FillFlag = fill_flag;

	Create(sd);
}

void aqua::CSphere::Create(SphereData sphele_data)
{
	m_SpheleData = sphele_data;
}

void aqua::CSphere::Delete()
{
	
}

void aqua::CSphere::Draw()
{
	DrawSphere3D
	(
		position,
		radius,
		m_SpheleData.DivNum,
		m_SpheleData.DifColor,
		m_SpheleData.SpcColor,
		m_SpheleData.FillFlag
	);

	IDrawObject3D::Draw();
}
