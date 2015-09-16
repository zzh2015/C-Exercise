#ifndef Complex_h
#define Complex_h

#include <math.h>
class Complex
{
public:
    Complex(float real = 0.0f, float imag = 0.0f)
    {
        m_real = real;
        m_imag = imag;
    }
    Complex(const Complex &source)
    {
        m_real = source.m_real;
        m_imag = source.m_imag;
    }
    Complex& operator=(const Complex &source)
    {
        m_real = source.m_real;
        m_imag = source.m_imag;
        return *this;
    }
    ~Complex()
    {
    }
    void Set(float real, float imag = 0.0f)
    {
        m_real = real;
        m_imag = imag;
    }
    float MagSqr() const
    {
        return m_real * m_real + m_imag * m_imag;
    }
    void ConjBy(const Complex &source)
    {
        m_real = source.m_real;
        m_imag = -source.m_imag;
    }
    Complex &operator+=(const Complex &source)
    {
        m_real += source.m_real;
        m_imag += source.m_imag;
        return *this;
    }
    Complex operator*(const Complex &source)
    {
        return Complex(m_real * source.m_real - m_imag * source.m_imag,
                       m_real * source.m_imag + m_imag * source.m_real);
    }
    void DivLength1By(Complex &A, Complex &B)
    {
        m_real = A.m_real * B.m_real + A.m_imag * B.m_imag;
        m_imag = A.m_imag * B.m_real - A.m_real * B.m_imag;
    }
    void AddBy(Complex &A, Complex &B)
    {
        m_real = A.m_real + B.m_real;
        m_imag = A.m_imag + B.m_imag;
    }
    void AddBy(Complex &A)
    {
        m_real += A.m_real;
        m_imag += A.m_imag;
    }
    void AddBy(float real)
    {
        m_real += real;
    }
    void AddEqualMulBy(Complex &A, Complex &B)
    {
        m_real += A.m_real * B.m_real - A.m_imag * B.m_imag;
        m_imag += A.m_real * B.m_imag + A.m_imag * B.m_real;
    }
    void AddEqualMulBy(Complex &source, float &k)
    {
        m_real += source.m_real * k;
        m_imag += source.m_imag * k;
    }
    void SubBy(Complex &A, Complex &B)
    {
        m_real = A.m_real - B.m_real;
        m_imag = A.m_imag - B.m_imag;
    }
    void MulBy(Complex &A, Complex &B)
    {
        m_real = A.m_real * B.m_real - A.m_imag * B.m_imag;
        m_imag = A.m_real * B.m_imag + A.m_imag * B.m_real;
    }
    void MulBy(Complex &source, float &k)
    {
        m_real = source.m_real * k;
        m_imag = source.m_imag * k;
    }
    void MulBy(float &k)
    {
        m_real *= k;
        m_imag *= k;
    }
    void DivBy(float k)
    {
        m_real /= k;
        m_imag /= k;
    }
    void DivBy(Complex &A, Complex &B)
    {
        float mag = B.MagSqr();
        if(mag > 0.0f)
        {
            m_real = (A.m_real * B.m_real + A.m_imag * B.m_imag) / mag;
            m_imag = (A.m_imag * B.m_real - A.m_real * B.m_imag) / mag;
        }
        else
        {
            m_real = 0;
            m_imag = 0;
        }
    }

    float m_real;
    float m_imag;
};
#endif
