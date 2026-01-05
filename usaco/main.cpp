/*
ID: ryanlin2
TASK:
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>
#include<map>
using namespace std;
using ll = long long;//woah
//    vector<vector<int>> a(3, vector<int>(3));



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("pails.in");//temporary
    ofstream fout("pails.out");

    int x, y, m;
    fin >> x >> y >> m;
    int n = min(x, y);
    n = m / n;//38
    int ans = -1, placeHolder = n;
    for (int i = 0; i <= n; i++)
    {
        int yes = m - (x * i);
        int rem = yes / y;
        ans = max(ans, x*i+rem * y);
        // cout << yes << ' ' << rem << endl;
    }
    fout << ans;
}
