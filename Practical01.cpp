#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    string name;
    int rollNo;
    float marks;

public:
    Student()
    {
        cout << "Constructor is called." << endl;

        name = "Tejal";
        rollNo = 139;
        marks = 85.5;
    }
    void displayDetails()
    {
        cout << "\n--- Student Details ---" << endl;
        cout << "Name    : " << name << endl;
        cout << "Roll No : " << rollNo << endl;
        cout << "Marks   : " << marks << endl;
    }
    void calculateGrade()
    {
        if (marks >= 80)
            cout << "Grade   : A" << endl;
        else if (marks >= 60)
            cout << "Grade   : B" << endl;
        else if (marks >= 40)
            cout << "Grade   : C" << endl;
        else
            cout << "Grade   : F" << endl;
    }
    ~Student()
    {
        cout << "\nDestructor is called." << endl;
    }
};

int main()
{
    Student student;
    student.displayDetails();
    student.calculateGrade();

    return 0;
}