#include <iostream>
#include <string>
using namespace std;

int hashFunc1(string key)
{
    int hashVal = 0;
    int pow27 = 1;
    for (int j = key.length() - 1; j >= 0; j--)
    {
        int letter = key[j] - 96;
        hashVal += pow27 * letter;
        pow27 *= 27;
    }
    return hashVal % 4;
}
int main()
{
    cout << hashFunc1("catsanddogs");
}