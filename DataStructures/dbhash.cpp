#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class DataItem
{
public:
    int iData; // data item (key)

    DataItem(int ii) : iData(ii) {} // constructor
};

class HashTable
{
private:
    vector<DataItem *> hashArray; // vector holds the hash table
    int arraySize;
    DataItem *pNonItem; // placeholder for deleted items

public:
    HashTable(int size) : arraySize(size)
    {
        hashArray.resize(arraySize, nullptr); // initialize table
        pNonItem = new DataItem(-1);          // marker for deleted items
    }

    void displayTable()
    {
        cout << "Table: ";
        for (int j = 0; j < arraySize; j++)
        {
            if (hashArray[j] != nullptr)
                cout << hashArray[j]->iData << " ";
            else
                cout << "** ";
        }
        cout << endl;
    }

    int hashFunc1(int key)
    {
        return key % arraySize; // primary hash function
    }

    int hashFunc2(int key)
    {
        return 5 - (key % 5); // secondary hash function
    }

    void insert(int key, DataItem *pItem)
    {
        int hashVal = hashFunc1(key);
        int stepSize = hashFunc2(key);

        while (hashArray[hashVal] != nullptr && hashArray[hashVal]->iData != -1)
        {
            hashVal += stepSize;  // apply step size
            hashVal %= arraySize; // wrap around
        }

        hashArray[hashVal] = pItem; // insert item
    }

    DataItem *remove(int key)
    {
        int hashVal = hashFunc1(key);
        int stepSize = hashFunc2(key);

        while (hashArray[hashVal] != nullptr)
        {
            if (hashArray[hashVal]->iData == key)
            {
                DataItem *pTemp = hashArray[hashVal];
                hashArray[hashVal] = pNonItem; // mark as deleted
                return pTemp;
            }

            hashVal += stepSize;
            hashVal %= arraySize;
        }
        return nullptr; // item not found
    }

    DataItem *find(int key)
    {
        int hashVal = hashFunc1(key);
        int stepSize = hashFunc2(key);

        while (hashArray[hashVal] != nullptr)
        {
            if (hashArray[hashVal]->iData == key)
                return hashArray[hashVal];

            hashVal += stepSize;
            hashVal %= arraySize;
        }
        return nullptr; // item not found
    }
};

int main()
{
    int aKey, size, n;
    char choice;
    DataItem *pDataItem;

    cout << "Enter size of hash table (use prime number): ";
    cin >> size;
    cout << "Enter initial number of items: ";
    cin >> n;

    HashTable theHashTable(size);
    srand(static_cast<unsigned>(time(0)));

    for (int j = 0; j < n; j++)
    {
        aKey = rand() % (2 * size);
        pDataItem = new DataItem(aKey);
        theHashTable.insert(aKey, pDataItem);
    }

    while (true)
    {
        cout << "Enter first letter of show, insert, delete, or find (or 'x' to exit): ";
        cin >> choice;

        switch (choice)
        {
        case 's':
            theHashTable.displayTable();
            break;
        case 'i':
            cout << "Enter key value to insert: ";
            cin >> aKey;
            pDataItem = new DataItem(aKey);
            theHashTable.insert(aKey, pDataItem);
            break;
        case 'd':
            cout << "Enter key value to delete: ";
            cin >> aKey;
            if (theHashTable.remove(aKey))
                cout << "Deleted " << aKey << endl;
            else
                cout << "Key not found." << endl;
            break;
        case 'f':
            cout << "Enter key value to find: ";
            cin >> aKey;
            pDataItem = theHashTable.find(aKey);
            if (pDataItem != nullptr)
                cout << "Found " << pDataItem->iData << endl;
            else
                cout << "Key not found." << endl;
            break;
        case 'x':
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid entry." << endl;
        }
    }

    return 0;
}
