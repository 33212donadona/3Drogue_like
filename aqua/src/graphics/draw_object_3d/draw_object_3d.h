#pragma once

#include <list>
namespace aqua
{
	namespace core
	{
		class IDrawObject3D
		{
		public:
			bool visible;

			static void DrawList();

		protected:
			IDrawObject3D();

			virtual ~IDrawObject3D();
			virtual void Draw() {}

		private:

			static std::list<IDrawObject3D*> m_DrawList;
		};
	}
}