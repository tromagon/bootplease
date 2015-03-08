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

    void Identity()
    {
        m_A = 1;
        m_B = 0;
        m_C = 0;
        m_D = 1;
        m_Tx = 0;
        m_Ty = 0;
    }

    void Invert()
    {
        float det = m_A * m_D - m_B * m_C;

        SetTo(
            m_D / det, -m_B / det, -m_C / det, m_A / det,
            (m_C * m_Ty - m_D * m_Tx) / det,
            (m_Tx * m_B - m_Ty * m_A) / det
            );
    }

    void SetTo(float a, float b, float c, float d, float tx, float ty)
    {
        m_A = a;
        m_B = b;
        m_C = c;
        m_D = d;
        m_Tx = tx;
        m_Ty = ty;
    }

    void Prepend(Matrix& matrix)
    {
        SetTo(
            m_A * matrix.m_A + m_C * matrix.m_B,
            m_B * matrix.m_A + m_D * matrix.m_B,
            m_A * matrix.m_C + m_C * matrix.m_D,
            m_B * matrix.m_C + m_D * matrix.m_D,
            m_Tx + m_A * matrix.m_Tx + m_C * matrix.m_Ty,
            m_Ty + m_B * matrix.m_Tx + m_D * matrix.m_Ty
            );
    }

    void Concat(Matrix& matrix)
    {
        SetTo(
            matrix.m_A * m_A + matrix.m_C * m_B,
            matrix.m_B * m_A + matrix.m_D * m_B,
            matrix.m_A * m_C + matrix.m_C * m_D,
            matrix.m_B * m_C + matrix.m_D * m_D,
            matrix.m_Tx + matrix.m_A * m_Tx + matrix.m_C * m_Ty,
            matrix.m_Ty + matrix.m_B * m_Tx + matrix.m_D * m_Ty
            );
    }

    void CopyFrom(Matrix& matrix)
    {
        m_A = matrix.m_A;
        m_B = matrix.m_B;
        m_C = matrix.m_C;
        m_D = matrix.m_D;
        m_Tx = matrix.m_Tx;
        m_Ty = matrix.m_Ty;
    }
};

#endif