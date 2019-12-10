#include <iostream>
#include "set.hpp"
#include <vector>
#include <string>

using namespace std;
int main()
{
    // int a[] = {1,32,35,12,57,8,63,3,7821};
    // int b[] = {1,32,5,2,7,1,63,3,721};
    // Set<int> s1 = Set<int>(a, 9);
    // Set<int> s2 = Set<int>(b, 9);
    // Set<int> s3 = s1 ^ s2;
    string arr[] = {"vatsal", "srivastava", "alstav", "Trivas", "Sava", "sava", "srivastava"};
    string arr2[] = {"tanmay", "Srivastava", "yatman", "trivas", "sava", "sava", "srivastava"};
    Set<string> S1 = Set<string>(arr, 7);
    Set<string> S2 = Set<string>(arr2, 7);
    Set<string> S3 = S1 ^ S2;
    string* elms;
    // int* elms;
    S3.getAllElements(elms);
    int order = S3.getOrder();
    for(int i = 0; i < order; i++)
    {
        cout << elms[i] << endl;
    }
}