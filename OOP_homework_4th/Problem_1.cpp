/*
1. Define CMyString class with demands as follows:
 1.1 The class, CMyString, can save any string which means an arbitary length;
 1.2 Overload appropriate operators to operate instance of CMyString in the main;
 1.3 Define Find( ) member function to locate the first position of searching a character or a string;
 1.4 Define Mid( ) member function to get substring from one string;
 1.5 Define type operator and other member functions if you need.
 1.6 Define any member functions if you need.
 1.6 The client can use CMyString you defined like as in the main:
NOTE: The type such as string or template in C++, and string library functions in C
and C++ are both FORBIDDEN in your program. The types you can use is only building type, such as char, int, double, bool and correspondding pointer
*/
#include <iostream>
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
int main()
{
    CMyString s1("BIT"), s2;
    s2 = "love";
    s2[0] = 'L';
    cout << "I " + s2 + " " << s1 << endl; // The output is: I Love BIT
    int pos = s1.Find('T');                // pos is 2, or -1 if 'T' is not found.
    pos = s1.Find("IT");                   // pos is 1, or -1 if "IT" is not found.
    int startPos = 3, len = 4;
    s2 = "Welcome";
    // In Mid, startPos represents starting position, len represents the length of substring.
    CMyString myStr = s2.Mid(startPos, len); // myStr is "come"
    cout << s2 << endl
         << myStr << endl;
    return 0;
}