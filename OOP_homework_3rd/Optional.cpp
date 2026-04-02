/*
Create a class, CLINT, to save a big positive integer which is no more than 100
digits.
NOTES: You can define appropriate member functions and variables.
*/
#include <iostream>
#include <cstring>
using namespace std;
class CLINT
{
private:
    int digits[105]; // 存储大整数的每一位，digits[0]为最低位
    int length;      // 大整数的位数
public:
    CLINT() : length(0) {}
    CLINT(const char *numStr);                               // 构造函数，接受字符串形式的大整数
    CLINT operator+(const CLINT &L);                         // Achieve the sum of two big numbers
    CLINT operator=(const CLINT &L);                         // 赋值运算符重载
    friend ostream &operator<<(ostream &os, const CLINT &L); // Output big number
};
CLINT::CLINT(const char *numStr)
{
    length = strlen(numStr);
    for (int i = 0; i < length; i++)
    {
        digits[i] = numStr[length - 1 - i] - '0'; // 将字符串转换为整数数组，反向存储
    }
}
CLINT CLINT::operator+(const CLINT &L)
{
    CLINT result;
    int carry = 0;
    int maxLength = max(length, L.length);
    for (int i = 0; i < maxLength || carry; i++)
    {
        int sum = carry;
        if (i < length)
            sum += digits[i];
        if (i < L.length)
            sum += L.digits[i];
        result.digits[result.length++] = sum % 10; // 存储当前位的结果
        carry = sum / 10;                            // 计算进位
    }
    return result;
}
CLINT CLINT::operator=(const CLINT &L)
{
    if (this != &L) // 防止自赋值
    {
        length = L.length;
        for (int i = 0; i < length; i++)
        {
            digits[i] = L.digits[i];
        }
    }
    return *this;
}
ostream &operator<<(ostream &os, const CLINT &L)
{
    for (int i = L.length - 1; i >= 0; i--)
    {
        os << L.digits[i]; // 从最高位开始输出
    }
    return os;
}

int main()
{
    CLINT L1("12345678900987654321"), L2("9876543210"), L3;
    L3 = L1 + L2;
    cout << L3 << endl; // 12345678910864197531
    return 0;
}