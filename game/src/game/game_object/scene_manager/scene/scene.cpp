#include "scene.h"

IScene::IScene(aqua::IGameObject* parent, const std::string& name)
	// parent(scene_manager)
	: aqua::IGameObject(parent, name)
{
}

void IScene::Draw(void)
{
#ifdef _DEBUG
	m_Label.Draw();
#endif // _DEBUG

}
