#include "draw_object_3d.h"
std::list<aqua::core::DrawObject3D*> aqua::core::DrawObject3D::m_DrawList;

void aqua::core::DrawObject3D::DrawList()
{
	for (auto& i : m_DrawList)
		i->Draw();
}

aqua::core::DrawObject3D::DrawObject3D()
{
	m_DrawList.push_back(this);
}

aqua::core::DrawObject3D::~DrawObject3D()
{
	auto find = std::find(m_DrawList.begin(), m_DrawList.end(), this);

	if (find != m_DrawList.end())
		m_DrawList.erase(find);
}

void aqua::core::DrawObject3D::Draw()
{
}
