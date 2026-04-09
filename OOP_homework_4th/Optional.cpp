/*
[Optional] Try again to finish CExpression (with CStack) using only CMyString instead of string
in C++ and char*
*/
#include <iostream>
#include <cstring>
using namespace std;
class CMyString
{
private:
    char *str; // 字符串指针，表示第一个字符的位置
    int size;  // 字符串长度
public:
    CMyString(const char *s = "\0")
    {
        size = 0;
        while (s[size] != '\0')
            size++;
        str = new char[size + 1];
        for (int i = 0; i < size; i++)
            str[i] = s[i];
        str[size] = '\0';
    }

    CMyString(const CMyString &other)
    {
        size = other.size;
        str = new char[size + 1];
        for (int i = 0; i < size; i++)
            str[i] = other.str[i];
        str[size] = '\0';
    }

    ~CMyString()
    {
        delete[] str;
    }

    const char *c_str() const
    {
        return str;
    }

    char &operator[](int index)
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of bounds");
        return str[index]; // 返回指向第index个字符的引用
    }
    const char &operator[](int index) const
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of bounds");
        return str[index];
    }
    friend CMyString operator+(const CMyString &a, const CMyString &b)
    {
        CMyString result;
        delete[] result.str; // 释放默认构造函数分配的内存
        result.size = a.size + b.size;
        result.str = new char[result.size + 1];
        for (int i = 0; i < a.size; i++)
            result.str[i] = a.str[i];
        for (int i = 0; i < b.size; i++)
            result.str[a.size + i] = b.str[i];
        result.str[result.size] = '\0';
        return result;
    }
    CMyString &operator=(const CMyString &other)
    {
        if (this != &other)
        {
            delete[] str;
            size = other.size;
            str = new char[size + 1];
            for (int i = 0; i < size; i++)
                str[i] = other.str[i];
            str[size] = '\0';
        }
        return *this;
    }
    bool operator==(const CMyString &other) const
    {
        if (size != other.size)
            return false;
        for (int i = 0; i < size; i++)
            if (str[i] != other.str[i])
                return false;
        return true;
    }
    friend ostream &operator<<(ostream &os, const CMyString &s)
    {
        os << s.str;
        return os;
    }

    int getSize() const
    {
        return size;
    }

    int Find(char c, int startPos = 0) const
    {
        for (int i = startPos; i < size; i++)
            if (str[i] == c)
                return i;
        return -1;
    }

    int Find(const CMyString &substr) const // kmp
    {
        CMyString tmp = substr + CMyString("#") + *this;
        int n = tmp.size;
        int m = substr.size;
        int *pi = new int[n];
        pi[0] = 0;
        for (int i = 1; i < n; i++)
        {
            int j = pi[i - 1];
            while (j > 0 && tmp[i] != tmp[j])
                j = pi[j - 1];
            if (tmp[i] == tmp[j])
                j++;
            pi[i] = j;
            if (j == m)
            {
                delete[] pi;
                return i - 2 * m; // 返回在原字符串中的位置
            }
        }
        delete[] pi;
        return -1; // 未找到子字符串
    }

    CMyString Mid(int startPos, int len) const
    {
        if (startPos < 0 || startPos >= size || len < 0)
            return CMyString();
        int actualLen = (startPos + len > size) ? (size - startPos) : len;
        char *substr = new char[actualLen + 1];
        for (int i = 0; i < actualLen; i++)
            substr[i] = str[startPos + i];
        substr[actualLen] = '\0';
        CMyString result(substr);
        delete[] substr;
        return result;
    }
};
template <typename T>
class CMyStack
{
private:
    T *m_pTop;       // Top pointer of stack
    int m_iSize;     // Number of actual elements
    int m_iCapacity; // Capacity of stack
public:
    CMyStack(int size);
    ~CMyStack();
    T Pop();
    T Peek();
    bool Push(T item);
    bool isEmpty(); // Is Stack empty?
    bool isFull();  // Is Stack full?
    int GetSize();  // Get number of actual elements
    void Clear();   // Clear stack
};

class CExpression
{
private:
    CMyString expression; // 存储表达式的字符串
public:
    CExpression(const CMyString &str);                                // 构造函数，接受表达式字符串                                             // 析构函数，释放资源
    void SetExpression(const CMyString &expr);                        // 设置新的表达式
    double CharToDouble(const CMyString &str);                        // 字符转双精度浮点数
    double Value();                                                   // Get value of expresstion
    friend ostream &operator<<(ostream &os, const CExpression &expr); // print only expression except its value
};

template <typename T>
CMyStack<T>::CMyStack(int size)
{
    m_iCapacity = size;
    m_iSize = 0;
    m_pTop = new T[m_iCapacity];
}
template <typename T>
CMyStack<T>::~CMyStack()
{
    delete[] m_pTop;
}
template <typename T>
T CMyStack<T>::Pop()
{
    if (!isEmpty())
    {
        return m_pTop[--m_iSize];
    }
    return '\0'; // 返回空字符表示栈空
}
template <typename T>
T CMyStack<T>::Peek()
{
    if (!isEmpty())
    {
        return m_pTop[m_iSize - 1];
    }
    return '\0'; // 返回空字符表示栈空
}
template <typename T>
bool CMyStack<T>::Push(T item)
{
    if (!isFull())
    {
        m_pTop[m_iSize++] = item;
        return true;
    }
    return false; // 栈满无法压入
}
template <typename T>
bool CMyStack<T>::isEmpty()
{
    return m_iSize == 0;
}
template <typename T>
bool CMyStack<T>::isFull()
{
    return m_iSize == m_iCapacity;
}
template <typename T>
int CMyStack<T>::GetSize()
{
    return m_iSize;
}
template <typename T>
void CMyStack<T>::Clear()
{
    m_iSize = 0; // 只需重置大小，实际数据不需要清除
}
CExpression::CExpression(const CMyString &str)
{
    expression = str;
}
void CExpression::SetExpression(const CMyString &expr)
{
    expression = CMyString(expr);
}
double CExpression::CharToDouble(const CMyString &str)
{
    double val = 0.0; // 转换字符串为双精度浮点数
    sscanf(str.c_str(), "%lf", &val);
    return val;
}
double CExpression::Value()
{
    // 表达式求值
    CMyStack<char> operatorStack(100);  // 操作符栈
    CMyStack<double> operandStack(100); // 操作数栈
    for (int i = 0; i < expression.getSize(); i++)
    {
        char c = expression[i];
        if (isdigit(c) || c == '.')
        {
            char buf[64]; // 临时缓冲区存储数字
            int j = 0;
            while (i < expression.getSize() && (isdigit(expression[i]) || expression[i] == '.'))
                buf[j++] = expression[i++];
            buf[j] = '\0';
            operandStack.Push(CharToDouble(buf)); // 将数字压入操作数栈
            i--;                                  // 调整索引，因为外层循环会增加i
        }
        else if (c == '(')
        {
            operatorStack.Push(c); // 左括号直接压栈
        }
        else if (c == ')')
        {
            // 处理右括号，弹出操作符直到遇到左括号
            while (!operatorStack.isEmpty() && operatorStack.Peek() != '(')
            {
                char op = operatorStack.Pop();
                double b = operandStack.Pop();
                double a = operandStack.Pop();
                double res;
                switch (op)
                {
                case '+':
                    res = a + b;
                    break;
                case '-':
                    res = a - b;
                    break;
                case '*':
                    res = a * b;
                    break;
                case '/':
                    res = a / b;
                    break;
                }
                operandStack.Push(res);
            }
            operatorStack.Pop(); // 弹出左括号
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            // 处理操作符，考虑优先级
            while (!operatorStack.isEmpty() && ((c == '+' || c == '-') && (operatorStack.Peek() == '*' || operatorStack.Peek() == '/')) ||
                   ((c == '+' || c == '-') && (operatorStack.Peek() == '+' || operatorStack.Peek() == '-')) ||
                   ((c == '*' || c == '/') && (operatorStack.Peek() == '*' || operatorStack.Peek() == '/')))
            {
                char op = operatorStack.Pop();
                double b = operandStack.Pop();
                double a = operandStack.Pop();
                double res;
                switch (op)
                {
                case '+':
                    res = a + b;
                    break;
                case '-':
                    res = a - b;
                    break;
                case '*':
                    res = a * b;
                    break;
                case '/':
                    res = a / b;
                    break;
                }
                operandStack.Push(res);
            }
            operatorStack.Push(c); // 将操作符压入操作符栈
        }
    }
    while (!operatorStack.isEmpty())
    {
        char op = operatorStack.Pop();
        double b = operandStack.Pop();
        double a = operandStack.Pop();
        double res;
        switch (op)
        {
        case '+':
            res = a + b;
            break;
        case '-':
            res = a - b;
            break;
        case '*':
            res = a * b;
            break;
        case '/':
            res = a / b;
            break;
        }
        operandStack.Push(res);
    }
    return operandStack.Pop(); // 最后操作数栈顶就是表达式的值
}
ostream &operator<<(ostream &os, const CExpression &expr)
{
    os << expr.expression;
    return os;
}
int main()
{
    CExpression expr("50.3-20.12+8*8/2");
    cout << expr << " = " << expr.Value() << endl; // 50.3-20.12+8*8/2 = 62.18
    expr.SetExpression("55.99-88.11+77.12");
    cout << expr << " = " << expr.Value() << endl; // 55.99-88.11+77.12 = 45
    expr.SetExpression("(39+11)*30+10/5");
    cout << expr << " = " << expr.Value() << endl; // (39+11)*30+10/5 = 1502
    expr.SetExpression("39+12*(47+33)");
    cout << expr << " = " << expr.Value() << endl; // 39+12*(47+33) = 999
    expr.SetExpression("20/(112-(10*1.2))/10-1.01");
    cout << expr << " = " << expr.Value() << endl; // 20/(112-(10*1.2))/10-1.01 = -0.99
    expr.SetExpression("20/(112-10*1.2)/10-1.01");
    cout << expr << " = " << expr.Value() << endl; // 20/(112-10*1.2)/10-1.01 = -0.99
    cout << "ENDING..." << endl;
    return 0;
}