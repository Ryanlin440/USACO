#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
class Link
{
public:
    int iData;
    Link *pNext;
    Link(int it) : iData(it) {}
    void displayList()
    {
        cout << iData << ' ';
    }
};
class SortedList
{
private:
    Link *pFirst;

public:
    SortedList()
    {
        pFirst = NULL;
    }
    void insert(Link *pLink)
    {
        int key = pLink->iData;
        Link *pPrevious = NULL;
        Link *pCurrent = pFirst;

        while (pCurrent != NULL && key > pCurrent->iData)
        {
            pPrevious = pCurrent;
            pCurrent = pCurrent->pNext;
        }
        if (pPrevious == NULL)
            pFirst = pLink;
        else
            pPrevious->pNext = pLink;
        pLink->pNext = pCurrent;
    }
    void remove(int key)
    {
        Link *pPrevious = NULL;
        Link *pCurrent = pFirst;

        while (pCurrent != NULL && key != pCurrent->iData)
        {
            pPrevious = pCurrent;
            pCurrent = pCurrent->pNext;
        }
        if (pPrevious == NULL)
            pFirst = pFirst->pNext;
        else
            pPrevious->pNext = pCurrent->pNext;
    }
    Link *find(int key)
    {
        Link *pCurrent = pFirst;

        while (pCurrent != NULL && pCurrent->iData <= key)
        {
            if (pCurrent->iData == key)
                return pCurrent;
            pCurrent = pCurrent->pNext;
        }
        return NULL;
    }
    void displayList()
    {
        cout << "List (first->last): ";
        Link *pCurrent = pFirst;
        while (pCurrent != NULL)
        {
            pCurrent->displayList();
            pCurrent = pCurrent->pNext;
        }
        cout << endl;
    }
};
class HashTable
{
private:
    vector<SortedList *> hashArray;
    int arraySize;

public:
    HashTable(int size)
    {
        arraySize = size;
        hashArray.resize(arraySize);
        for (int j = 0; j < arraySize; j++)
            hashArray[j] = new SortedList;
    }
    void displayTable()
    {
        for (int j = 0; j < arraySize; j++)
        {
            cout << j << ". ";
            hashArray[j]->displayList();
        }
    }
    int hashFunc(int key)
    {
        return key % arraySize;
    }
    void insert(Link *pLink)
    {
        int key = pLink->iData;
        int hashVal = hashFunc(key);
        hashArray[hashVal]->insert(pLink);
    }
    void remove(int key)
    {
        int hashVal = hashFunc(key);
        hashArray[hashVal]->remove(key);
    }
    Link *find(int key)
    {
        int hashVal = hashFunc(key);
        Link *pLink = hashArray[hashVal]->find(key);
        return pLink;
    }
};

int main()
{
    int aKey;
    Link *pDataItem;
    int size, n, keysPerCell = 100;
    time_t aTime;
    char choice = 'b';

    cout << "enter size of hash table: ";
    cin >> size;
    cout << "enter initial number of items: ";
    cin >> n;
    HashTable theHashTable(size);
    srand(static_cast<unsigned>(time(&aTime)));

    for (int j = 0; j < n; j++)
    {
        aKey = rand() % (keysPerCell * size);
        pDataItem = new Link(aKey);
        theHashTable.insert(pDataItem);
    }
    while (choice != 'x')
    {
        cout << "enter first letter of show, insert, delete, or find: ";
        cin >> choice;
        switch (choice)
        {
        case 's':
            theHashTable.displayTable();
            break;
        case 'i':
            cout << "enter key value to insert: ";
            cin >> aKey;
            pDataItem = new Link(aKey);
            theHashTable.insert(pDataItem);
            break;
        case 'd':
            cout << "enter key vale to delete: ";
            cin >> aKey;
            theHashTable.remove(aKey);
            break;
        case 'f':
            cout << "enter key vale to find: ";
            cin >> aKey;
            pDataItem = theHashTable.find(aKey);
            if (pDataItem != NULL)
                cout << "Found " << aKey << endl;
            else
                cout << "Could not find " << aKey << endl;
            break;
        default:
            cout << "try again\n";
        }
    }
    return 0;
}