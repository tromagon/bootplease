#ifndef _MATRIXUTIL_H_
#define _MATRIXUTIL_H_

#include "Matrix.h"
#include "Vec2d.h"

class MatrixUtil
{
public:
    static void PrependMatrix(Matrix& base, Matrix& prep)
    {
        base.SetTo(
            base.m_A * prep.m_A + base.m_C * prep.m_B,
            base.m_B * prep.m_A + base.m_D * prep.m_B,
            base.m_A * prep.m_C + base.m_C * prep.m_D,
            base.m_B * prep.m_C + base.m_D * prep.m_D,
            base.m_Tx + base.m_A * prep.m_Tx + base.m_C * prep.m_Ty,
            base.m_Ty + base.m_B * prep.m_Tx + base.m_D * prep.m_Ty
            );
    }

    static Vec2d& TransformCoords(Matrix& matrix, float x, float y, Vec2d& resultVec2d)
    {
        resultVec2d.x = matrix.m_A * x + matrix.m_C * y + matrix.m_Tx;
        resultVec2d.y = matrix.m_D * y + matrix.m_B * x + matrix.m_Ty;

        return resultVec2d;
}
};

#endif