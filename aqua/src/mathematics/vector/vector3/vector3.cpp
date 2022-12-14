#include "vector3.h"

const aqua::CVector3 aqua::CVector3::ZERO = aqua::CVector3(0.0f, 0.0f,0.0f);
const aqua::CVector3 aqua::CVector3::ONE  = aqua::CVector3(1.0f, 1.0f,1.0f);

/*
*   コンストラクタ
*/
aqua::CVector3::CVector3(void)
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}
/*
*   コンストラクタ
*/
aqua::CVector3::CVector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
aqua::CVector3::CVector3(int x, int y, int z)
{
	this->x = (float)x;
	this->y = (float)y;
	this->z = (float)z;
}
/*
*   コンストラクタ
*/
aqua::CVector3::CVector3(const VECTOR& v)
	: CVector3(v.x, v.y, v.z)
{
}
/*
*  　正規化
*/
aqua::CVector3 aqua::CVector3::Normalize(void)const
{
	return Normalize (*this);
}
/*
*  　正規化
*/
aqua::CVector3 aqua::CVector3::Normalize(const VECTOR& v)
{
	return VNorm(v);
}
/*
 *   ベクトルの大きさ取得
 */
float aqua::CVector3::Length(void)const
{
	return Length(*this);
}
/*
 *   ベクトルの大きさ取得
 */
float aqua::CVector3::Length(const VECTOR& v)
{
	return VSize(v);
}
/*
*   内積
*/
float aqua::CVector3::Dot(const VECTOR& vA, const VECTOR& vB)
{
	return VDot(vA, vB);
}
/*
*   外積
*/
aqua::CVector3 aqua::CVector3::Cross(const VECTOR& vA, const VECTOR& vB)
{
#if 0
	return CVector3
		(
			vA.y * vB.z - vA.z * vB.y,
			vA.z * vB.x - vA.x * vB.z,
			vA.x * vB.y - vA.y * vB.x
		);
#endif
	return VCross(vA, vB);

}
/*
*   行列をベクトル変換
*/
void aqua::CVector3::Transform(MATRIX in_Matrix)
{

	//this->x = VTransform(aqua::CVector3::ONE, in_Matrix).x;
	//this->y = VTransform(aqua::CVector3::ONE, in_Matrix).y;
	//this->z = VTransform(aqua::CVector3::ONE, in_Matrix).z;

	*this = CVector3(VTransform(aqua::CVector3::ONE, in_Matrix));

}
