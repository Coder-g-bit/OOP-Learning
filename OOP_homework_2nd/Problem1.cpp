#include <iostream>
using namespace std;
class Cset
{
public:
    Cset(int capacity = 100);
    ~Cset();
    bool IsExist(int item) const;
    bool IsEqual(const Cset &other) const;
    Cset Intersection(const Cset &other);
    Cset Union(const Cset &other);
    void RemoveItem(int item);
    void AddItem(int item);
    int GetItem(int position) const;
    void show();
private:
    int *data; // 存储集合元素的动态数组
    int size;  // 当前集合中元素的数量
    int capacity; // 集合的最大容量
};
Cset::Cset(int capacity)
{
    this->capacity = capacity;
    this->size = 0;
    data = new int[capacity];
}
Cset::~Cset()
{
    delete[] data;
}
bool Cset::IsExist(int item) const
{
    for (int i = 0; i < size; i++)
    {
        if (data[i] == item)
        {
            return true;
        }
    }
    return false;
}
bool Cset::IsEqual(const Cset &other) const
{
    if (size != other.size)
    {
        return false;
    }
    for (int i = 0; i < size; i++)
    {
        if (!other.IsExist(data[i]))
        {
            return false;
        }
    }
    return true;
}
Cset Cset::Intersection(const Cset &other)// 交集
{
    Cset result;
    for (int i = 0; i < size; i++)
    {
        if (other.IsExist(data[i]))
        {
            result.AddItem(data[i]);
        }
    }
    return result;
}
Cset Cset::Union(const Cset &other)// 并集
{
    Cset result;
    for (int i = 0; i < size; i++)
    {
        result.AddItem(data[i]);
    }
    for(int i = 0; i < other.size; i++)
    {
        result.AddItem(other.data[i]);
    }
    return result;
}
void Cset::RemoveItem(int item)
{
    for (int i = 0; i < size; i++)
    {
        if (data[i] == item)
        {
            for (int j = i; j < size - 1; j++)
            {
                data[j] = data[j + 1];
            }
            size--;
            return;
        }
    }
}
void Cset::AddItem(int item) // 添加元素并且保证集合中没有重复元素
{
    if (size < capacity && !IsExist(item))
    {
        data[size++] = item;
    }
}
int Cset::GetItem(int position) const// 获取position位置的整数
{
    if (position >= 0 && position < size)
    {
        return data[position];
    }
    else {
        cout<<"Position out of range"<<endl;
        return -1; // 返回-1表示位置越界
    }
}
void Cset::show()// 显示集合元素
{
    cout << "{ ";
    for (int i = 0; i < size; i++)
    {
        cout << data[i] << " ";
    }
    cout << "}" << endl;
}

int main()
{
    Cset set1(5),set2(5);
    for(int i = 0; i < 5; i++)
    {
        set1.AddItem(i);
        set2.AddItem(i+3);
    }
    cout<<set1.IsEqual(set2)<<endl;
    Cset intersectionSet = set1.Intersection(set2);
    Cset unionSet = set1.Union(set2);
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