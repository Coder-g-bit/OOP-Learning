/*
3. 银 行 个 人 账 户 （ CCount ） 分 为 贷 记 卡 账 户 （ CCreditAccount ） 和 借 记 卡 账 户
（CDebitAccount），保存有账号、密码、余额等信息。贷记卡账户资金通过个人信用额度进
行消费、取现、还款等功能。借记卡账户资金的使用通过入账、消费、取现等操作来完成。
请利用面向对象继承机制反映上述内容，并满足 main()的调用。
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
class CCount
{
private:
    int account_number; // 账号
    CMyString password; // 密码
protected:
    double balance; // 余额
public:
    CCount(int acc_num, const CMyString &pwd, double bal) : account_number(acc_num), password(pwd), balance(bal) {}
    virtual void Withdraw(double amount) = 0; // 取现
    virtual void Spending(double amount) = 0; // 消费
    friend ostream &operator<<(ostream &os, const CCount &acc)
    {
        os << "账户余额：" << acc.balance;
        return os;
    }
};
class CCreditAccount : public CCount
{
public:
    CCreditAccount(int acc_num, const CMyString &pwd, double bal) : CCount(acc_num, pwd, bal) {}
    void Withdraw(double amount) override
    {
        balance -= amount; // 直接扣除金额，允许透支
    }
    void Spending(double amount) override
    {
        balance -= amount; // 直接扣除金额，允许透支
    }
    void Repay(double amount)
    {
        balance += amount; // 还款，增加余额
    }
};
class CDebitAccount : public CCount
{
public:
    CDebitAccount(int acc_num, const CMyString &pwd, double bal) : CCount(acc_num, pwd, bal) {}
    void Withdraw(double amount) override
    {
        double fee = max(2.0, amount * 0.01); // 取现费率：1%，最低 2 元 / 笔
        if (balance < amount + fee)
        {
            cout << "余额不足，无法取现" << endl;
            return;
        }
        balance -= (amount + fee); // 扣除金额和手续费
    }
    void Spending(double amount) override
    {
        if (balance < amount)
        {
            cout << "余额不足，无法消费" << endl;
            return;
        }
        balance -= amount; // 直接扣除金额，不允许透支
    }
};
int main()
{
    CCreditAccount credit(1061, "123456", 500); // 贷记卡：账号、密码（字符串）、透支额度
    CDebitAccount debit(9032, "654321", 3000);  // 借记卡：账号、密码（字符串）、余额
    credit.Withdraw(200);                       // 取现
    cout << credit << endl;                     // 账户余额：300
    debit.Withdraw(200);                        // 取现，费率：1%，最低 2 元 / 笔
    debit.Spending(200);                        // 消费
    cout << debit << endl;                      // 账户余额：2598
    return 0;
}