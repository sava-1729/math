#include "math.h"
#include <vector>

using namespace std;

template <class CoeffType>
class Polynomial
{
    vector<CoeffType> _coefficients;

    public:
    int degree;

    Polynomial(CoeffType *coefficients_, int length_)
    {
        degree = length_ - 1;
        _coefficients.clear();
        for(int i = 0; i < length_; i++)
        {
            _coefficients.push_back(coefficients_[i]);
        }
    }

    template <class type>
    type operator()(type x)
    {
        type result = 0;
        for(int i = 0; i <= degree; i++)
        {
            type monomial = _coefficients[i];
            for(int j = 1; j <= i; j++)
            {
                monomial = monomial * x;
            }
            result = result + monomial;
        }
        return result;
    }
};

template <class CoeffType>
Polynomial<CoeffType> operator+(Polynomial<CoeffType> F, Polynomial<CoeffType> G)
{
    Polynomial<CoeffType> A;
    Polynomial<CoeffType> B;

    if(F.degree > G.degree)
    {
        A = F;
        B = G;
    }
    else
    {
        A = G;
        B = F;
    }

    CoeffType *sum_coeffs = new CoeffType[A.degree];
    for(int i = 0; i <= A.degree; i++)
    {
        if(i <= B.degree)
        {
            sum_coeffs[i] = A._coefficients[i] + B._coefficients[i];
        }
        else
        {
            sum_coeffs[i] = A._coefficients[i];
        }
    }
    Polynomial<CoeffType> P(sum_coeffs, A.degree+1);
    delete sum_coeffs;
    return P;
}

template <class CoeffType>
Polynomial<CoeffType> operator*(Polynomial<CoeffType> F, Polynomial<CoeffType> G)
{
    CoeffType *product_coeffs = new CoeffType[F.degree + G.degree];
    for(int i = 0; i <= F.degree; i++)
    {
        for(int j = 0; j <= G.degree; j++)
        {
            product_coeffs[i+j] = F._coefficients[i] * G._coefficients[j];
        }
    }
    Polynomial<CoeffType> P(product_coeffs, F.degree + G.degree);
    delete product_coeffs;
    return P;
}