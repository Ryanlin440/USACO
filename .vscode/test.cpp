#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>
using namespace std;
int main()
{
    vector<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    reverse(a.begin(), a.end());
    for (const auto c : a)
    {
        cout << c << ' ';
    }
    return 0;
}