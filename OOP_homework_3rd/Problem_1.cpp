/*
Create a class CSingleton(单例模型) to realize that only one object can be defined in the
client program.
Give your codes and describe your thought.
*/
#include <iostream>
using namespace std;
class CSingleton
{
private:
    static CSingleton *instance; // 静态成员变量，指向唯一实例
    CSingleton()                 // 私有构造函数，防止外部创建对象
    {
        cout << "Singleton instance constructed" << endl;
    }

public:
    // 获取唯一实例的静态方法
    static CSingleton getInstance()
    {
        if (instance == nullptr) // 如果实例不存在，创建一个新的实例
        {
            instance = new CSingleton();
        }
        return *instance; // 返回唯一实例的指针
    }
};
CSingleton *CSingleton::instance = nullptr;
int main()
{
    CSingleton s1 = CSingleton::getInstance(); // 获取唯一实例
    CSingleton s2 = CSingleton::getInstance(); // 再次获取唯一实例
    return 0;
}