// Define a class of CSmart which can print how many objects of CSmart there are in the
// program, and explain the results of the procedure.
//  NOTE: Don't modify any codes EXCEPT CSmart class.
#include <iostream>
using namespace std;
class CSmart
{
public:
    CSmart()
    {
        count++;
        ShowCount();
    }
    ~CSmart()
    {
        if (!isDestroyed) // 确保析构函数只执行一次
        {
            isDestroyed = true;
            count--;
            ShowCount();
        }
    }
    static void ShowCount()
    {
        cout << count << " object" << (count < 2 ? "" : "s") << endl;
    }

private:
    static int count; // 静态成员变量，记录对象数量
    bool isDestroyed = false; // 标记对象是否已被销毁
};

// 初始化静态成员变量
int CSmart::count = 0;

void DoSomething()
{
    CSmart s;
}
CSmart s1;
int main()
{
    CSmart s2;
    DoSomething();
    CSmart *s3 = new CSmart;
    delete s3;
    s2.~CSmart();
    return 0;
}
