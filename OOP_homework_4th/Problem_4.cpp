/*
4. 教室（Classroom）里有多套桌椅（SetDC，sets of desks and chairs），黑板（Blacboard）
和多媒体设备（Multimedia）。给出定义及实现，在体现面向对象类间关系的同时，满足如下
main 函数的调用：
*/
#include <iostream>
using namespace std;
class SetDC
{
protected:
    int num_pairs; // 桌椅套数
public:
    SetDC(int pairs = 0) : num_pairs(pairs) {}
    int getNumPairs() const
    {
        return num_pairs;
    }
};
class Blackboard
{
private:
    int num_blackboards; // 黑板数量
public:
    Blackboard(int blackboards = 0) : num_blackboards(blackboards) {}
    int getNumBlackboards() const
    {
        return num_blackboards;
    }
};
class Multimedia
{
private:
    int num_multimedia; // 多媒体设备数量
public:
    Multimedia(int multimedia = 0) : num_multimedia(multimedia) {}
    int getNumMultimedia() const
    {
        return num_multimedia;
    }
};
class CClassroom
{
private:
    SetDC setdc;           // 桌椅
    Blackboard blackboard; // 黑板
    Multimedia multimedia; // 多媒体设备
public:
    CClassroom(int num_pairs = 0, int num_blackboards = 0, int num_multimedia = 0)
    {
        setdc = SetDC(num_pairs);
        blackboard = Blackboard(num_blackboards);
        multimedia = Multimedia(num_multimedia);
    }
    CClassroom &operator=(const CClassroom &other)
    {
        if (this != &other)
        {
            setdc = other.setdc;
            blackboard = other.blackboard;
            multimedia = other.multimedia;
        }
        return *this;
    }
    friend ostream &operator<<(ostream &os, const CClassroom &c)
    {
        os << "Desks - Chairs : " << c.setdc.getNumPairs()
           << " Blackboard : " << c.blackboard.getNumBlackboards()
           << " Multimedia : " << c.multimedia.getNumMultimedia();
        return os;
    }
};

int main()
{
    CClassroom C601(90, 2, 1); // 三个参数分别表示：
    // SetDC、Blackboard 和 Mutimedia 的数量
    CClassroom C602;
    C602 = C601; // 设置教室 C602 的设施与教室 C601 相同
    cout << C602 << endl;
    return 0;
}
/*
输出：
Desks - Chairs : 90 Blackboard : 2 Multimedia : 1
*/
