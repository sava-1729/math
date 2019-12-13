#include <iostream>
#include "set.hpp"
#include <vector>
#include <string>
#include <tuple>
using namespace std;

class A
{
    private:
    int x;
    public:
    A(int y)
    {
        x = y;
    }
    void print(A obj)
    {
        cout << "self.x = " << x << endl;
        cout << "obj.x = " << obj.x << endl;
    }
};
int main()
{
    // tuple<> emp;
    // tuple<int> uno = make_tuple(1729);
    // tuple<std::string, char> dos = make_tuple("oh",'f');
    // tuple<float, bool, std::string> tres = make_tuple(2.718, false, "vatsal rocks");
    // auto concat = tuple_cat(emp, uno, dos, tres);
    // for(int i = 0; i < tuple_size<decltype(concat)>::value; i++)
    // {
    //     const int j = i;
    //     //cout << get<j>(concat) << ", ";
    // }
    // int a[] = {1,32,35,12,57,8,63,3,7821};
    // int b[] = {1,32,5,2,7,1,63,3,721};
    // Set<int> s1 = Set<int>(a, 9);
    // Set<int> s2 = Set<int>(b, 9);
    // Set<int> s3 = s1 ^ s2;

    string arr[] = {"vatsal", "srivastava", "alstav", "Trivas", "Sava", "sava", "srivastava"};
    string arr2[] = {"tanmay", "Srivastava", "yatman", "trivas", "sava", "sava", "srivastava"};
    Set<string> S1 = Set<string>(arr, 7);
    Set<string> S2 = Set<string>(arr2, 7);
    Set<std::tuple<string,string>> S3 = cartesianProduct<string,string>(S1, S2);
    // Set<string> S4 = S1 ^ S2;
    std::tuple<string,string>* elms;
    S3.getAllElements(elms);
    int order = S3.getOrder();
    for(int i = 0; i<order; i++)
    {
        cout << get<0>(elms[i]) << ", " <<  get<1>(elms[i]) << endl;
    }
    // cout << "S1 is not a subset of S2: " << (bool)(S1>S2) << "\n"; 
    // cout << "S1 is not a subset of S3: " << (bool)(S1>S3) << "\n"; 
    // cout << "S1 is not a subset of S4: " << (bool)(S1>S4) << "\n"; 
    // cout << "S2 is not a subset of S1: " << (bool)(S2>S1) << "\n"; 
    // cout << "S2 is not a subset of S3: " << (bool)(S2>S3) << "\n"; 
    // cout << "S2 is not a subset of S4: " << (bool)(S2>S4) << "\n";
    // cout << "S3 is not a subset of S1: " << (bool)(S3>S1) << "\n"; 
    // cout << "S3 is not a subset of S2: " << (bool)(S3>S2) << "\n"; 
    // cout << "S3 is not a subset of S4: " << (bool)(S3>S4) << "\n"; 
    // cout << "S4 is not a subset of S1: " << (bool)(S4>S1) << "\n"; 
    // cout << "S4 is not a subset of S2: " << (bool)(S4>S2) << "\n"; 
    // cout << "S4 is not a subset of S3: " << (bool)(S4>S3) << "\n";
    // cout << "S4 is not a subset of S4: " << (bool)(S4==S4) << "\n";
    // cout << "S3 is not a subset of S3: " << (bool)(S3==S3) << "\n";
    // cout << "S2 is not a subset of S2: " << (bool)(S2==S2) << "\n";
    // cout << "S1 is not a subset of S1: " << (bool)(S1==S1) << "\n";
}