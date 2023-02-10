#pragma once
#include "aqua.h"
#include "stage_id.h"
#include "stage_object/rock/object_rock.h"
#include "stage_object/tower/object_tower.h"
#include "stage_object/tree/object_tree.h"

class CCommonData;

class CStage : public aqua::IGameObject
{
public:
	CStage(aqua::IGameObject* parent);
	~CStage() = default;

	void Initialize() override;
	void Update() override;
	void Finalize() override;
	/*
	*  @brief  �����Ȃ����
	*
	* @param[in] stage_data �Q�Ƃ���z��̗v�f��
	* @return    �����Ȃ����
	*/
	aqua::CVector3 GetArePosition(aqua::CPoint stage_data);
	/*
	*  @brief  �I�u�W�F�N�g�̗L��
	*
	*  @param[in] position ���W
	* 
	*  @retval true    �I�u�W�F�N�g����
    *  @retval false   �I�u�W�F�N�g������
	*/
	bool CheckObject(aqua::CVector3 position);



private:

	void CreateStageObject();
	void LodaStageMap();
	void SpaceAlgorithms();
	void AutoMapCreate();

	/*
	*  @brief  �}�b�v����
	* 
	* @param[in] min_stage_size �X�e�[�W�}�b�v�̎n�_
	* @param[in] max_stage_size �X�e�[�W�}�b�v�̏I�_
	* @param[in] max_partition  ��������ő��
	*/
	void MapPartition(aqua::CPoint stage_size_first, aqua::CPoint stage_size_end,int max_partition);

private:

	static const int		  m_max_stage;           //! 
	static const int		  m_max_template_stage;	 //! 
	static const int		  m_map_object_space;	 //! 
	static const aqua::CPoint m_map_size;		     //! 
	static const std::string  m_stage_commn_name;    //! 

	std::vector<std::vector<int>> m_StageMap;        //! 
	std::vector<aqua::CPoint>     m_FirstPosition;	 //! 
	std::vector<aqua::CPoint>     m_EndPosition;	 //! 
	aqua::CPoint			      m_StageSize;		 //! 
	aqua::CModel                  m_StageModel;      //! 
	aqua::CModel*			      m_RandStage;		 //! 
	int						      m_StageObjectSize; //! 
	int						      m_StageNum;        //! 
	CCommonData*                  m_CommonData;      //! 
	STAGE_LEVER                   m_CreateStageLever;//! 
};