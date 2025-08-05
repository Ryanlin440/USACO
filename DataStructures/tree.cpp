#include <iostream>
#include <stack>
using namespace std;

class Node
{
public:
    int iData;
    double dData;
    Node *pLeftChild;
    Node *pRightChild;

    Node() : iData(0), dData(0.0), pLeftChild(nullptr), pRightChild(nullptr) {}
    ~Node()
    {
        cout << "X-" << iData << " ";
    }
    void displayNode()
    {
        cout << '{' << iData << ", " << dData << " }";
    }
};

class Tree
{
private:
    Node *pRoot;

public:
    Tree() : pRoot(nullptr) {}

    Node *find(int key)
    {
        Node *pCurrent = pRoot;
        while (pCurrent != nullptr && pCurrent->iData != key)
        {
            pCurrent = (key < pCurrent->iData) ? pCurrent->pLeftChild : pCurrent->pRightChild;
        }
        return pCurrent;
    }

    void insert(int id, double dd)
    {
        Node *pNewNode = new Node;
        pNewNode->iData = id;
        pNewNode->dData = dd;

        if (pRoot == nullptr)
            pRoot = pNewNode;
        else
        {
            Node *pCurrent = pRoot;
            Node *pParent;
            while (true)
            {
                pParent = pCurrent;
                if (id < pCurrent->iData)
                {
                    pCurrent = pCurrent->pLeftChild;
                    if (pCurrent == nullptr)
                    {
                        pParent->pLeftChild = pNewNode;
                        return;
                    }
                }
                else
                {
                    pCurrent = pCurrent->pRightChild;
                    if (pCurrent == nullptr)
                    {
                        pParent->pRightChild = pNewNode;
                        return;
                    }
                }
            }
        }
    }

    void traverse(int traverseType)
    {
        switch (traverseType)
        {
        case 1:
            cout << "\nPreorder traversal: ";
            preOrder(pRoot);
            break;
        case 2:
            cout << "\nInorder traversal: ";
            inOrder(pRoot);
            break;
        case 3:
            cout << "\nPostorder traversal: ";
            postOrder(pRoot);
            break;
        default:
            cout << "Invalid traversal type!";
        }
        cout << endl;
    }

    void preOrder(Node *pLocalRoot)
    {
        if (pLocalRoot != nullptr)
        {
            cout << pLocalRoot->iData << ' ';
            preOrder(pLocalRoot->pLeftChild);
            preOrder(pLocalRoot->pRightChild);
        }
    }

    void inOrder(Node *pLocalRoot)
    {
        if (pLocalRoot != nullptr)
        {
            inOrder(pLocalRoot->pLeftChild);
            cout << pLocalRoot->iData << ' ';
            inOrder(pLocalRoot->pRightChild);
        }
    }

    void postOrder(Node *pLocalRoot)
    {
        if (pLocalRoot != nullptr)
        {
            postOrder(pLocalRoot->pLeftChild);
            postOrder(pLocalRoot->pRightChild);
            cout << pLocalRoot->iData << ' ';
        }
    }

    void destroy()
    {
        destroyRec(pRoot);
    }

    void destroyRec(Node *pLocalRoot)
    {
        if (pLocalRoot != nullptr)
        {
            destroyRec(pLocalRoot->pLeftChild);
            destroyRec(pLocalRoot->pRightChild);
            delete pLocalRoot;
        }
    }
};

int main()
{
    int value;
    char choice = ' ';
    Node *found;
    Tree theTree;

    theTree.insert(50, 5.0);
    theTree.insert(25, 2.5);
    theTree.insert(75, 7.5);
    theTree.insert(12, 1.2);
    theTree.insert(37, 3.7);
    theTree.insert(43, 4.3);
    theTree.insert(30, 3.0);
    theTree.insert(33, 3.3);
    theTree.insert(87, 8.7);
    theTree.insert(93, 9.3);
    theTree.insert(97, 9.7);

    while (choice != 'q')
    {
        cout << "Enter first letter of show, insert, find, traverse, or quit: ";
        cin >> choice;
        switch (choice)
        {
        case 's':
            cout << "Tree display not implemented yet." << endl;
            break;
        case 'i':
            cout << "Enter a value to insert: ";
            cin >> value;
            theTree.insert(value, value + 0.9);
            break;
        case 'f':
            cout << "Enter value to find: ";
            cin >> value;
            found = theTree.find(value);
            if (found != nullptr)
            {
                cout << "Found: ";
                found->displayNode();
                cout << endl;
            }
            else
            {
                cout << "Didn't find " << value << endl;
            }
            break;
        case 't':
            cout << "Enter traverse type (1=preorder, 2=inorder, 3=postorder): ";
            cin >> value;
            theTree.traverse(value);
            break;
        case 'q':
            theTree.destroy();
            cout << "Tree destroyed.\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}
