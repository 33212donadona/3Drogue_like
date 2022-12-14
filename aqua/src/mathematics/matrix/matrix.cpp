#include "matrix.h"
#include "../vector/vector3/vector3.h"
#include <cmath>
/*
*   コンストラクタ
*/
aqua::CMatrix::CMatrix()
{
	*this = MGetIdent();
}
/*
*   コンストラクタ
*/
aqua::CMatrix::CMatrix(const float in_Float[4][4])
{
	const int index = 4;
	const int matrix = index * index;

	for (unsigned short i = 0; i < matrix; i++)
		this->m[i / index][i % index] = in_Float[i / index][i % index];

}
/*
*   コンストラクタ
*/
aqua::CMatrix::CMatrix(const MATRIX& in_Matrix)
	:CMatrix(in_Matrix.m)
{

}
/*
*   X軸回転
*/
aqua::CMatrix aqua::CMatrix::XRotation(const float Axis)
{
	return MGetRotX(Axis);
}
/*
*   Y軸回転
*/
aqua::CMatrix aqua::CMatrix::YRotation(const float Axis)
{
	return MGetRotY(Axis);
}
/*
*   Z軸回転
*/
aqua::CMatrix aqua::CMatrix::ZRotation(const float Axis)
{
	return MGetRotZ(Axis);
}
/*
*   指定軸固定の回転
*/
void aqua::CMatrix::AxisRotation(VECTOR in_Vector, const float Axis)
{
	if (abs(in_Vector.x) > 1.0f)
		in_Vector.x = abs(in_Vector.x) / in_Vector.x;
	
	if (abs(in_Vector.y) > 1.0f)
		in_Vector.y = abs(in_Vector.y) / in_Vector.y;
	
	if (abs(in_Vector.z) > 1.0f)
		in_Vector.z = abs(in_Vector.z) / in_Vector.z;

	if (aqua::CVector3::ZERO == in_Vector)
		in_Vector = aqua::CVector3::ONE;

	*this = MGetRotAxis(in_Vector, Axis);
}

void aqua::CMatrix::SetTranslate(VECTOR in_Vector)
{
	*this = MGetTranslate(in_Vector);
}

void aqua::CMatrix::SetScale(VECTOR in_Scale)
{
	if (aqua::CVector3::ZERO == in_Scale)
		in_Scale = aqua::CVector3::ONE;

	*this = MGetScale(in_Scale);
}
