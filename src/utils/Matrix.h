#ifndef _MATRIX_H_
#define _MATRIX_H_

class Matrix
{
public:
	float m_A;
	float m_B;
	float m_C;
	float m_D;
	float m_Tx;
	float m_Ty;

public:
	explicit Matrix(float a = 1, float b = 0, float c = 0, float d = 1, float tx = 0, float ty = 0) 
		: m_A(a), m_B(b), m_C(c), m_D(d), m_Tx(tx), m_Ty(ty) {}

	void	Identity();
	void	Invert();
	void	SetTo(float a = 1, float b = 0, float c = 0, float d = 1, float tx = 0, float ty = 0);
	void	Prepend(Matrix& matrix);
	void	Concat(Matrix& matrix);
	void	CopyFrom(Matrix& matrix);

};

#endif