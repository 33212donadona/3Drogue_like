#pragma once
#include "aqua.h"
class IUserInterface : public aqua::IGameObject
{
public:
	
	IUserInterface(aqua::IGameObject* parent,std::string name);
	~IUserInterface() = default;

	virtual void Initialize()override ;
	virtual void Update() {} ;
	virtual void Finalize() {} ;
	virtual void Draw();
private:
	aqua::CSprite m_UserInterfaceSprite;
protected:
	std::string m_user_interface_name;
};