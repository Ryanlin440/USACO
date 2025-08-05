#include <iostream>
using namespace std;

int main()
{
    int x = 42;    // A variable
    int *ptr = &x; // Pointer storing the address of x

    cout << "Value of x: " << x << endl;           // Prints 42
    cout << "Address of x: " << &x << endl;        // Prints x's address
    cout << "Pointer (address): " << ptr << endl;  // Prints the same address as &x
    cout << "Value via pointer: " << *ptr << endl; // Prints 42 (dereference ptr)

    *ptr = 100;                              // Modify the value of x through the pointer
    cout << "New value of x: " << x << endl; // Prints 100
    return 0;
}
