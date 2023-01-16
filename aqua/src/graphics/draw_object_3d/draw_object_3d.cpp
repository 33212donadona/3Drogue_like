#include "draw_object_3d.h"
std::list<aqua::core::IDrawObject3D*> aqua::core::IDrawObject3D::m_DrawList;

void aqua::core::IDrawObject3D::DrawList()
{
	for (auto& i : m_DrawList)
		i->Draw();
}

aqua::core::IDrawObject3D::IDrawObject3D()
{
	m_DrawList.push_back(this);
}

aqua::core::IDrawObject3D::~IDrawObject3D()
{
	auto find = std::find(m_DrawList.begin(), m_DrawList.end(), this);

	if (find != m_DrawList.end())
		m_DrawList.erase(find);
}