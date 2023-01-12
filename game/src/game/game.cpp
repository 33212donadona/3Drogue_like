
/*!
 *  @file       game.cpp
 *  @brief      ゲーム管理
 *  @author     Kazuya Maruyama
 *  @date       2021/02/06
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "game.h"
#include "game_object/unit/unit.h"
#include "game_object/enemy/enemy.h"
#include "game_object/stage/stage.h"
#include "game_object/money/money.h"
#include "game_object/bag/bag.h"
#include "game_object/bag/bag_data.h"
#include "game_object/game_camera/game_camera.h"

const unsigned int CGame::m_clear_color = 0xff000000;

/*
 *  コンストラクタ
 */
CGame::
CGame( aqua::IGameObject* parent )
    : aqua::IGameObject( parent, "Game" )
{
}

/*
 *  初期化
 */
void
CGame::
Initialize(void)
{
    // 最初に作るオブジェクト群

    aqua::CreateGameObject<CBagData>(this);
    aqua::CreateGameObject<CEnemy>(this);
    aqua::CreateGameObject<CUnit>(this);
    aqua::CreateGameObject<CStage>(this);
    aqua::CreateGameObject<CGameCamera>(this);
    aqua::CreateGameObject<CMoney>(this);
    aqua::CreateGameObject<CBag>(this);

    IGameObject::Initialize();
}

/*
 *  描画
 */
void
CGame::
Draw(void)
{
    // 画面のクリア
    aqua::Clear(m_clear_color);

    // 描画したいオブジェクト群

    IGameObject::Draw();
}
