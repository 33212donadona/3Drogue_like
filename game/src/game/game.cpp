
/*!
 *  @file       game.cpp
 *  @brief      �Q�[���Ǘ�
 *  @author     Kazuya Maruyama
 *  @date       2021/02/06
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "game.h"
#include "game_object/unit_manager/unit_manager.h"
#include "game_object/stage/stage.h"
#include "game_object/money_manager/money_manager.h"
#include "game_object/bag/bag.h"
#include "game_object/bag/bag_data.h"
#include "game_object/game_camera/game_camera.h"

const unsigned int CGame::m_clear_color = 0xff000000;

/*
 *  �R���X�g���N�^
 */
CGame::
CGame( aqua::IGameObject* parent )
    : aqua::IGameObject( parent, "Game" )
{
}

/*
 *  ������
 */
void
CGame::
Initialize(void)
{
    // �ŏ��ɍ��I�u�W�F�N�g�Q

    aqua::CreateGameObject<CBagData>(this);
    aqua::CreateGameObject<CMoneyManager>(this);
    aqua::CreateGameObject<CStage>(this);
    aqua::CreateGameObject<CUnitManager>(this);
    aqua::CreateGameObject<CGameCamera>(this);
    aqua::CreateGameObject<CBag>(this);

    IGameObject::Initialize();
}

/*
 *  �`��
 */
void
CGame::
Draw(void)
{
    // ��ʂ̃N���A
    aqua::Clear(m_clear_color);

    // �`�悵�����I�u�W�F�N�g�Q

    IGameObject::Draw();
}
