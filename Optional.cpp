//  Define a class of CLoopSet which holds data with linear structure and connects
// the last node to the first node, and reimplement all of the member functions in the CSet
// above.
//  Note:
//  (1) You may define compatible parameters as well as other members you need.
//  (2) Templates in STL(Standard Template Library) of C++ are FORBIDDEN
#include <iostream>
using namespace std;
class CLoopSet
{
    class Node
    {
    public:
        int data;
        Node *next;
        Node(int value) : data(value), next(nullptr) {}
    };

public:
    CLoopSet(int capacity = 100);
    ~CLoopSet();
    bool IsExist(int item) const;
    bool IsEqual(const CLoopSet &other) const;
    CLoopSet Intersection(const CLoopSet &other);
    CLoopSet Union(const CLoopSet &other);
    void RemoveItem(int item);
    void AddItem(int item);
    int GetItem(int position) const;
    void show();

private:
    Node *head;   // 存储集合元素的动态数组
    int size;     // 当前集合中元素的数量
    int capacity; // 集合的最大容量
};
CLoopSet::CLoopSet(int capacity)
{
    this->capacity = capacity;
    this->size = 0;
    head = nullptr;
}
CLoopSet::~CLoopSet()
{
    if (head != nullptr)
    {
        Node *current = head;
        for (int i = 0; i < size; i++)
        {
            Node *temp = current;
            current = current->next;
            delete temp;
        }
    }
}
bool CLoopSet::IsExist(int item) const
{
    Node *current = head;
    for (int i = 0; i < size; i++, current = current->next)
    {
        if (current->data == item)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}
bool CLoopSet::IsEqual(const CLoopSet &other) const
{
    if (size != other.size)
    {
        return false;
    }
    Node *current = head;
    for (int i = 0; i < size; i++, current = current->next)
    {
        if (!other.IsExist(current->data))
        {
            return false;
        }
        current = current->next;
    }
    return true;
}
CLoopSet CLoopSet::Intersection(const CLoopSet &other) // 交集
{
    CLoopSet result;
    Node *current = head;
    for (int i = 0; i < size; i++, current = current->next)
    {
        if (other.IsExist(current->data))
        {
            result.AddItem(current->data);
        }
        current = current->next;
    }
    return result;
}
CLoopSet CLoopSet::Union(const CLoopSet &other) // 并集
{
    CLoopSet result;
    Node *current = head;
    for (int i = 0; i < size; i++, current = current->next)
    {
        result.AddItem(current->data);
        current = current->next;
    }
    current = other.head;
    for (int i = 0; i < other.size; i++, current = current->next)
    {
        result.AddItem(current->data);
    }
    return result;
}
void CLoopSet::RemoveItem(int item)
{
    if (head == nullptr)
        return; // 空集合
    Node *current = head;
    Node *prev = head;
    for (int i = 0; i < size; i++, current = current->next)
    {
        if (current->data == item)
        {
            prev->next = current->next;
            delete current;
            size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}
void CLoopSet::AddItem(int item)
{
    if (size < capacity && !IsExist(item))
    {
        Node *newNode = new Node(item);
        if (head == nullptr)
        {
            head = newNode;
            head->next = head; // 形成循环
        }
        else
        {
            Node *current = head;
            while (current->next != head)
            {
                current = current->next;
            }
            current->next = newNode;
            newNode->next = head; // 形成循环
        }
        size++;
    }
}
int CLoopSet::GetItem(int position) const // 获取position位置的整数
{
    if (position >= 0 && position < size)
    {
        Node *current = head;
        for (int i = 0; i < position; i++)
        {
            current = current->next;
        }
        return current->data;
    }
    else
    {
        cout << "Position out of range" << endl;
        return -1; // 返回-1表示位置越界
    }
}
void CLoopSet::show() // 显示集合元素
{
    cout << "{ ";
    Node *current = head;
    for (int i = 0; i < size; i++)
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << "}" << endl;
}

int main()
{
    CLoopSet set1(50), set2(50);
    for (int i = 0; i < 5; i++)
    {
        set1.AddItem(i);
        set2.AddItem(i + 3);
    }
    cout << set1.IsEqual(set2) << endl;
    CLoopSet intersectionSet = set1.Intersection(set2);
    CLoopSet unionSet = set1.Union(set2);
    cout << "Set 1: ";
    set1.show();
    cout << "Set 2: ";
    set2.show();
    cout << "Intersection: ";
    intersectionSet.show();
    cout << "Union: ";
    unionSet.show();
    return 0;
}