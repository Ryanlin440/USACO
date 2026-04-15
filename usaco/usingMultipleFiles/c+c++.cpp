#include <iostream>
#include "MyFunctions.hpp"
using namespace std;
int main (){
    sayHello();
    cout<<addNumbers(52,5);
    return 0;

}
//g++ -std=c++20 usingMultipleFiles/c+c++.cpp usingMultipleFiles/MyFunctions.cpp -o ryan.out && ./ryan.out