#pragma once
// —æ‰¹‚Ì”­‘z
#include <list>
namespace aqua
{
	namespace core
	{
		class DrawObject3D
		{
		public:

			static void DrawList();

		protected:
			DrawObject3D();

			virtual ~DrawObject3D();
			virtual void Draw();

		private:

			static std::list<DrawObject3D*> m_DrawList;
		};
	}
}