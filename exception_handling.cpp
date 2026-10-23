#include <iostream>
using namespace std;
 
int main()
{
    int a, b;
 
    cout << "Enter two numbers: ";
    cin >> a >> b;
 
    try
    {
        if (b == 0)
        {
            throw b;
        }
 
        cout << "Result = " << a / b << endl;
    }
    catch (int x)
    {
        cout << "Exception caught: Division by zero is not allowed!" << endl;
    }
 
    cout << "Program continues..." << endl;
 
    return 0;
}
 
