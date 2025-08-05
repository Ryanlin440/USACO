/*
ID: ryanlin2
TASK:hamming
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
int main()
{

    ifstream fin("speeding.in");
    ofstream fout("speeding.out"); 
    int t;
    cin>>t;
    for(int i = 0; i < t; i++){
        int n;
        cin>>n;
        vector<int>a(n);
        for(int j = 0; j <n; j++){
            cin>>a[j];
        }
        sort(a.begin(), a.end());
        int count =0,ans=1;
        // for(int c : a){
        //     cout<<c<<' ';
        // }
        for(int j = 0; j <n-1; j++){
            bool f= false;
            while(a[j] == a[j+1] && a[j] != a[a.size()-1]){ 
                if(!f){
                    count+=2;
                    f=true;
                } 
             // cout<<count;
                j++;
            }
        }
        ans+=count;

        
        cout<<ans<<endl;

    }
   
}
//abcabbacabac
// bcabba
// abbac
// bcab
// cabbacab