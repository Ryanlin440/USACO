/*
ID: ryanlin2
TASK:It's Mooin' Time II
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>
using namespace std;
// example test case
/*
3
1 3 2
3 2 1
--------
3
3
0
0


///////

3
1 2 3
1 2 3
---------
0
3
0
3
/////////
7
1 3 2 2 1 3 2
3 2 2 1 2 3 1
--------
0
6
14
6
2
0
0
0

*/
int main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    } // gets all the inputs

    vector<pair<int, int>> pos; // for the possible switches
    vector<int> points(n + 1);  // map of the points 0 included
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++) // no point looking backwards since it already would have been acounted for
        {
            pos.push_back(make_pair(a[i], a[j]));      // gets the reversing points
            vector<int> c = b;                         // copies the vector
            reverse(c.begin() + i, c.begin() + j + 1); // reverse in incluseive of the first point but exlusive of the second point
            int count = 0;
            for (int k = 0; k < n; k++)
            {
                if (a[k] == c[k]) // if its same then count++
                {
                    count++;
                }
            }
            points[count]++;
        }
    }
    for (const auto c : points)
    {
        cout << c << endl;
    }
}
