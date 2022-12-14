#pragma once
#include "../mathematics/mathematics.h"
#include "../graphics/surface/surface.h"
#include "../graphics/sprite/sprite.h"
namespace aqua
{
	
	class CCamera : public aqua::core::IDrawObject
	{
	public:

		aqua::CVector3 camera_position;  //! 3D��Ԃ̍��W

		aqua::CVector2 screen_position;  //! �`�悷����W

		aqua::CVector2 screen_center; //! �`�悷��f���̒��S�l�i�Q��ʂƂ��Ɏg�p�j

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