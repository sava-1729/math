#include <iostream>
#include "set.hpp"
#include "utils.hpp"
#include "binary_operation.hpp"
#include <vector>
#include <string>
#include <tuple>
using namespace std;

class X
{
    public:
    int add7(int x, int y)
    {
        return (x+y)%7;
    }
};
int main()
{
    // {0,1,2,3,4,5,6};
    //string arr[] = {"vatsal", "srivastava", "alstav", "Trivas", "Sava", "sava", "srivastava"};
    int arr2[] = {0,1,2,3,4,5,6};//{"tanmay", "Srivastava", "yatman", "trivas", "sava", "sava", "srivastava"};
    FiniteSet<int> S1 = FiniteSet<int>(arr2, 7);
    //cout << S1 << endl;
    X obj;
    BinaryOperation<int, int, int, X> modulo7add(S1, S1, S1, &obj, &X::add7, true);
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            cout << "modulo7add.operate(" << i << "," << j << ") = " << modulo7add.operate(i,j) << endl;
        }
    }
    // FiniteSet<int> S2 = FiniteSet<int>(arr2, 7);
    //FiniteSet<std::tuple<string,string>> S3 = cartesianProduct<string,string>(S1, S2);
    // FiniteSet<string> S4 = S1 ^ S2;
    //std::tuple<string,string>* elms;
    //S3.getAllElements(elms);
    // int order = S3.getOrder();
    // for(int i = 0; i<order; i++)
    // {
    //     cout << get<0>(elms[i]) << ", " <<  get<1>(elms[i]) << endl;
    // }
    // cout << " \"sava\" < S1 = " << (string("sava") < S1) << endl;
    // cout << " \"sava\" < S2 = " << (string("sava") < S2) << endl;
    return 0;
}
// class A
// {
//     private:
//     int x;
//     public:
//     A(int y)
//     {
//         x = y;
//     }
//     void print(A obj)
//     {
//         cout << "self.x = " << x << endl;
//         cout << "obj.x = " << obj.x << endl;
//     }
// };
//     tuple<> emp;
//     tuple<int> uno = make_tuple(1729);
//     tuple<std::int, char> dos = make_tuple("oh",'f');
//     tuple<float, bool, std::int> tres = make_tuple(2.718, false, "vatsal rocks");
//     auto concat = tuple_cat(emp, uno, dos, tres);
//     for(int i = 0; i < tuple_size<decltype(concat)>::value; i++)
//     {
//         const int j = i;
//         //cout << get<j>(concat) << ", ";
//     }
//     int a[] = {1,32,35,12,57,8,63,3,7821};
//     int b[] = {1,32,5,2,7,1,63,3,721};
//     FiniteSet<int> s1 = FiniteSet<int>(a, 9);
//     FiniteSet<int> s2 = FiniteSet<int>(b, 9);
//     FiniteSet<int> s3 = s1 ^ s2;

    