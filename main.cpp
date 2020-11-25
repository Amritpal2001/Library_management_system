#include <iostream>
#include "Student.h"
using namespace std;

int main()
{
    system("clear");
    cout << "\t\t\t\t\t\t\tStudent Login" << endl
         << endl;
    Student s;
    stu *student;
    while (true)
    {
        student = s.login();
        if (student == NULL)
        {
            cout << "Enter correct roll number and password" << endl;
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        system("clear");
        cout << endl
             << endl
             << "Welcome " << student->name << "\t\t\t\t\t\t\t\t\t\tRoll Number : " << student->roll_no << endl
             << endl;
        cout << "\t\t\t\t\t\t********************************" << endl;
        cout << "\t\t\t\t\t\t* Press 1 to see issued books  *" << endl;
        cout << "\t\t\t\t\t\t* Press 2 to issue a book      *" << endl;
        cout << "\t\t\t\t\t\t* Press 3 to return a book     *" << endl;
        cout << "\t\t\t\t\t\t* Press 4 to exit              *" << endl;
        cout << "\t\t\t\t\t\t********************************" << endl;
        int q;
        cin >> q;
        if (q == 1)
        {
            s.display(student);
            cin.get();
            cin.get();
        }
        else if (q == 2)
        {
            s.get_book(student);
            cin.get();
            cin.get();
        }
        else if (q == 3)
        {
            s.display(student);
            s.return_book(student);

            cin.get();
            cin.get();
        }
        else if (q == 4)
            return 0;
        else
        {
            cout << "Enter correct choice" << endl;
        }
    }

    return 0;
}