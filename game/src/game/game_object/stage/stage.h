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
	*  @brief  何もない空間
	*
	* @param[in] stage_data 参照する配列の要素数
	* @return    何もない空間
	*/
	aqua::CVector3 GetArePosition(aqua::CPoint stage_data);
	/*
	*  @brief  オブジェクトの有無
	*
	*  @param[in] position 座標
	* 
	*  @retval true    オブジェクト発見
    *  @retval false   オブジェクト未発見
	*/
	bool CheckObject(aqua::CVector3 position);



private:

	void CreateStageObject();
	void LodaStageMap();
	void SpaceAlgorithms();
	void AutoMapCreate();

	/*
	*  @brief  マップ分割
	* 
	* @param[in] min_stage_size ステージマップの始点
	* @param[in] max_stage_size ステージマップの終点
	* @param[in] max_partition  分割する最大回数
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