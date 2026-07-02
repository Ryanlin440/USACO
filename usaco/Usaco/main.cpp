#include <iostream> //g++ -std=c++20 Usaco/main.cpp -o Usaco/ryan.out && Usaco/ryan.out
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include<map>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
using namespace std;
using ll = long long;//woah
//    vector<vector<int>> a(3, vector<int>(3));



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ifstream fin("Usaco/temporary.in");//temporary
    ofstream fout("Usaco/temporary.out"); 
    
    long int i,j,a,b,c,n,k,ans,rem;
    while(cin>>n>>a>>b>>c)
    {
          ans=0;
       for(i=0;i*a<=n;++i)
       {
           for(j=0;i*a+j*b<=n;++j)
           {
                rem=n-i*a-j*b;
                if(rem%c==0)
                {
                    k=rem/c;
                ans=max(ans,i+j+k);}
           }

       }
       cout<<ans<<endl;
    }
    return 0;



}//53 10 11 23
//50 - 3
//40 - 13
//30 - 23.     10 10 10 23
//20 - 33      10 10 11 11 11
//10 - 43 
//0 - 53 23 

//29 7 10 12
//28 - 1
//21 - 8
//14 - 15
//7 - 22

//27 4 7 10
//24 - 3 lefover
//20 - 7 left over
//16 - 11
//12 - 15 left over
//8 - 19 left over
//4 - 
//4 4 4 4 4 7