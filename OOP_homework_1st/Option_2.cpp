#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
void DrawTriangle(int n); // n is rows of trangle
void DrawSqure(int n);   // n is rows of squre
class CCircle
{
public:
    CCircle(int R = 0, int X = 0, int Y = 0) : radius(R), posX(X), posY(Y)
    {
        index = 0;
        if (radius < 0)
        {
            radius = 0;
            cout << "The radius must bigger then zero\n";
        }
    }
    string Relationship(CCircle ACirlce) const //根据圆心距离判断位置关系
    {
        if (distance(ACirlce) > radius + ACirlce.radius)
            return "seperated";
        else if (distance(ACirlce) == radius + ACirlce.radius)
            return "circumscribed";
        else if (distance(ACirlce) < radius + ACirlce.radius && distance(ACirlce) > abs(radius - ACirlce.radius))
            return "overlapped";
        else if (distance(ACirlce) == abs(radius - ACirlce.radius))
            return "inscribed,";
        else if(distance(ACirlce) < abs(radius - ACirlce.radius) && distance(ACirlce) > 0)
            return "contained";
        else if(distance(ACirlce) == 0)
            return "coincide";
        else
            return "error";
    }
    double distance(const CCircle &ACirlce) const
    {
        return sqrt((posX - ACirlce.posX) * (posX - ACirlce.posX) + (posY - ACirlce.posY) * (posY - ACirlce.posY));
    }
    void Exit(void f(int), int n) //退出时记录函数和参数
    {
        isReleased = true;
        if(f==DrawTriangle){
            functionCalled[index++] = true;
        }
        else if(f==DrawSqure){
            functionCalled[index++] = false;
        }
        else{
            cout<<"Invalid function pointer\n";
            return;
        }
        parameter[index-1] = n;
    }
    ~CCircle() // 析构时按顺序调用记录的函数
    {
        if(isReleased){
            for(int i=0;i<index;++i){
                if(functionCalled[i]){
                    DrawTriangle(parameter[i]);
                }
                else{
                    DrawSqure(parameter[i]);
                }
            }
            isReleased = false;
        }
    }

private:
    double radius, posX, posY;
    static bool isReleased;
    bool functionCalled[10];
    static int parameter[10];
    static int index;
};

int CCircle::parameter[10];
int CCircle::index = 0;
bool CCircle::isReleased = false;

void DrawTriangle(int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
            putchar(' ');
        for (int j = 0; j < 2 * i + 1; ++j)
            putchar('*');
        putchar('\n');
    }
    putchar('\n');
    putchar('\n');
}
void DrawSqure(int n)
{
    for (int i = 0; i < n; ++i)
    {
        putchar('*');
    }
    putchar('\n');
    for (int i = 0; i < n - 2; ++i)
    {
        putchar('*');
        for (int j = 0; j < n - 2; ++j)
            putchar(' ');
        putchar('*');
        putchar('\n');
    }
    for (int i = 0; i < n; ++i)
    {
        putchar('*');
    }
    putchar('\n');
    putchar('\n');
}
int main()
{
    CCircle c1(3);       // 3 is radius
    CCircle c2(2, 4, 3); // 2 is radius, 4 is x-coordinate， 3 is y-coordiante.
    c1.Exit(DrawTriangle, 4);
    c2.Exit(DrawSqure, 5);
    cout << "The relationship is " << c1.Relationship(c2) << endl<< endl;
    return 0;
}
