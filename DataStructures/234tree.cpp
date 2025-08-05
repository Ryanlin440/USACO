#include <iostream>
using namespace std;

// Represents a data item with a double value.
class DataItem
{
public:
    double dData;              // The value of the data item.
    DataItem() : dData(0.0) {} // default constructor

    DataItem(double dd) : dData(dd) {} // Constructor to initialize with a specific value.
    void displayItem()                 // Displays the data item.
    {
        cout << '/' << dData;
    }
};

class Node
{
private:
    enum // Constants and properties of a 2-3-4 tree.
    {
        ORDER = 4 // max num of children
    };
    int numItems;                   // num of data items ina node
    Node *pParent;                  // pointer to parent
    Node *childArray[ORDER];        // array of child node pointers
    DataItem *itemArray[ORDER - 1]; // array of data items in the node

public:
    Node() : numItems(0) // Constructor to initialize the node.
    {                    // Initialize child and item pointers to NULL.

        for (int j = 0; j < ORDER; j++)
            childArray[j] = NULL;
        for (int k = 0; k < ORDER - 1; k++)
            itemArray[k] = NULL;
    }
    void connectChild(int childNum, Node *pChild) // Connects a child node to this node.
    {
        childArray[childNum] = pChild;
        if (pChild != NULL)
            pChild->pParent = this; // Set parent pointer in child.
    }
    Node *disconnectChild(int childNum) // Disconnects a child node and returns it.
    {
        Node *pTempNode = childArray[childNum];
        childArray[childNum] = NULL;
        return pTempNode;
    }
    Node *getChild(int childNum) // Returns a pointer to the specified child.
    {
        return childArray[childNum];
    }
    Node *getParent() // Returns the parent of this node.
    {
        return pParent;
    }
    bool isLeaf() // Checks if the node is a leaf (no children).
    {
        return (childArray[0] == NULL) ? true : false;
    }
    int getNumItems() // Gets the number of data items in this node.
    {
        return numItems;
    }
    DataItem getItem(int index) // Gets a data item at the specified index.
    {
        return *(itemArray[index]);
    }
    bool isFull() // Checks if the node is full.
    {
        return (numItems == ORDER - 1) ? true : false;
    }
    int findItem(double key) // Finds the index of a data item with the given key.
    {
        for (int j = 0; j < ORDER - 1; j++)
        {
            if (itemArray[j] == NULL)
                break;
            else if (itemArray[j]->dData == key)
                return j;
        }
        return -1;
    }
    int insertItem(DataItem *pNewItem) // Finds the index of a data item with the given key.
    {
        numItems++;
        double newKey = pNewItem->dData;

        for (int j = ORDER - 2; j >= 0; j--)
        {
            if (itemArray[j] == NULL) // skip the emtpy ones
                continue;
            else
            {
                double itsKey = itemArray[j]->dData;
                if (newKey < itsKey)
                    itemArray[j + 1] = itemArray[j]; // Shift right
                else
                {
                    itemArray[j + 1] = pNewItem; // Insert here.
                    return j + 1;
                }
            }
        }
        itemArray[0] = pNewItem; // Insert at the first position.
        return 0;
    }
    DataItem *removeItem() // Removes and returns the rightmost data item.
    {
        DataItem *pTemp = itemArray[numItems - 1];
        itemArray[numItems - 1] = NULL; // Remove reference.
        numItems--;                     // Remove reference.
        return pTemp;
    }
    void displayNode() // Displays the items in the node.

    {
        for (int j = 0; j < numItems; j++)
            itemArray[j]->displayItem();
        cout << '/';
    }
};
class Tree234 // Represents a 2-3-4 tree.
{
private:
    Node *pRoot; // Pointer to the root node.

public:
    // Constructor to initialize the tree.

    Tree234()
    {
        pRoot = new Node;
    }
    // Finds a data item with the given key in the tree.

    int find(double key)
    {
        Node *pCurNode = pRoot;
        int childNumber;
        while (true)
        {
            if ((childNumber = pCurNode->findItem(key)) != -1) // found
                return childNumber;
            else if (pCurNode->isLeaf()) // not found in leaf
                return -1;
            else
                pCurNode = getNextChild(pCurNode, key); // go deeper
        }
    }
    void insert(double dValue) //    // Inserts a value into the tree.
    {
        Node *pCurNode = pRoot;
        DataItem *pTempItem = new DataItem(dValue);
        while (true)
        {
            if (pCurNode->isFull()) // Split if node is full.
            {
                split(pCurNode);
                pCurNode = pCurNode->getParent();
                pCurNode = getNextChild(pCurNode, dValue);
            }
            else if (pCurNode->isLeaf()) // Insert at the leaf.
                break;
            else
                pCurNode = getNextChild(pCurNode, dValue);
        }
        pCurNode->insertItem(pTempItem);
    }
    void split(Node *pThisNode) // Splits a full node.
    {
        DataItem *pItemB, *pItemC;
        Node *pParent, *pChild2, *pChild3;
        int itemIndex;

        pItemC = pThisNode->removeItem(); // Rightmost item.
        pItemB = pThisNode->removeItem(); // middle item
        pChild2 = pThisNode->disconnectChild(2);
        pChild3 = pThisNode->disconnectChild(3);

        Node *pNewRight = new Node;

        if (pThisNode == pRoot) // Create new root.
        {
            pRoot = new Node();
            pParent = pRoot;
            pRoot->connectChild(0, pThisNode);
        }
        else
            pParent = pThisNode->getParent();
        itemIndex = pParent->insertItem(pItemB); // Add middle to parent.
        int n = pParent->getNumItems();
        // Rearrange children.

        for (int j = n - 1; j > itemIndex; j--)
        {
            Node *pTemp = pParent->disconnectChild(j);
            pParent->connectChild(j + 1, pTemp);
        }
        pParent->connectChild(itemIndex + 1, pNewRight);

        pNewRight->insertItem(pItemC); // Add rightmost to new node.
        pNewRight->connectChild(0, pChild2);
        pNewRight->connectChild(1, pChild3);
    }
    // Determines the next child to traverse for a given value.

    Node *getNextChild(Node *pNode, double theValue)
    {
        int j;
        int numItems = pNode->getNumItems();
        for (j = 0; j < numItems; j++)
        {
            if (theValue < pNode->getItem(j).dData) // Traverse left.
                return pNode->getChild(j);
        }
        return pNode->getChild(j); // go right
    }
    void displayTree()
    {
        // Displays the tree structure.

        recDisplayTree(pRoot, 0, 0);
    }
    // Recursive helper to display the tree
    void recDisplayTree(Node *pThisNode, int level, int childNumber)
    {
        cout << "level=" << level << " child=" << childNumber << " ";
        pThisNode->displayNode();
        cout << endl;

        int numItems = pThisNode->getNumItems();
        for (int j = 0; j < numItems + 1; j++)
        {
            Node *pNextNode = pThisNode->getChild(j);
            if (pNextNode != NULL)
                recDisplayTree(pNextNode, level + 1, j);
            else
                return;
        }
    }
};

int main()
{
    double value;
    Tree234 *pTree = new Tree234;
    pTree->insert(50);
    pTree->insert(40);
    pTree->insert(60);
    pTree->insert(30);
    pTree->insert(70);
    while (true)
    {
        int found;
        cout << "Enter first letter of show, insert, or find: ";
        char choice;
        cin >> choice;
        switch (choice)
        {
        case 's':
            pTree->displayTree();
            break;
        case 'i':
            cout << "Enter value to insert: ";
            cin >> value;
            pTree->insert(value);
            break;
        case 'f':
            cout << "Enter value to find: ";
            cin >> value;
            found = pTree->find(value);
            if (found != -1)
                cout << "Found " << value << endl;
            else
                cout << "Could not find " << value << endl;
            break;
        default:
            cout << "Invalid entry\n";
        }
    }
    return 0;
    delete pTree;
}