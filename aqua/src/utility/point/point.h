
/*!
 *  @file       point.h
 *  @brief      点クラス
 *  @author     Kazuya Maruyama
 *  @date       2021/03/10
 *  @version    7.17
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#pragma once

/*!
 *  @brief  aqua名前空間
 */
namespace aqua
{
    /*!
     *  @class      CPoint
     *
     *  @brief      点クラス
     *
     *  @author     Kazuya Maruyama
     *
     *  @date       2021/03/10
     *
     *  @version    7.17
     */
    class CPoint
    {
    public:
        //! X成分
        int     x;
        //! Y成分
        int     y;

        /*!
         *  @brief      コンストラクタ
         */
        CPoint( void );

        /*!
         *  @brief      コンストラクタ
         *
         *  @param[in]  point    点クラス
         */
        CPoint( const CPoint& point );

        /*!
         *  @brief      コンストラクタ
         *
         *  @param[in]  x   X成分
         *  @param[in]  y   Y成分
         */
        CPoint( int x, int y );

        /*!
         *  @brief      デストラクタ
         */
        ~CPoint( void ) = default;

        /*!
         *  @brief      デバッグログに値を表示する
         */
        void    DebugLog( void );

        /*!
         *  @brief      等価演算子のオーバーロード
         *
         *  @param[in]  p   点クラス
         *
         *  @return     二つの点が等しい
         *  @retval     true    等しい
         *  @retval     false   等しくない
         */
        bool      operator==(aqua::CPoint p) { return x == p.x && y == p.y; };

        /*!
         *  @brief      不等演算子のオーバーロード
         *
         *  @param[in]  p   点クラス
         *
         *  @return     二つの点が等しくない
         *  @retval     true    等しくない
         *  @retval     false   等しい
         */
        bool      operator!=(aqua::CPoint p) { return x != p.x || y != p.y; };

        //! 要素がすべて0
        static const CPoint  ZERO;
    };
}
