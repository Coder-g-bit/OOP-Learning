/*
3. 用迭代器实现for语句对CMyString的使用。
要求：
1）基于上次实验中自己定义的CMyString类；
2）定义CMyString类的迭代器Iterator，并实现其构造函数、重载++、-- 为前缀及后缀运算
符，以及重载运算符 != 和 *；
3）为了使得 for 语句能成功运行，至少在 CMyString 类中定义与迭代器有关的成员函数：
begin()，end()；
4）所定义的CMyString类，使得 main 函数能正确运行
*/
#include <iostream>
using namespace std;
class CMyString
{
private:
    char *str; // 字符串指针，表示第一个字符的位置
    int size;  // 字符串长度
    class Iterator
    {
    private:
        char *ptr;
    public:
        Iterator(CMyString& p, bool isend = false){
            ptr = isend ? p.str + p.size : p.str;
        }
        Iterator operator++(int){
            Iterator temp = *this;
            ptr++;
            return temp;
        }
        Iterator operator++(){
            ptr++;
            return *this;
        }
        Iterator operator--(int){
            Iterator temp = *this;
            ptr--;
            return temp;
        }
        Iterator operator--(){
            ptr--;
            return *this;
        }
        char &operator*(){
            return *ptr;
        }
        bool operator!=(const Iterator &other) const{
            return ptr != other.ptr;
        }
    };

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

    Iterator begin() {
        return Iterator(*this);
    }

    Iterator end() {
        return Iterator(*this, true);
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
    CMyString str("I Love BIT");
    cout << "Use iterator to print a string with FOR statement." << endl;
    for (char ch : str)
        cout << ch << ' ';
    cout << endl;
    return 0;
}