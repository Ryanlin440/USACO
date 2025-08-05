#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class ArrayIns
{
private:
    vector<double> theVect; // Correct syntax for member variable
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
        {
            cout << theVect[j] << ' ';
        }
        cout << endl;
    }
    void quickSort()
    {
        recQuickSort(0, nElems - 1);
    }
    void recQuickSort(int left, int right)
    {
        int size = right - left + 1; // Correct size calculation
        if (size <= 3)
            manualSort(left, right);
        else
        {
            double median = medianOf3(left, right);
            int partition = partitionIt(left, right, median);
            recQuickSort(left, partition - 1);
            recQuickSort(partition + 1, right);
        }
    }
    double medianOf3(int left, int right)
    {
        int center = (left + right) / 2;
        if (theVect[left] > theVect[center])
            swap(left, center);
        if (theVect[left] > theVect[right])
            swap(left, right);
        if (theVect[center] > theVect[right])
            swap(center, right);
        swap(center, right - 1);
        return theVect[right - 1]; // Return the median
    }
    void swap(int dex1, int dex2)
    {
        double temp = theVect[dex1];
        theVect[dex1] = theVect[dex2];
        theVect[dex2] = temp;
    }
    int partitionIt(int left, int right, double pivot)
    {
        int leftMark = left;
        int rightMark = right - 1;
        while (true)
        {
            while (leftMark < right && theVect[++leftMark] < pivot)
            {
            } // Guard condition
            while (rightMark > left && theVect[--rightMark] > pivot)
            {
            } // Guard condition
            if (leftMark >= rightMark)
                break;
            else
            {
                swap(leftMark, rightMark);
            }
        }
        swap(leftMark, right - 1);
        return leftMark;
    }
    void manualSort(int left, int right)
    {
        int size = right - left + 1; // Correct size calculation
        if (size <= 1)
            return;
        if (size == 2)
        {
            if (theVect[left] > theVect[right])
                swap(left, right);
        }
        else
        {
            if (theVect[left] > theVect[right - 1])
                swap(left, right - 1);
            if (theVect[left] > theVect[right])
                swap(left, right);
            if (theVect[right - 1] > theVect[right])
                swap(right - 1, right);
        }
    }
};

int main()
{
    time_t aTime;
    int maxSize = 16;
    ArrayIns arr(maxSize);
    srand(static_cast<unsigned>(time(&aTime)));

    for (int i = 0; i < maxSize; i++)
    {
        arr.insert(rand() % 99); // Random numbers between 0 and 99
    }

    // Display and sort
    arr.display();
    arr.quickSort();
    arr.display();

    return 0;
}
