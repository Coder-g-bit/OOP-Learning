#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
struct Person // 参数：人物姓名，出现次数；重载运算符，按照次数从大到小排序
{
    string name;
    int num;
    bool operator<(Person T) const
    {
        return num > T.num;
    }
};
const string NAME[5] = {"大圣", "玉帝", "王母娘娘", "仙女", "天王"};
int numOfPerson[5] = {0, 0, 0, 0, 0};
void findNumOfPerson(const string t) // 匹配人物姓名与原始文本，统计出现次数
{
    const int len = t.size();
    for (int i = 0; i < len - 1; ++i)
    {
        if (t[i] == '大' && t[i + 1] == '圣')
        {
            numOfPerson[0]++;
        }
        else if (t[i] == '玉' && t[i + 1] == '帝')
        {
            numOfPerson[1]++;
        }
        else if (t[i] == '仙' && t[i + 1] == '女')
        {
            numOfPerson[3]++;
        }
        else if (t[i] == '天' && t[i + 1] == '王')
        {
            numOfPerson[4]++;
        }
    }
    for (int i = 0; i < len - 3; ++i)
    {
        if (t[i] == '王' && t[i + 1] == '母' && t[i + 2] == '娘' && t[i + 3] == '娘')
        {
            numOfPerson[2]++;
        }
    }
}
int main()
{
    ifstream inputFile("JourneyToWest.txt");
    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            findNumOfPerson(line);
        }
        Person tmp[5] = {};
        for (int i = 0; i < 5; ++i)
        {
            tmp[i] = {NAME[i], numOfPerson[i]};
        }
        sort(tmp, tmp + 5);
        cout << "VIP are: " << NAME[0] << " and " << NAME[1] << '\n';
        cout << "因为他们在文本中出现次数最多\n";
        inputFile.close();
    }
    else
    {
        cout << "Unable to open the file for reading.\n";
    }
    return 0;
}
