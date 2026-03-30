#include <iostream>
#include <cstring>
using namespace std;
class CIntChar
{
public:
    CIntChar(const char*);
    void ASC_Print();
    void Binary_Print();
    void Int_Print();
    char At(int position);
    const char* str();
private:
    int data; // 用一个整数来存储字符串
};
CIntChar::CIntChar(const char* str)
{
    if(strlen(str) > 4)
    {
        cout << "String length exceeds 4 characters." << endl;
    }
    else
    {
        data = 0; // 初始化为0
        for(int i = 0; i < strlen(str); i++)
        {
            data |= (str[i] << (8 * (3 - i))); // 将字符按位存储在整数中
        }
    }
}
void CIntChar::ASC_Print()
{
    for(int i = 0; i < 4; i++)
    {
        char c = (data >> (8 * (3 - i))) & 255; // 从整数中提取字符
        cout << c; // 从整数中提取字符
    }
    cout << endl;
}
void CIntChar::Binary_Print()
{
    for(int i = 0; i < 4; i++)
    {
        char c = (data >> (8 * (3 - i))) & 255; // 从整数中提取字符
        for(int j = 7; j >= 0; j--)
        {
            cout << ((c >> j) & 1); // 打印字符的二进制表示
            if (j == 4) cout << " "; // 每4位添加一个空格
        }
        cout << " ";
    }
    cout << endl;
}
void CIntChar::Int_Print() // 打印整数表示
{
    cout << data << endl;
}
char CIntChar::At(int position) // 获取指定位置的字符
{
    if(position >= 0 && position < 4)
    {
        return (data >> (8 * (4 - position))) & 255; // 从整数中提取字符
    }
    else
    {
        cout << "Position out of range." << endl;
        return '\0'; // 返回空字符
    }
}
const char* CIntChar::str() // 获取字符串表示
{
    static char str[5]; // 存储字符串，最后一个字符为'\0'
    for(int i = 0; i < 4; i++)
    {
        str[i] = (data >> (8 * (3 - i))) & 255; // 从整数中提取字符
    }
    str[4] = '\0'; // 添加字符串结束符
    return str;
}
int main()
{
    CIntChar IC("Love");
    IC.ASC_Print();           // Print the content with string format: Love
    IC.Binary_Print();        // Print the content with binary format: 0100 1100 0110
                              // 1111 0111 0110 0110 0101
    IC.Int_Print();           // Print the content with integer format: 1282373221
    cout << IC.At(3) << endl; // Get the fourth chararacter in the integer: 'v'
    cout << IC.str() << endl; // Get the string: "Love"
}