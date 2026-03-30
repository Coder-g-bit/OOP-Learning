#include <iostream>
#include <ctime>
using namespace std;
class CDateTime
{
public:
    static CDateTime Now();
    void ShowTime12();
    void ShowTime24();
    void ShowDate();

private:
    int year, month, day, hour, minute, second;
};
CDateTime CDateTime::Now() // 获取当前日期和时间
{
    CDateTime dt;
    time_t t = time(0);
    tm *now = localtime(&t);
    dt.year = now->tm_year + 1900;
    dt.month = now->tm_mon + 1;
    dt.day = now->tm_mday;
    dt.hour = now->tm_hour;
    dt.minute = now->tm_min;
    dt.second = now->tm_sec;
    return dt;
}
void CDateTime::ShowTime12() // 以 am 或 pm 形式显示当前时间，例如下午：3:30:12 pm
{
    int displayHour = hour % 12;
    if (displayHour == 0)
        displayHour = 12; // 12小时制中0点和12点显示为12
    cout << displayHour << ":"
         << (minute < 10 ? "0" : "") << minute << ":"
         << (second < 10 ? "0" : "") << second
         << (hour < 12 ? " am" : " pm") << endl;
}
void CDateTime::ShowTime24() // 以 24 小时形式显示当前时间，例如下午：22:11:12 pm
{
    cout << (hour < 10 ? "0" : "") << hour << ":"
         << (minute < 10 ? "0" : "") << minute << ":"
         << (second < 10 ? "0" : "") << second
         << (hour < 12 ? " am" : " pm") << endl;
}
void CDateTime::ShowDate() // 显示当前日期和星期，例如：2025 年 3 月 19 日，星期三
{
    const char *daysOfWeek[] = {"星期日", "星期一", "星期二", "星期三", "星期四", "星期五", "星期六"};
    time_t t = time(0);
    tm *now = localtime(&t);
    int wday = now->tm_wday; // 获取当前是星期几
    cout << year << " 年 " << month << " 月 " << day << " 日，" << daysOfWeek[wday] << endl;
}
int main()
{
    CDateTime dt = CDateTime::Now();
    dt.ShowTime12(); // 以 am 或 pm 形式显示当前时间，例如下午：3:30:12 pm
    dt.ShowTime24(); // 以 24 小时形式显示当前时间，例如下午：22:11:12 pm
    dt.ShowDate();   // 显示当前日期和星期，例如：2025 年 3 月 19 日，星期三
    return 0;
}
