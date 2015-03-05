#ifndef _MATRIXUTIL_H_
#define _MATRIXUTIL_H_

#include "Matrix.h"
#include "Vec2d.h"

class MatrixUtil
{
public:
	static void PrependMatrix(Matrix& base, Matrix& prep);
	static Vec2d& TransformCoords(Matrix& matrix, float x, float y, Vec2d& resultVec2d);
};

#endif