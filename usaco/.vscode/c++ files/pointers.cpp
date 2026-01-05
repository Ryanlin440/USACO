/*
ID: ryanlin2
TASK:
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
using namespace std;



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("temporary.in");//temporary
    ofstream fout("temporary.out");

    std::vector<int> a = {10, 20, 30, 40, 50};
    int first = *a.begin();
    int last = *prev(a.end())+1;
    int second = *next(a.begin());
    int secondLast = *prev(prev(a.end()));
    for(auto i = a.begin(); i != a.end(); i++){
    }
    auto anotherFirst = &first;
    first = 200;
    // cout<<*anotherFirst<<endl;

    // cout<<first<< ' '<<second<<' '<<secondLast<<' ' <<last;
    auto f = a.begin();
    f += 3;
    // cout << *f;
    int lol = 1 << 4;
    cout<<lol;

}
// ryanlin@RyansMacbook usaco % g++ -std=c++17 main.cpp -o ryan.out && ./ryan.out