/*
Create a class, CMyStack, to save double elements and implement the operations on the
stack
Note: Don't modify any member variables and interface of member function in CMyStack
*/
#include <iostream>
using namespace std;
class CMyStack
{
private:
    char *m_pTop;    // Top pointer of stack
    int m_iSize;     // Number of actual elements
    int m_iCapacity; // Capacity of stack
public:
    CMyStack(int size);
    ~CMyStack();
    char Pop();
    char Peek();
    bool Push(char ch);
    bool isEmpty(); // Is Stack empty?
    bool isFull();  // Is Stack full?
    int GetSize();  // Get number of actual elements
    void Clear();   // Clear stack
};
CMyStack::CMyStack(int size)
{
    m_iCapacity = size;
    m_iSize = 0;
    m_pTop = new char[m_iCapacity];
}
CMyStack::~CMyStack()
{
    delete[] m_pTop;
}
char CMyStack::Pop()
{
    if (!isEmpty())
    {
        return m_pTop[--m_iSize];
    }
    return '\0'; // 返回空字符表示栈空
}
char CMyStack::Peek()
{
    if (!isEmpty())
    {
        return m_pTop[m_iSize - 1];
    }
    return '\0'; // 返回空字符表示栈空
}
bool CMyStack::Push(char ch)
{
    if (!isFull())
    {
        m_pTop[m_iSize++] = ch;
        return true;
    }
    return false; // 栈满无法压入
}
bool CMyStack::isEmpty()
{
    return m_iSize == 0;
}
bool CMyStack::isFull()
{
    return m_iSize == m_iCapacity;
}
int CMyStack::GetSize()
{
    return m_iSize;
}
void CMyStack::Clear()
{
    m_iSize = 0; // 只需重置大小，实际数据不需要清除
}
int main()
{
    CMyStack stack(5); // 创建容量为5的栈
    stack.Push('A');
    stack.Push('B');
    stack.Push('C');
    cout << "栈顶元素: " << stack.Peek() << endl; //
    cout << "栈大小: " << stack.GetSize() << endl;
    cout << "弹出元素: " << stack.Pop() << endl;
    cout << "栈顶元素: " << stack.Peek() << endl;
    cout << "栈大小: " << stack.GetSize() << endl;
    stack.Clear();
    cout << "清空栈后栈大小: " << stack.GetSize() << endl;
    return 0;
}