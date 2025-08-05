#include <vector>
#include <iostream>
#include <string>
using namespace std;
class word
{
private:
    int size;

    int count;
    string workStr;
    void rotate(int);
    void displayWord();

public:
    vector<string> a;
    word(string); // constructor
    void anagram(int);
};
word ::word(string inpStr) : workStr(inpStr), count(0), size(inpStr.length()) // constructor
{
}
void word::anagram(int newSize)
{
    if (newSize == 1)
    {
        return;
    }
    for (int j = 0; j < newSize; j++)
    {
        anagram(newSize - 1);
        if (newSize == 2)
        {
            displayWord();
        }
        rotate(newSize);
    }
}
void word::rotate(int newSize)
{
    int j;
    int position = size - newSize;
    char temp = workStr[position];
    for (j = position + 1; j < size; j++)
        workStr[j - 1] = workStr[j];
    workStr[j - 1] = temp; // put first on right side
}
void word::displayWord()
{
    if (count < 99)
        cout << " ";
    if (count < 9)
        cout << " ";
    cout << ++count << ' ';
    a.push_back(workStr);
    cout << workStr << "  ";
    if (count % 6 == 0)
    {
        cout << endl;
    }
}

int main()
{
    string input;
    int length;

    cout << "enter a word: ";
    cin >> input;
    length = input.length();

    word theWord(input);
    theWord.anagram(length);
    sort(theWord.a.begin(), theWord.a.end());
    for (auto l : theWord.a)
    {

        cout << l << endl;
    }
    return 0;
}