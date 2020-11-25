#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Books.h"
using namespace std;
Book b;

string get_time()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string s;
    s = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
    return s;
}
struct issued_book
{
    string ref_no;
    string date_time;
    issued_book(string ref_no, string date_time)
    {
        this->ref_no = ref_no;
        this->date_time = date_time;
    }
};
struct stu
{
public:
    string roll_no;
    string name;
    string pass;
    issued_book *issued1;
    issued_book *issued2;
    int total_issued;
    stu *next;
    stu()
    {
        next = NULL;
        issued1 = issued2 = NULL;
        total_issued = 0;
    }
};

class Student
{
    stu *head;
    fstream file;
    stu *curr;

public:
    Student()
    {
        head = NULL;
        file.open("students.csv", ios::out | ios::app);
        fstream fin;
        fin.open("students.csv", ios::in);
        string line, word, word2, temp;
        {
            getline(fin, line);

            stringstream s(line);

            head = new stu();
            getline(s, word, ',');
            head->roll_no = word;
            getline(s, word, ',');
            head->name = word;
            getline(s, word, ',');
            head->pass = word;

            getline(s, word, ',');
            getline(s, word2, ',');
            if (word.length() > 0 && word2.length() > 0)
            {
                head->issued1 = new issued_book(word, word2);
                head->total_issued++;
            }
            getline(s, word, ',');
            getline(s, word2, ',');
            if (word.length() > 0 && word2.length() > 0)
            {
                head->issued2 = new issued_book(word, word2);
                head->total_issued++;
            }
        }

        curr = head;
        getline(fin, line);
        while (!fin.eof())
        {

            stringstream s(line);
            stu *temp = new stu();
            getline(s, word, ',');
            temp->roll_no = word;
            getline(s, word, ',');
            temp->name = word;
            getline(s, word, ',');
            temp->pass = word;

            getline(s, word, ',');
            getline(s, word2, ',');
            if (word.length() > 0 && word2.length() > 0)
            {
                temp->issued1 = new issued_book(word, word2);
                temp->total_issued++;
            }
            getline(s, word, ',');
            getline(s, word2, ',');
            if (word.length() > 0 && word2.length() > 0)
            {
                temp->issued2 = new issued_book(word, word2);
                temp->total_issued++;
            }

            curr->next = temp;
            curr = temp;
            getline(fin, line);
        }
    }
    stu *login()
    {
        string x, y;
        cout << "Enter roll number" << endl;
        cin >> x;
        cout << "Enter password" << endl;
        cin >> y;
        stu *temp = head;
        while (temp)
        {
            if (temp->roll_no == x && temp->pass == y)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }
    void display(stu *temp)
    {
        int c = 0;
        if (temp->issued1)
        {
            Node *book_d = b.book_detail(temp->issued1->ref_no);
            cout << "Issued Book 1" << endl;
            cout << "Book Name : " << book_d->name << endl;
            cout << "Book Author : " << book_d->author << endl;
            cout << "Issue Date : " << temp->issued1->date_time << endl;
            string s1, s2, s3;
            s1 = temp->issued1->date_time[0];
            s2 = temp->issued1->date_time[1];
            s3 = s1 + s2;
            int x = stoi(s3);
            time_t now = time(0);
            tm *ltm = localtime(&now);
            int day = ltm->tm_mday;
            cout << "Days till issue : " << day - x << endl
                 << endl;
            c++;
        }

        if (temp->issued2)
        {
            Node *book_d = b.book_detail(temp->issued2->ref_no);
            cout << "Issued Book 2" << endl;
            cout << "Book Name : " << book_d->name << endl;
            cout << "Book Author : " << book_d->author << endl;
            cout << "Issue Date : " << temp->issued2->date_time << endl;
            string s1, s2, s3;
            s1 = temp->issued2->date_time[0];
            s2 = temp->issued2->date_time[1];
            s3 = s1 + s2;
            int x = stoi(s3);
            time_t now = time(0);
            tm *ltm = localtime(&now);
            int day = ltm->tm_mday;
            cout << "Days till issue : " << day - x << endl
                 << endl;
            c++;
        }
        if (c == 0)
            cout << "No issued Books" << endl;
        cout << endl;
    }
    void get_book(stu *student)
    {
        Node *book = b.get_information();
        if (book == NULL)
            return;
        cout << "Press 1 to issue the book" << endl;
        cout << "Press 2 to return" << endl;
        int q;
        cin >> q;
        if (q == 1)
        {
            int x = student->issued1 && student->issued2;
            if (x)
            {
                cout << "No more books can be issued" << endl;
                return;
            }
            else
            {
                if (student->issued1 == NULL && book->stock > 0)
                {
                    student->issued1 = new issued_book(book->ref_num, get_time());
                    book->stock--;
                    cout << "Book issued successfully" << endl;
                }
                else if (student->issued2 == NULL && book->stock > 0)
                {
                    student->issued2 = new issued_book(book->ref_num, get_time());
                    book->stock--;
                    cout << "Book issued successfully" << endl;
                }
            }
        }
        else
        {
            return;
        }
    }
    void return_book(stu *student)
    {
        int q;
        cout << "Press 1 to return book 1" << endl;
        cout << "Press 2 to return book 2" << endl;
        cin >> q;
        if (q == 1)
        {
            string s1, s2, s3;
            issued_book *temp = student->issued1;
            s1 = temp->date_time[0];
            s2 = temp->date_time[1];
            s3 = s1 + s2;
            int x = stoi(s3);
            time_t now = time(0);
            tm *ltm = localtime(&now);
            int day = ltm->tm_mday;
            if (day - x > 15)
            {
                cout << "Fine for " << day - x - 15 << " day(s) = Rs." << (day - x - 15) * 10 << endl;
                cout << "Press Enter to pay fine" << endl;
                cin.get();
                cin.get();
            }

            student->issued1 = NULL;
            Node *book = b.book_detail(temp->ref_no);
            book->stock++;
            delete temp;
            cout << "Book returned Succcessfully" << endl;
        }
        if (q == 2)
        {
            string s1, s2, s3;
            issued_book *temp = student->issued2;
            s1 = temp->date_time[0];
            s2 = temp->date_time[1];
            s3 = s1 + s2;
            int x = stoi(s3);
            time_t now = time(0);
            tm *ltm = localtime(&now);
            int day = ltm->tm_mday;
            if (day - x > 15)
            {
                cout << "Fine for " << day - x - 15 << " day(s) = Rs." << (day - x - 15) * 10 << endl;
                cout << "Press Enter to pay fine" << endl;
                cin.get();
                cin.get();
            }

            student->issued2 = NULL;
            Node *book = b.book_detail(temp->ref_no);
            book->stock++;
            delete temp;
            cout << "Book returned Succcessfully" << endl;
        }
    }
    ~Student()
    {
        fstream fout;
        fout.open("students.csv", ios::out);
        stu *temp = head;
        while (temp)
        {
            fout << temp->roll_no << "," << temp->name << "," << temp->pass;
            if (temp->issued1 == NULL)
                fout << ",,";
            else
            {
                fout << "," << temp->issued1->ref_no << "," << temp->issued1->date_time;
            }
            if (temp->issued2 == NULL)
                fout << ",,";
            else
            {
                fout << "," << temp->issued2->ref_no << "," << temp->issued2->date_time;
            }
            fout << endl;

            temp = temp->next;
        }
        fout.close();
    }
};