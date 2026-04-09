/*
2. Define CInternetURL class to save a URL string like as "bit.edu.cn"，and finish the demands
as follows:
 2.1 Only use CMyString you just finished before to save URL string；
 2.2 Define member function getDomain() to get domain from URL.
 For example, we can get "bit.edu.cn" from "https://jwc.bit.edu.cn/index.htm"；
 2.3 Define member function getDomainCountry() to get country name in the domain
from URL, such as "us", "uk", etc.
 For example, we can get "cn" from "https://jwc.bit.edu.cn/index.htm"；
 2.4 Define member function getDomainType() to get domain type from URL, such as
"gov", "com", "org", and so on.
 For example, we can get "edu" from "https://jwc.bit.edu.cn/index.htm"；
 2.5 Define member function getHomePage() to get home page from URL, such as
"index.htm", "default.htm", and so on.
 For example, we can get "index" from "https://jwc.bit.edu.cn/index.htm"；
 2.6 The string you CAN ONLY use is CMyString in the main:
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

    char &operator[](int index)
    {
        if (index < 0 || index >= size)
            throw std::out_of_range("Index out of bounds");
        return str[index]; // 返回指向第index个字符的引用
    }
    friend CMyString operator+(const CMyString &a, const CMyString &b)
    {
        CMyString result;
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

class CInternetURL
{
private:
    CMyString url; // 保存URL字符串
public:
    CInternetURL(const CMyString &s) : url(s) {} // 构造函数，初始化URL

    CMyString GetDomain() const
    {
        int start = url.Find('.');
        if (start == -1)
            return CMyString();
        int end = url.Find('/', start);
        if (end == -1)
            end = url.getSize(); // 如果没有路径，域名到字符串末尾
        return url.Mid(start + 1, end - start - 1);
    }

    CMyString GetDomainCountry() const
    {
        CMyString domain = GetDomain();
        int next_dot = domain.Find('.');           // 从第一个点开始找
        next_dot = domain.Find('.', next_dot + 1); // 下一个点
        if (next_dot == -1)
            return CMyString();
        return domain.Mid(next_dot + 1, domain.getSize() - next_dot - 1);
    }

    CMyString GetDomainType() const
    {
        CMyString domain = GetDomain();
        int first_dot = domain.Find('.');
        int next_dot = domain.Find('.', first_dot + 1);
        if (first_dot == -1 || next_dot == -1)
            return CMyString();
        return domain.Mid(first_dot + 1, next_dot - first_dot - 1);
    }

    CMyString GetHomePage() const
    {
        int pure_url_end = url.Find("://");
        if (pure_url_end == -1)
            pure_url_end = 0;
        else
            pure_url_end += 3; // 跳过 "://"
        int first_slash = url.Find('/', pure_url_end);
        int next_slash = url.Find('/', first_slash + 1);
        if (first_slash == -1)
            return CMyString();
        if (next_slash != -1)
            return url.Mid(first_slash + 1, next_slash - first_slash - 1);
        else
            return url.Mid(first_slash + 1, url.getSize() - first_slash - 1);
    }
};

int main()
{
    CInternetURL URL("https://jwc.bit.edu.cn/index.htm");

    cout << URL.GetDomain() << endl;        // The result is: bit.edu.cn
    cout << URL.GetDomainCountry() << endl; // The result is: cn
    cout << URL.GetDomainType() << endl;    // The result is: edu
    cout << URL.GetHomePage() << endl;      // The result is: index.htm
    return 0;
}
