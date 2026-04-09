#include <iostream>
#include <algorithm>
using namespace std;
class CDate
{
public:
    CDate(int Y = 0, int M = 0, int D = 0) : year(Y), month(M), day(D)
    {
        if (!isValid())
        {
            year = month = day = 0;
            cout << "该日期不存在\n";
        }
    }
    int spanDays(CDate Aday) const // 计算两个日期的跨度
    {
        return abs(countDaysFromOrigin() - Aday.countDaysFromOrigin());
    }
    int countDaysFromOrigin() const // 计算从 0001-1-1 起的天数
    {
        int y = year, m = month, d = day;
        if (m < 3)
            y--, m += 12;
        return 365 * y + (y >> 2) - y / 100 + y / 400 + (153 * m - 457) / 5 + d - 306;
    }

    bool isValid() const // 判断该日期是否合法
    {
        int y = year, m = month, d = day;
        if (m < 1 || m > 12 || d < 1)
            return false;
        int mdays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (m == 2 && isLeap())
            return d <= 29;
        return d <= mdays[m];
    }

    bool isLeap() const // 判断该年是否是闰年
    {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    void printDate() const // 打印日期
    {
        cout << year << '-' << month << '-' << day << '\n';
    }

private:
    int year, month, day;
};
int main()
{
    CDate date1(2026, 1, 3), date2(2026, 3, 19);
    int spanDays = date2.spanDays(date1);
    cout << spanDays << '\n';
    date1.printDate();
    return 0;
}
