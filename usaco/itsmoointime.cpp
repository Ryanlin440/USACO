#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>
using namespace std;
/*
example
6
1 2 3 4 4 4
-------------
3

*/
int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    set<int> distinct;
    int count = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] == a[i + 1] && distinct.find(a[i]) == distinct.end())
        {
            count += distinct.size();
        }
        distinct.insert(a[i]);
    }

    cout << count << endl;
}
