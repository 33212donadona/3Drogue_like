#include "model.h"
#include "../../aqua.h"

// 弓削に対して初めに作ったファイル検索の機能を追加して！！！！！
void aqua::CModel::Create(const std::string& file_name, int anime_max, float add_frame)
{
	Delete();
	m_max_animetion = anime_max;
	m_AddFrame = add_frame;

	//if (m_max_animetion > 0)
	//	m_AnimetionObject3D = AQUA_NEW aqua::CObject3D[m_max_animetion];

	if (file_name == "")return;

	m_Object3D.Load(file_name + ".mv1");

	m_ModelHandle = m_Object3D.GetResourceHandle();

	m_MaxTime = m_Object3D.GetAnimeTotalTime(0);

	for (int i = 0; i <= MV1GetFrameNum(m_ModelHandle); i++)
		MV1SetupCollInfo(m_ModelHandle, i, 2, 2, 2);

	for (int f_i = 0; f_i < m_max_animetion; ++f_i)
	{
		std::string name;
		aqua::CObject3D model;
		name = file_name + "_" + std::to_string(f_i / 10) + std::to_string(f_i) + ".mv1";
		model.Load(name);
		m_AnimetionObject3D.push_back(model.GetResourceHandle());
	}

	m_MatrixPosition.SetTranslate(position);
	m_MatrixRotation.AxisRotation(axis);
	m_MatrixScale.SetScale(scale);
	m_InitialMatrixRotation.AxisRotation(initial_axis);

	m_Frame = 0;
}

void aqua::CModel::Delete()
{
	m_Object3D.Unload();

	if (m_max_animetion > 0)
		m_AnimetionObject3D.clear();
}

// ボーンのインデックス番号
int aqua::CModel::GetBoneIndex(std::string bone_name)
{
	int bone_index;

	bone_index = max(MV1SearchFrame(m_ModelHandle, bone_name.c_str()), 0);

	return bone_index;
}

void aqua::CModel::ChengeFrameVisible(std::string frame_name, bool visible_flag)
{
	int frame_index = GetBoneIndex(frame_name);

	MV1SetFrameVisible(m_ModelHandle, frame_index, visible_flag);
}

int aqua::CModel::GetMaxAnimationIndex()
{
	return m_max_animetion;
}

void aqua::CModel::AttachAnimation(int index)
{
	if (m_AttachIndex == index || m_max_animetion <= 0)return;
	if (m_AttachIndex >= 0)m_Object3D.Detach(0);
	if (m_AttachIndex != index)m_Frame = 0.0f;
	//! リソースに書き込む
	m_AttachIndex = index;
	m_AttachIndex = aqua::Limit(m_AttachIndex, 0, m_max_animetion - 1);

	m_Object3D.ReAttach(0, m_AnimetionObject3D[m_AttachIndex]);
	m_MaxTime = m_Object3D.GetAnimeTotalTime(0);
}

// アニメーションの更新
void aqua::CModel::AnimationUpdata()
{
	m_Frame += m_AddFrame;

	if (m_Frame >= m_MaxTime)
		m_Frame = 0.0f;

	//! リソースに書き込む
	m_Object3D.SetAnimeFrame(0, m_Frame);
}

bool aqua::CModel::AnimetionFinished()
{
	return m_Frame >= m_MaxTime;
}

bool aqua::CModel::AnimetionFinished(float m_time)
{
	return m_Frame >= m_time;
}

aqua::CollisionInfo aqua::CModel::GetBoneCollision(
	std::string bone_name,
	float r,
	aqua::CVector3 start_pos,
	aqua::CVector3 end_pos
)
{
	// 戻り値の変数
	aqua::CollisionInfo info;
	// 球の中心点
	aqua::CVector3 sphele = GetBonePosistion(GetBoneIndex(bone_name));
	// 球と線分の距離
	float distance;
	float end_distance;
	float center_distance;

	aqua::CVector3 end_sphele = sphele;
	end_sphele.y = 0;

	// 計算
	distance = Segment_Point_MinLength(start_pos, end_pos, sphele);
	end_distance = Segment_Point_MinLength(start_pos, end_pos, end_sphele);
	center_distance = Segment_Segment_MinLength(start_pos, end_pos, sphele, end_sphele);

	info.HitFlag = distance <= r || end_distance <= r || center_distance <= r;
	return info;
}

aqua::CollisionInfo aqua::CModel::GetBoneCollision
(
	std::string bone_name,
	aqua::CVector3 start_pos,
	aqua::CVector3 end_pos
)
{
	CollisionInfo info;
	MV1_COLL_RESULT_POLY coll_result_poly;
	aqua::CVector3 sphele;

	sphele = GetBonePosistion(GetBoneIndex(bone_name));

	int index;
	if (MV1GetFrameName(m_ModelHandle, GetBoneIndex(bone_name)) == bone_name)
		index = GetBoneIndex(bone_name);
	else
		index = 0;

	coll_result_poly = MV1CollCheck_Line(m_ModelHandle, index, start_pos, end_pos);

	info.HitFlag = coll_result_poly.HitFlag;
	info.HitPosition = coll_result_poly.HitPosition;
	info.Normal = coll_result_poly.Normal;

	return info;
}

aqua::CollisionInfo aqua::CModel::GetBoneCollision(
	std::string bone_name, 
	aqua::CVector3 m_position, 
	float r
)
{
	CollisionInfo info;
	MV1_COLL_RESULT_POLY_DIM coll_result_poly;
	int index;
	aqua::CVector3 distance = aqua::CVector3::ZERO;

	// 計算
	if (MV1GetFrameName(m_ModelHandle, GetBoneIndex(bone_name)) == bone_name)
		index = GetBoneIndex(bone_name);
	else
		index = 0;

	aqua::CVector3 low_position = m_position;
	low_position.y = 0;

	coll_result_poly = MV1CollCheck_Capsule
	(
		m_ModelHandle,
		index,
		m_position,
		low_position,
		r
	);

	int num = coll_result_poly.HitNum;

	if (coll_result_poly.Dim && coll_result_poly.Dim[num].HitFlag)
		distance = m_position - coll_result_poly.Dim[num].HitPosition;

	distance.x = abs(distance.x);
	distance.y = abs(distance.y);
	distance.z = abs(distance.z);

	// 処理
	if (coll_result_poly.Dim)
	{
		info.HitFlag = coll_result_poly.HitNum >= TRUE;
		info.HitPosition = coll_result_poly.Dim[num].HitPosition;
		info.Normal = coll_result_poly.Dim[0].Normal;
		info.distance = distance;
	}
	else
	{
		info.HitFlag = false;
		info.Normal = aqua::CVector3::ZERO;
	}
	return info;
}

void aqua::CModel::Draw()
{
	for (int i = 0; i <= MV1GetFrameNum(m_ModelHandle); i++)
		MV1RefreshCollInfo(m_ModelHandle, i);

	if (position != m_PrevPosition)
	{
		m_MatrixPosition.SetTranslate(position);
		m_PrevPosition = position;
	}

	if (angles != m_PrevAngles)
	{
		m_MatrixRotation.AxisRotation(axis, angles.x);

		if (initial_angles != m_PrevInitialAngles)
		{
			m_InitialMatrixRotation.AxisRotation(initial_axis, initial_angles.x);
			m_PrevInitialAngles = initial_angles;
		}

		m_PrevAngles = angles;

		m_MatrixRotation *= m_InitialMatrixRotation;
	}

	if (scale != m_PrevScale)
	{
		m_MatrixScale.SetScale(scale);
		m_PrevScale = scale;
	}

	if (axis != aqua::CVector3::ZERO)
		MV1SetMatrix(m_ModelHandle, (m_MatrixRotation * m_MatrixScale * m_MatrixPosition));

	MV1DrawModel(m_ModelHandle);

	IDrawObject3D::Draw();
}

aqua::CVector3 aqua::CModel::GetBonePosistion(int bone_index)
{
	return MV1GetFramePosition(m_ModelHandle, bone_index);
}

aqua::CMatrix aqua::CModel::GetBoneMatrix(int bone_index)
{
	return MV1GetFrameLocalWorldMatrix(m_ModelHandle, bone_index);
}

void aqua::CModel::SetMatrix(aqua::CMatrix m)
{
	MV1SetMatrix(m_ModelHandle, m);
}