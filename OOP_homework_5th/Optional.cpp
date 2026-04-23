/*
[operation] 在数据库操作中，对SQL语句的查询构造，一般采用如下类似的方式：
int main( )
{
CMyString userName, password;
cin >> userName >> password;
CMyString sql = "select * from DB where userName=" + username + "and password =" + password;
return 0;
}
这种方法存在一个缺陷，即容易造成SQL语句的注入错误：如果输入useName为 "user"，
输入password为"abc || 1 == 1"，则 where 字句中的密码查询结果都将是true。
为了防止出现类似SQL语句的注入错误，在ODBC或JDBC等的数据库连接与查询过程
中，SQL语句的构成一般采用以下方法来构造：

在 main 函数中，出现“？”的地方，都默认有一个整数编号依次相对应。成员函数
SetAttribute 通过编号一一对应赋值，并最终构造完整的SQL语句。
请按照上述main函数中对象sql调用各成员函数的形式，来定义CSqlStatement类。在
实际应用中，成员函数ExecuteSql的功能是执行sql语句。但作为课堂实验，改为输出所构
造的整个SQL语句。
注意：
1. 字符串类型只能使用自己定义的CMyString类，不能使用 C/C++ 提供的字符串类及库函
数。
2. 请将CMyString 类直接放在程序文件中，不要单独提交CMyString类的文件。
*/
#include <bits/stdc++.h>
using namespace std;

class CMyString
{
private:
    char *str;
    int size;

public:
    class Iterator
    {
    private:
        char *ptr;

    public:
        Iterator(CMyString &p, bool isend = false)
        {
            ptr = isend ? p.str + p.size : p.str;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ptr++;
            return temp;
        }

        Iterator operator++()
        {
            ptr++;
            return *this;
        }

        char &operator*()
        {
            return *ptr;
        }

        bool operator!=(const Iterator &other) const
        {
            return ptr != other.ptr;
        }
    };

    CMyString(const char *s = "")
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

    char &operator[](int index)
    {
        return str[index];
    }

    const char &operator[](int index) const
    {
        return str[index];
    }

    int getSize() const
    {
        return size;
    }

    const char *c_str() const
    {
        return str;
    }

    friend CMyString operator+(const CMyString &a, const CMyString &b)
    {
        char *tmp = new char[a.size + b.size + 1];
        for (int i = 0; i < a.size; i++)
            tmp[i] = a.str[i];
        for (int i = 0; i < b.size; i++)
            tmp[a.size + i] = b.str[i];
        tmp[a.size + b.size] = '\0';

        CMyString res(tmp);
        delete[] tmp;
        return res;
    }

    friend ostream &operator<<(ostream &os, const CMyString &s)
    {
        os << s.str;
        return os;
    }

    int Find(char c, int startPos = 0) const
    {
        for (int i = startPos; i < size; i++)
            if (str[i] == c)
                return i;
        return -1;
    }

    CMyString Mid(int startPos, int len) const
    {
        if (startPos < 0 || startPos >= size || len <= 0)
            return CMyString("");

        int actualLen = (startPos + len > size) ? (size - startPos) : len;
        char *tmp = new char[actualLen + 1];
        for (int i = 0; i < actualLen; i++)
            tmp[i] = str[startPos + i];
        tmp[actualLen] = '\0';

        CMyString res(tmp);
        delete[] tmp;
        return res;
    }
};

class CSqlStatement
{
private:
    CMyString sqlTemplate;
    CMyString attributes[105];
    bool used[105];

    int ToInt(const CMyString &s) const
    {
        int n = s.getSize();
        if (n == 0)
            return -1;
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] < '0' || s[i] > '9')
                return -1;
            ans = ans * 10 + (s[i] - '0');
        }
        return ans;
    }

    bool IsSafeValue(const CMyString &value) const
    {
        for (int i = 0; i < value.getSize(); i++)
        {
            char ch = value[i];
            if (ch == ' ' || ch == '|' || ch == '&' || ch == '=' ||
                ch == '\'' || ch == '"' || ch == ';')
                return false;
        }
        return true;
    }

public:
    CSqlStatement(const CMyString &sql = "") : sqlTemplate(sql)
    {
        for (int i = 0; i < 105; i++)
            used[i] = false;
    }

    CSqlStatement(const char *sql) : sqlTemplate(sql)
    {
        for (int i = 0; i < 105; i++)
            used[i] = false;
    }

    CSqlStatement &operator=(const CMyString &other)
    {
        sqlTemplate = other;
        return *this;
    }

    const char *GetSqlTemplate() const
    {
        return sqlTemplate.c_str();
    }

    void SetAttribute(const CMyString &index, const CMyString &value)
    {
        int idx = ToInt(index);
        if (idx <= 0 || idx >= 105 || !IsSafeValue(value))
            throw "Errors in setting attribution";

        attributes[idx] = value;
        used[idx] = true;
    }

    void ExecuteSql()
    {
        CMyString finalSql = sqlTemplate;
        int pos = finalSql.Find('?');
        int idx = 1;

        while (pos != -1)
        {
            if (!used[idx])
                throw "Errors in setting attribution";

            CMyString left = finalSql.Mid(0, pos);
            CMyString right = finalSql.Mid(pos + 1, finalSql.getSize() - pos - 1);
            finalSql = left + attributes[idx] + right;

            idx++;
            pos = finalSql.Find('?');
        }

        cout << finalSql << endl;
    }
};
int main()
{
    CSqlStatement sql = "select ?, ? from student where SID = ?"; // 假定：这条 sql 语句没有错误
    sql.SetAttribute("1", "Name");
    sql.SetAttribute("2", "Age");
    sql.SetAttribute("3", "2020007"); // 如果：sql.SetAttribute("3",  "abc || 2023 == 2023");
    // 这时，成员函数应抛出异常：Errors in setting attribution
    try{
        sql.SetAttribute("3",  "abc || 2023 == 2023");
    }
    catch (const char *e)
    {
        cout << e << endl;
    }
    sql.ExecuteSql();
    return 0;
}