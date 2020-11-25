#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

struct Node
{
    string ref_num;
    string name;
    int stock;
    string author;
    Node *next;
    Node()
    {
        next = NULL;
    }
};
class Book
{
    Node *head;
    Node *curr;

public:
    Book()
    {
        head = NULL;
        fstream fin;
        fin.open("books.csv", ios::in);
        string line, word, temp;
        {
            getline(fin, line);

            stringstream s(line);

            head = new Node();
            getline(s, word, ',');
            head->ref_num = word;
            getline(s, word, ',');
            head->name = word;
            getline(s, word, ',');
            head->stock = stoi(word);
            getline(s, word, ',');
            head->author = word;
        }

        curr = head;
        getline(fin, line);
        while (!fin.eof())
        {

            stringstream s(line);
            Node *temp = new Node();
            getline(s, word, ',');
            temp->ref_num = word;
            getline(s, word, ',');
            temp->name = word;
            getline(s, word, ',');
            temp->stock = stoi(word);
            getline(s, word, ',');
            temp->author = word;
            curr->next = temp;
            curr = temp;
            getline(fin, line);
        }
        fin.close();
    }

    Node *get_information()
    {
        string b, a;
        cout << "Enter Book name" << endl;
        cin >> b;
        cout << "Enter author" << endl;
        cin >> a;
        Node *temp = head;
        while (temp)
        {
            if (temp->name == b)
            {
                cout << "Book Name : " << temp->name << endl;
                cout << "Book Author : " << temp->author << endl;
                cout << "Book Stock : " << temp->stock << endl
                     << endl;
                if (temp->stock == 0)
                {
                    cout << "Sorry , Book not in stock" << endl;
                    return NULL;
                }
                return temp;
            }
            temp = temp->next;
        }
        cout << "Sorry , Book not found" << endl;
        return NULL;
    }
    Node *book_detail(string ref)
    {
        Node *temp = head;
        while (temp)
        {
            if (temp->ref_num == ref)
                return temp;
            temp = temp->next;
        }
        return NULL;
    }
    ~Book()
    {
        fstream fout;
        fout.open("books.csv", ios::out);
        Node *temp = head;
        while (temp)
        {
            fout << temp->ref_num << "," << temp->name << "," << temp->stock << "," << temp->author << endl;
            temp = temp->next;
        }
    }
};