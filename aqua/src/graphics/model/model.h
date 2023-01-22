#pragma once
#include <string>
#include <vector>
#include "..\graphic_filter\graphic_filter.h"
#include "../draw_object_3d/draw_object_3d.h"
#include "..\..\mathematics\mathematics.h"
#include "..\object3D/object3D.h"

/*!
 *  @file       model.h
 *  @brief      3Dモデルクラス
 *  @author     Ryuiti Yugue
 *  @date       2022/03/10
 *  @version    7.17
 *
 */
namespace aqua
{
	/*!
	*  @param[in]   HitFlag      衝突判定
	*  @param[in]   HitPosition  衝突座標
	*  @param[in]   Normal       法線
	*/
	struct CollisionInfo
	{

		// 衝突判定
		bool HitFlag;
		// 衝突座標
		CVector3 HitPosition;
		// 法線
		CVector3 Normal;
		// モデルと対象の距離
		CVector3 distance;
	};

	class CModel : public aqua::core::IDrawObject3D
	{
	public:

		/*!
		*  @brief      コンストラクタ
		*/
		CModel();

		/*!
		*  @brief       モデルを生成
		*
		*  @param[in]   file_name 読み込むファイル
		*/
		void      Create(const std::string& file_name,int anime_max = 1,float add_frame = 1.0f);

		//  モデルを解放
		void      Delete();

		//! ボーンの数取得
		int       GetBone()const { return MV1GetFrameNum(m_ModelHandle); }

		/*!
		*  @brief     モデルから特定のボーン座標を取得
		* 
		* @param[in]  bone_index   ボーン番号
		*/
		aqua::CVector3 GetBonePosistion(int bone_index);

		/*!
		*  @brief     モデルから特定のボーン回転行列を取得
		*
		* @param[in]  bone_index   ボーン番号
		*/
		aqua::CMatrix GetBoneMatrix(int bone_index);

		/*!
		*  @brief     モデルから特定のボーン回転行列を取得
		*
		* @param[in]  bone_index   ボーン番号
		*/
		void  SetMatrix(aqua::CMatrix m);

		//! モデルのハンドル取得
		int       GetHandle()const { return m_ModelHandle; };
		//! モデルのボーン取得
		int       GetBoneIndex(std::string bone_name);
		//! モデルのボーンの表示設定
		void      ChengeFrameVisible(std::string frame_name, bool visible_flag);

		//! アニメーション最大数の取得
		int       GetMaxAnimationIndex();

		void      AttachAnimation(int index = 0);
		//! アニメーションを再生
		void      AnimationUpdata();
		
		//! アニメーションの終了
		bool      AnimetionFinished();

		//! アニメーションの終了
		bool      AnimetionFinished(float m_time);

		/*!
		*  @brief       球と線分の衝突情報
		*
		*  @param[in]   bone_name    ボーン名
		*  @param[in]   r            半径
		*  @param[in]   start_pos    始点
		*  @param[in]   end_pos      終点
		*/
		CollisionInfo GetBoneCollision
		(	std::string bone_name,
			float r,
			aqua::CVector3 start_pos,
			aqua::CVector3 end_pos
		);


		/*!
		*  @brief       線分とモデルの衝突情報
		*
		*  @param[in]   BoneName     ボーン名
		*  @param[in]   start_pos 　 始点
		*  @param[in]   end_pos　　  終点
		*/
		CollisionInfo    GetBoneCollision
		(
			std::string bone_name,
			aqua::CVector3 start_pos,
			aqua::CVector3 end_pos
		);
		/*!
		*  @brief       球とモデルの衝突情報
		*
		*  @param[in]   bone_name    ボーン名
		*  @param[in]   position 　  座標
		*  @param[in]   r            半径
		*/
		CollisionInfo    GetBoneCapsuleCollision
		(
			std::string bone_name,
			aqua::CVector3 top_position,
			aqua::CVector3 bottom_position,
			float r
		);

		float          initial_angles;//! 初期回転値
		aqua::CVector3 initial_axis;  //! 初期回転軸

		float          angles;        //! 回転値
		aqua::CVector3 axis;          //! 1つ目の回転軸


		aqua::CVector3 position;      //! 座標
		aqua::CVector3 scale;         //! 拡大率

	private:

		void      Draw()override;

		static const aqua::CMatrix m_Indent;               //! マトリクスの初期化

		aqua::CObject3D  m_Object3D;                       //! モデル
		std::vector<int> m_AnimetionObject3D;              //! アニメーションモデル
		float          m_PrevAngles;                       //! 回転値
		float          m_PrevInitialAngles;                //! 回転値
		aqua::CVector3 m_PrevPosition;
		aqua::CVector3 m_PrevScale;

		aqua::CMatrix m_MatrixRotation;                    //! 回転行列
		aqua::CMatrix m_InitialMatrixRotation;             //! 回転行列
		aqua::CMatrix m_MatrixPosition;                    //! 座標行列
		aqua::CMatrix m_MatrixScale;                       //! 拡大行列

		int m_ModelHandle;

		int m_max_animetion;

		int m_AttachIndex;

		int m_AttachHandle;

		float m_Frame;
		float m_AddFrame;

		float m_MaxTime;
		float m_NowTime;
	};

}