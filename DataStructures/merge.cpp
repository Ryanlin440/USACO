#include <iostream>
#include <vector>
using namespace std;
class DArray
{
private:
    vector<double>(theVect);                     // store elements
    int nElems;                                  // how many numbers are in theVect
    void recMergeSort(vector<double>, int, int); // preforms merge sort
    void merge(vector<double>, int, int, int);   // merge 2 subarrays that is sorted by recMergeSort

public:
    DArray(int max) : nElems(0) // contructor
    {
        theVect.resize(max); // defines maximum
    }
    void insert(double value)
    {
        theVect[nElems++] = value; // inserts
    }
    void display()
    {
        for (int j = 0; j < nElems; j++)
        {
            cout << theVect[j] << ' '; // displays
        }
        cout << endl;
    }
    void mergeSort() // creates a temporary workspace
    {
        vector<double>(workSpace); // temporary workspace to assist in actual sorting
        workSpace.resize(nElems);
        recMergeSort(workSpace, 0, nElems - 1); // starts sorting
    }
};
void DArray ::recMergeSort(vector<double> workSpace, int lowerBound, int upperBound)
{
    if (lowerBound == upperBound)
    {
        return;
    }
    else
    {
        int mid = (lowerBound + upperBound) / 2;
        recMergeSort(workSpace, lowerBound, mid);     //    sorts lower half
        recMergeSort(workSpace, mid + 1, upperBound); // sort upper half
        // for (int i = 0; i <= upperBound; i++)
        // {
        //     cout << theVect[i] << ' ';
        // }
        // cout << endl;
        merge(workSpace, lowerBound, mid + 1, upperBound); // merge upper and lower together
    }
}
void DArray::merge(vector<double> workSpace, int lowPtr, int highPtr, int upperBound)
{ // highPtr is mid
    int j = 0;
    int lowerBound = lowPtr;
    int mid = highPtr - 1;               // 1 element before highPtr which is the middle
    int n = upperBound - lowerBound + 1; // # of items in both
                                         // low and high pointers traverse through the 2 halves and sorts them into work space
    while (lowPtr <= mid && highPtr <= upperBound)
        if (theVect[lowPtr] < theVect[highPtr])
            workSpace[j++] = theVect[lowPtr++];
        else
            workSpace[j++] = theVect[highPtr++];

    while (lowPtr <= mid) // if there are leftovers
        workSpace[j++] = theVect[lowPtr++];
    while (highPtr <= upperBound)
        workSpace[j++] = theVect[highPtr++];

    for (j = 0; j < n; j++)
    {                                           // copies it over
        theVect[lowerBound + j] = workSpace[j]; //????
    }
}

int main()
{
    const int maxSize = 100;
    DArray arr(maxSize);

    arr.insert(64);
    arr.insert(21);
    arr.insert(33);
    arr.insert(70);
    arr.insert(12);
    arr.insert(85);
    arr.insert(44);
    arr.insert(3);
    arr.insert(99);
    arr.insert(0);
    arr.insert(108);
    arr.insert(36);

    arr.display();
    arr.mergeSort();
    arr.display();
    return 0;

    return 0;
}
