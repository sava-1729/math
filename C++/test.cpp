#include <iostream>
#include "finite_set.hpp"
#include "utils.hpp"
#include "binary_operation.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <tuple>
using namespace std;

class X
{
    public:
    int m;
    int add7(int x, int y)
    {
        return (x+y)%m;
    }
};
int main()
{
    int arr1[] = {0,1,2,3,4};
    int arr2[] = {0,1,2,3,4,5,6};
    FiniteSet<int> S1 = FiniteSet<int>(arr1, 5);
    FiniteSet<int> S2 = FiniteSet<int>(arr2, 7);
    X obj; obj.m = 5;
    BinaryOperation<int, int, int, X> modulo7add(&obj, &X::add7);
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            cout << "modulo7add.operate(" << i << "," << j << ") = " << modulo7add.operate(i,j) << endl;
        }
    }
    return 0;
}
