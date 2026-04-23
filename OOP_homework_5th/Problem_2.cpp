/*
Define the class template CList:
2.1 CList has member functions such as Add and Remove;
2.2 You may define corresponding members of CList;
2.3 You CAN'T use STL(Standard Template Library) in C++.

  Here is a class, CStudent:
2.4 CStudent has two member variables:  name, age;
2.5 Define other member functions if you need.

  So they can be used as follows in main( ):



Output is :  Equal.
*/
#include <bits/stdc++.h>
using namespace std;
class CStudent
{
private:
    string name;
    int age;
public:
    CStudent(string n = "", int a = 0) : name(n), age(a) {}
    string getName() const { return name; }
    int getAge() const { return age; }
    bool operator==(const CStudent &other) const
    {
        return age == other.age;
    }
};
template <typename T, int size>
class CList
{
private:
    T* items;
    int capacity = size;
    int idx = 0;
public:
    CList(int cap = size)
    {
        items = new T[cap];
    }
    ~CList()
    {
        delete[] items;
    }
    void Add(const T &item)
    {
        if (idx < capacity)
        {
            items[idx++] = item;
        }
        else
        {
            cout << "List is full!" << endl;
        }
    }
    void Remove(int index)
    {
        if (index >= 0 && index < idx)
        {
            for (int i = index; i < idx - 1; ++i)
            {
                items[i] = items[i + 1];
            }
            --idx;
        }
        else
        {
            cout << "Invalid index!" << endl;
        }
    }
    T &operator[](int index)
    {
        if (index >= 0 && index < idx)
        {
            return items[index];
        }
        else
        {
            throw out_of_range("Index out of range");
        }
    }
    const T &operator[](int index) const
    {
        if (index >= 0 && index < idx)
        {
            return items[index];
        }
        else
        {
            throw out_of_range("Index out of range");
        }
    }
};
int main()
{
    CStudent s1("Joan", 22), s2("John", 19), s3("Joe", 22);
    CList<CStudent, 50> listStudent; // 50 is capcity of List
    listStudent.Add(s1);
    listStudent.Add(s2);
    listStudent.Add(s3);
    listStudent.Remove(1);                // 1 is the 2rd element index of listStudent
    if (listStudent[0] == listStudent[1]) // If two students have same age.
        cout << "Equal." << endl;
    else
        cout << "Not equal." << endl;
    return 0;
}