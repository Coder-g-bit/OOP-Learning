/*
Create a class, CMyStack, to save double elements and implement the operations on the
stack
Note: Don't modify any member variables and interface of member function in CMyStack

Create a class , CExpression to calculate the value of an expression which consists of
numbers and operators,
such as + - * / and ( )
NOTE
 3.1 You can define appropriate member functions and variables.
 3.2 You MUST use CMyStack you have finished to complete the program together.
 3.3 Assume that an expression you input is always correct, that is , there is no grammatical
errors
*/
#include <iostream>
#include <cstring>
using namespace std;
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
    char *expression; // 存储表达式的字符串

public:
    CExpression(const char *expr);                                    // 构造函数，接受表达式字符串
    ~CExpression();                                                   // 析构函数，释放资源
    void SetExpression(const char *expr);                             // 设置新的表达式
    double CharToDouble(const char *str);                             // 字符转双精度浮点数
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

CExpression::CExpression(const char *expr)
{
    expression = new char[strlen(expr) + 1];
    strcpy(expression, expr);
}
CExpression::~CExpression()
{
    delete[] expression;
}
void CExpression::SetExpression(const char *expr)
{
    delete[] expression; // 释放旧的表达式内存
    expression = new char[strlen(expr) + 1];
    strcpy(expression, expr);
}
double CExpression::CharToDouble(const char *str)
{
    double val = 0.0; // 转换字符串为双精度浮点数
    sscanf(str, "%lf", &val);
    return val;
}
double CExpression::Value()
{
    // 表达式求值
    CMyStack<char> operatorStack(100);  // 操作符栈
    CMyStack<double> operandStack(100); // 操作数栈
    char *p = expression;
    while (*p)
    {
        if (isdigit(*p) || *p == '.') // 处理数字
        {
            char numStr[20];
            int idx = 0;
            while (isdigit(*p) || *p == '.')
            {
                numStr[idx++] = *p;
                p++;
            }
            numStr[idx] = '\0';
            operandStack.Push(CharToDouble(numStr)); // 将数字压入操作数栈
        }
        else if (*p == '(') // 左括号直接压栈
        {
            operatorStack.Push(*p);
            p++;
        }
        else if (*p == ')') // 右括号，弹出操作符直到遇到左括号
        {
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
            p++;
        }
        else if (*p == '+' || *p == '-' || *p == '*' || *p == '/') // 操作符
        {
            while (!operatorStack.isEmpty() &&
                   ((operatorStack.Peek() == '*' || operatorStack.Peek() == '/') ||
                    ((*p == '+' || *p == '-') && (operatorStack.Peek() == '+' || operatorStack.Peek() == '-'))))
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
            operatorStack.Push(*p); // 当前操作符压栈
            p++;
        }
        else
            p++;
    }
    // 处理剩余操作符
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
    return operandStack.Pop(); // 最终结果在操作数栈顶
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