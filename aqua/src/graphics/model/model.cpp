#include "model.h"
#include "../../aqua.h"
// 初めに作ったファイル検索の機能を追加して！！！！！弓削に対して
void aqua::CModel::Create(const std::string& file_name, int anime_max)
{
	Delete();
	m_max_animetion = anime_max;
	m_Object3D = AQUA_NEW aqua::CObject3D[m_max_animetion];
	m_ModelHandle = AQUA_NEW int[m_max_animetion];
	m_MaxTime = AQUA_NEW float[m_max_animetion];

	if (file_name == "")return;

	for (int f_i = 0; f_i < m_max_animetion; ++f_i)
	{
		std::string name;

		name = file_name + "_" + std::to_string(f_i / 10) + std::to_string(f_i) + ".mv1";

		m_Object3D[f_i].Load(name);

		m_ModelHandle[f_i] = m_Object3D[f_i].GetResourceHandle();

		m_MaxTime[f_i] = m_Object3D[f_i].GetAnimeTotalTime(0);

		for (int i = 0; i <= MV1GetFrameNum(m_ModelHandle[f_i]); i++)
			MV1SetupCollInfo(m_ModelHandle[f_i], i, 2, 2, 2);
	}

	m_MatrixPosition.SetTranslate(position);
	m_MatrixRotation.AxisRotation(axis);
	m_MatrixScale.SetScale(scale);
	m_InitialMatrixRotation.AxisRotation(initial_axis);

	AttachAnimation(0);
}

void aqua::CModel::Delete()
{
	for (int f_i = 0; f_i < m_max_animetion; ++f_i)
		m_Object3D[f_i].Unload();
}

// ボーンのインデックス番号
int aqua::CModel::GetBoneIndex(std::string bone_name)
{
	int bone_index;

	bone_index = max(MV1SearchFrame(m_ModelHandle[0], bone_name.c_str()), 0);

	return bone_index;
}

void aqua::CModel::ChengeFrameVisible(std::string frame_name, bool visible_flag)
{
	int frame_index = GetBoneIndex(frame_name);

	MV1SetFrameVisible(m_ModelHandle[0], frame_index, visible_flag);
}

void aqua::CModel::AttachAnimation(int index)
{
	if (m_AttachIndex == index)return;
	if (m_AttachIndex >= 0)m_Object3D[m_AttachIndex].Detach(m_AttachIndex);

	//! リソースに書き込む
	m_AttachIndex = index;
	m_AttachIndex = aqua::Limit(m_AttachIndex, 0, m_max_animetion);

	m_Object3D[m_AttachIndex].ReAttach(m_AttachIndex);
	m_MaxTime[(int)m_AttachIndex] = m_Object3D[m_AttachIndex].GetAnimeTotalTime(0);
}

// アニメーションの更新
void aqua::CModel::AnimationUpdata(int index)
{
	m_Frame += 1.0f;

	if (m_Frame == 0.0f)
		AttachAnimation(index);

	if (m_Frame >= m_MaxTime[index])
		m_Frame = 0.0f;

	if (m_AttachIndex != 0)
	{
		int a = 0;
	}

	//! リソースに書き込む
	m_Object3D[m_AttachIndex].SetAnimeFrame(0, m_Frame);
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
	if (MV1GetFrameName(m_ModelHandle[m_AttachIndex], GetBoneIndex(bone_name)) == bone_name)
		index = GetBoneIndex(bone_name);
	else
		index = 0;

	coll_result_poly = MV1CollCheck_Line(m_ModelHandle[m_AttachIndex], index, start_pos, end_pos);

	info.HitFlag = coll_result_poly.HitFlag;
	info.HitPosition = coll_result_poly.HitPosition;
	info.Normal = coll_result_poly.Normal;

	return info;
}

aqua::CollisionInfo aqua::CModel::GetBoneCollision(std::string bone_name, aqua::CVector3 position, float r)
{
	CollisionInfo info;
	MV1_COLL_RESULT_POLY_DIM coll_result_poly;
	int index;
	aqua::CVector3 distance = aqua::CVector3::ZERO;

	// 計算
	if (MV1GetFrameName(m_ModelHandle[m_AttachIndex], GetBoneIndex(bone_name)) == bone_name)
		index = GetBoneIndex(bone_name);
	else
		index = 0;

	aqua::CVector3 low_position = position;
	low_position.y = 0;

	coll_result_poly = MV1CollCheck_Capsule
	(
		m_ModelHandle[m_AttachIndex],
		index,
		position,
		low_position,
		r
	);

	int num = coll_result_poly.HitNum;

	if (coll_result_poly.Dim && coll_result_poly.Dim[num].HitFlag)
		distance = position - coll_result_poly.Dim[num].HitPosition;

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
	for (int i = 0; i <= MV1GetFrameNum(m_ModelHandle[m_AttachIndex]); i++)
		MV1RefreshCollInfo(m_ModelHandle[m_AttachIndex], i);

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

	for (int f_i = 0; f_i < m_max_animetion; ++f_i)
		MV1SetMatrix(m_ModelHandle[f_i], (m_MatrixRotation * m_MatrixScale * m_MatrixPosition));

	MV1DrawModel(m_ModelHandle[m_AttachIndex]);

	DrawObject3D::Draw();
}
aqua::CVector3 aqua::CModel::GetBonePosistion(int bone_index)
{
	return MV1GetFramePosition(m_ModelHandle[m_AttachIndex], bone_index);
}
