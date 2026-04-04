#include <iostream>
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
    ifstream fin("temporary.in");//temporary
    ofstream fout("temporary.out"); 
    int t;
    cin>>t;
    while(t--){
      int n;
      string s;
      cin>>n>>s;//break into characters and check each
      unordered_set<char>firstHalf;
      unordered_set<char>secondHalf;
      map<char, int>m;
      int maxPoints = s.length();

      firstHalf.insert(s[0]);
      m[s[0]]=1;
      for(int i = 1; i < maxPoints; i++){
        secondHalf.insert(s[i]);
        if(m.find(s[i]) != m.end()){
          m[s[i]]++;
        } else {
          m[s[i]]=1;
        }
      }
      m[s[0]]--;
      int sum = firstHalf.size() + secondHalf.size();
      for(int i = 1; i < maxPoints-1; i++){
        firstHalf.insert(s[i]);
        
        if(m[s[i]] < 2){ //normal
          secondHalf.erase(s[i]);
        }else{//if on both sides
          m[s[i]]--;
        }

        int j = firstHalf.size() + secondHalf.size();
        sum = max(sum, j);
      }
      cout<<sum<<endl;
      

    }


}
