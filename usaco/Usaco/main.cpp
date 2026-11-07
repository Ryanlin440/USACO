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
    int n, t;
    cin>>n>> t;
    vector<int>a(n);
    
    for(int i = 0; i < n; i++){
        cin>>a[i];
    }
    int sum=0,count=0;
    int big = 0;
    int lastIndex = 0;
    for(int i = 0; i < n; i++){
        if(lastIndex == 0){
            if(a[i] <= t){
                sum=a[i];
                count=1;
            }else{
                sum= 0;
                count=0;
            }
            for(int j = i+1; j < n; j++){
                if(sum+a[j] > t) break;
                sum+=a[j];
                count++;
                lastIndex = j;
            }
            // cout<<lastIndex;
            big = count;
            // cout<<sum<<endl;
        }else{
            //i > 0
            sum -= a[i-1];//get rid of first;
            count--;
            // cout<<sum<<endl;
            while(sum < t){//1 < 5
                lastIndex++;//2
                
                if(lastIndex < n && sum + a[lastIndex] <= t){
                    sum+=a[lastIndex];
                    count++;
                    // cout<<a[lastIndex]<<' ';
                }else{
                    lastIndex--;
                    break;
                }
            }
            // cout<<endl;
            big = max(big, count);
        }

        
        // big = max(big, count);
    }
    // if(!(sum+a[n-1] > t)){
    //     count++;
    //     big = max(big, count);
    // }
            
    cout<<big;


}
//sliding window? if sum too big then reduce and vice versa