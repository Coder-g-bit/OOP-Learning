#include <iostream>
using namespace std;

class Stash
{
public:
    Stash(int sz, int initQuantity = 0) : size(sz), quantity(initQuantity), next(0), storage(nullptr) {}
    ~Stash()
    {
        delete[] storage;
    }

    void initialize(int size)
    {
        this->size = size;
        quantity = 0;
        next = 0;
        storage = nullptr;
    }

    void Contract() //释放所有存储空间，清空容器
    {
        delete[] storage;
        storage = nullptr;
        quantity = 0;
        next = 0;
    }

    void Remove(int pos) // 删除第 pos 个元素（pos 为元素偏移量）
    {
        if (pos < 0 || pos >= next)
        {
            cout << "Invalid position\n";
            return;
        }

        for (int i = pos; i < next - 1; ++i)
        {
            for (int j = 0; j < size; ++j)
            {
                storage[i * size + j] = storage[(i + 1) * size + j];
            }
        }
        next--;
    }

    int add(const void *element)
    {
        if (quantity == 0 || next >= quantity)
        {
            inflate(100);
        }

        int startBytes = next * size;
        const unsigned char *e = (const unsigned char *)element;

        for (int i = 0; i < size; ++i)
        {
            storage[startBytes + i] = e[i];
        }

        next++;
        return next - 1;
    }

    void *fetch(int index)
    {
        if (index < 0 || index >= next)
        {
            return nullptr;
        }
        return &storage[index * size];
    }

    int count()
    {
        return next;
    }

    void inflate(int increase)// 扩展容量 increase 个元素空间
    {
        unsigned char *newStorage = new unsigned char[size * (quantity + increase)];

        if (storage)
        {
            for (int i = 0; i < size * next; ++i)
            {
                newStorage[i] = storage[i];
            }
        }

        delete[] storage;
        storage = newStorage;
        quantity += increase;
    }

private:
    int size;               
    int quantity;          
    int next;               
    unsigned char *storage; 
};

int main()
{
    Stash stash(sizeof(int));

    // 添加元素
    for (int i = 0; i < 5; ++i)
    {
        stash.add(&i);
    }

    cout << "Original elements:\n";
    for (int i = 0; i < stash.count(); ++i)
    {
        cout << *(int *)stash.fetch(i) << " ";
    }
    cout << endl;

    // 删除第2个元素
    stash.Remove(2);

    cout << "After Remove(2):\n";
    for (int i = 0; i < stash.count(); ++i)
    {
        cout << *(int *)stash.fetch(i) << " ";
    }
    cout << endl;

    // 释放空间
    stash.Contract();

    cout << "count = " << stash.count() << endl;

    return 0;
}