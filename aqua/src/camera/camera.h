#pragma once
#include "../mathematics/mathematics.h"
#include "../graphics/surface/surface.h"
#include "../graphics/sprite/sprite.h"
namespace aqua
{
	
	class CCamera : public aqua::core::IDrawObject
	{
	public:

		aqua::CVector3 camera_position;  //! 3D空間の座標

		aqua::CVector2 screen_position;  //! 描画する座標

		aqua::CVector2 screen_center; //! 描画する映像の中心値（２画面とかに使用）

		float angle_x;

		float angle_y;

	public:

		void        Create(int width,int height);

		void        Draw();

		CCamera();
		~CCamera() = default;

	private:
		aqua::CSurface m_Surface;
		aqua::CRect    m_Rect;
	};
}