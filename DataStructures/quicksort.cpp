#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class ArrayIns
{
private:
    vector<double>(theVect);
    int nElems;

public:
    ArrayIns(int max) : nElems(0)
    {
        theVect.resize(max);
    }
    void insert(double value)
    {
        theVect[nElems++] = value;
    }
    void display()
    {
        cout << "A=";
        for (int j = 0; j < nElems; j++)
            cout << theVect[j] << ' ';
        cout << endl;
    }
    void quickSort()
    {
        recQuickSort(0, nElems - 1);
    }
    void recQuickSort(int left, int right)
    { //?????????? int
        if (right - left <= 0)
        {
            return; // base case
        }
        else
        {
            double pivot = theVect[right]; // since nelems-1;
            int partition = partitionIt(left, right, pivot);
            recQuickSort(left, partition - 1);
            recQuickSort(partition + 1, right);
        }
    }
    int partitionIt(int left, int right, double pivot)
    {
        int leftMark = left - 1;
        int rightMark = right;
        while (true)
        {
            while (theVect[++leftMark] < pivot)
            {
            }
            while (theVect[--rightMark] > pivot && rightMark > 0)
            {
            }
            if (leftMark >= rightMark)
                break;
            else
            {
                swap(leftMark, rightMark);
            }
        }
        swap(leftMark, right);
        return leftMark;
    }
    void swap(int dex1, int dex2)
    {
        double temp = theVect[dex1];
        theVect[dex1] = theVect[dex2];
        theVect[dex2] = temp;
    }
};
int main()
{
    time_t aTime;
    int maxSize = 16;                           // array size
    ArrayIns arr(maxSize);                      // create array
    srand(static_cast<unsigned>(time(&aTime))); // seed randoms
    for (int j = 0; j < maxSize; j++)
    {
        double n = rand() % 199;
        arr.insert(n);
    }
    arr.display();
    arr.quickSort();
    arr.display();
    return 0;
}