#include <iostream>
using namespace std;

int main()
{
    // Reference and Pointer
    int num = 10;

    int &ref = num;       // Reference to num
    int *ptr = &num;      // Pointer stores address of num

    cout << "Original value: " << num << endl;
    cout << "Value using reference: " << ref << endl;
    cout << "Value using pointer: " << *ptr << endl;

    // Dynamic memory allocation using new
    int *p = new int;

    *p = 50;

    cout << "\nDynamically allocated value: " << *p << endl;

    // Deallocate memory using delete
    delete p;

    // Dynamic array allocation
    int n;

    cout << "\nEnter number of elements: ";
    cin >> n;

    int *arr = new int[n];

    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    cout << "Array elements are: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    // Deallocate array memory
    delete[] arr;

    return 0;
}