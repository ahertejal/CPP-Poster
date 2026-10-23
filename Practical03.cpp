#include <iostream>
#include <string>
using namespace std;

class Employee
{
public:
    int id;
    string name;
    float salary;

    Employee()
    {
        id = 0;
        name = "Unknown";
        salary = 0;
    }

    Employee(int i, string n, float s)
    {
        id = i;
        name = n;
        salary = s;
    }

    Employee operator+(Employee e)
    {
        Employee temp;

        temp.id = id + e.id;
        temp.name = name + " & " + e.name;
        temp.salary = salary + e.salary;

        return temp;
    }

    void display()
    {
        cout << "Employee ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Salary: " << salary << endl;
    }
};

int main()
{
    Employee e1;

    e1.id = 101;
    e1.name = "Rahul";
    e1.salary = 50000;

    Employee e2(102, "Priya", 70000);

    Employee e3 = e1 + e2;

    cout << "Employee 1:" << endl;
    e1.display();

    cout << "\nEmployee 2:" << endl;
    e2.display();

    cout << "\nAfter Operator Overloading:" << endl;
    e3.display();

    return 0;
}