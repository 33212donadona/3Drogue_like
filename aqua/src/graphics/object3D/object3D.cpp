#include "object3D.h"
#include "object3D_manager/object3D_manager.h"

aqua::CObject3D::CObject3D()
	:m_Object3DResorce(nullptr)
{
}

aqua::CObject3D::CObject3D(const CObject3D& model)
	: m_Object3DResorce(nullptr)
{
	if (m_Object3DResorce)
		m_Object3DResorce->RemoveReference();

	m_Object3DResorce = model.m_Object3DResorce;

	m_Object3DResorce->AddReference();
}

void aqua::CObject3D::Load(const std::string& file_name, int index)
{
	// �e�N�X�`�����\�[�X�ޔ�
	core::CObject3DResorce* object_3d = m_Object3DResorce;

	// �e�N�X�`���}�l�[�W������e�N�X�`���擾
	m_Object3DResorce = core::CObject3DManager::GetInstance().Load(file_name, index);

	if (object_3d)
	{
		int count = object_3d->RemoveReference();

		// �O�̃e�N�X�`���̎Q�ƃJ�E���^���Ȃ��Ȃ�������
		if (count <= 0)
			core::CObject3DManager::GetInstance().Unload(object_3d);
	}
}

void aqua::CObject3D::Unload(void)
{
	// �e�N�X�`�����
	if (m_Object3DResorce)
		core::CObject3DManager::GetInstance().Unload(m_Object3DResorce);

	m_Object3DResorce = nullptr;
}

void aqua::CObject3D::ReAttach(int a_i)
{
	if (m_Object3DResorce)
		m_Object3DResorce->ReAttach(a_i);
}

void aqua::CObject3D::Detach(int a_i)
{
	if (m_Object3DResorce)
		m_Object3DResorce->Dettach(a_i);
}

void aqua::CObject3D::SetAnimeFrame(int a_i, float time)
{
	if (m_Object3DResorce)
		m_Object3DResorce->SetAnimeFrame(a_i, time);
}

float aqua::CObject3D::GetAnimeTotalTime(int a_i)
{
	if (!m_Object3DResorce)return 0.0f;
	return m_Object3DResorce->GetAnimeTotalTime(a_i);
}

aqua::CObject3D& aqua::CObject3D::operator=(const CObject3D& texture)
{
	// �e�N�X�`���������Ă�����Q�Ƃ����Z
	if (m_Object3DResorce)
		m_Object3DResorce->RemoveReference();

	m_Object3DResorce = texture.m_Object3DResorce;

	// �Q�ƃJ�E���^���Z
	m_Object3DResorce->AddReference();

	return *this;
}

void aqua::CObject3D::Delete(void)
{
	if (m_Object3DResorce)
		core::CObject3DManager::GetInstance().Delete(m_Object3DResorce);

	m_Object3DResorce = nullptr;
}
