/*
学校里的学生、教师基本信息包括姓名，性别，出生年月，ID（学生以入学年份开头，教
师以t开头）。根据下面给出的示例性数据，定义相关的类及成员，并完成以下功能：
     1) GetTeacherByCourse( )：学生根据课程名称，查询授课教师;
     2) GetScoreByCourse( )：学生根据课程名称和学号，查询课程成绩；
     3) GetStudInfoBySID( )：教师通过学号SID，查询学生信息（姓名、性别和年龄）；
     4) SetScore2Course( )：教师根据课程ID，给出课程的学生成绩；
     要求：
     1）上述功能的接口定义、所属类自行定义；
     2）下面的示例数据，可以直接在程序中定义；
     3）要求：定义两个及以上的类完成上述功能，同时简要描述类的作用和功能、类间关
系（组合、继承、依赖、实现等），以及你的设计思路。

示例性的数据：

学生姓名    性别     出生年月         SID
 李逵        男       2006.8        20240801
 花千羽      女       2004.10       20221011
 TF-BOY      男       2005.6        20240601
 冷冰冰      女       2005.12       20241217


教师姓名    性别     出生年月        TID
 孙悟空       男      1968.8       t20011211
 张三丰       男      1989.10      t20060708


  课程编号           课程名称              TID
COM002          自然语言理解         t19971211
  COM006        面向对象技术与方法     t20060708
  COM016           大数据处理          t20160708


 学生ID            课程编号       成绩
20240801            COM002        86
20221011            COM006        97
20240601            COM016        90
20241217            COM006        79
*/
#include <bits/stdc++.h>
using namespace std;
class Person
{
public:
    string name;
    string gender;
    string birthDate;
    string id;
};
class Student : public Person
{
private:
    int age;

public:
    Student(string name, string gender, string birthDate, string id)
    {
        this->name = name;
        this->gender = gender;
        this->birthDate = birthDate;
        this->id = id;
        time_t now = time(0);
        tm *ltm = localtime(&now);
        age = ltm->tm_year + 1900 - stoi(birthDate.substr(0, 4)); // 计算年龄
    }
    string getStudentInfo() const
    {
        return "姓名: " + name + ", 性别: " + gender + ", 年龄: " + to_string(age) + "岁";
    }
};
class Teacher : public Person
{
public:
    Teacher(string name, string gender, string birthDate, string id)
    {
        this->name = name;
        this->gender = gender;
        this->birthDate = birthDate;
        this->id = id;
    }
    string getTeacherInfo() const
    {
        return "姓名: " + name + ", 性别: " + gender + ", 出生年月: " + birthDate + ", ID: " + id;
    }
};
class Course
{
private:
    string courseId;
    string courseName;
    string teacherId;
    vector<pair<Student, int>> studentScores; // 存储学生ID和成绩的对应关系
public:
    Course(string courseId, string courseName, string teacherId)
    {
        this->courseId = courseId;
        this->courseName = courseName;
        this->teacherId = teacherId;
    }
    string getCourseId() const
    {
        return courseId;
    }
    string getCourseName() const
    {
        return courseName;
    }
    string getTeacherId() const
    {
        return teacherId;
    }
    void addStudent(Student student)
    {
        studentScores.push_back({student, 0});
    }
    void setScore(string studentId, int score)
    {
        for (auto &pair : studentScores)
        {
            if (pair.first.id == studentId)
            {
                pair.second = score; // 设置对应学生的成绩
                return;
            }
        }
    }
    int getScoreByStudentId(string studentId) const
    {
        for (auto &pair : studentScores)
        {
            if (pair.first.id == studentId)
            {
                return pair.second; // 返回对应学生的成绩
            }
        }
        return -1; // 如果没有找到对应的学生，返回-1表示未找到
    }
};
class searchManagement
{
private:
    vector<Student> students;
    vector<Teacher> teachers;
    vector<Course> courses;

public:
    searchManagement(vector<Student> &students, vector<Teacher> &teachers, vector<Course> &courses)
    {
        this->students = students;
        this->teachers = teachers;
        this->courses = courses;
    }
    void addStudentToCourse(string courseId, Student student)
    {
        for (auto &course : courses)
        {
            if (course.getCourseId() == courseId)
            {
                course.addStudent(student);
                return;
            }
        }
    }
    string getTeacherByCourse(string courseName) const
    {
        for (const auto &course : courses)
        {
            if (course.getCourseName() == courseName)
            {
                string teacherId = course.getTeacherId();
                for (const auto &teacher : teachers)
                {
                    if (teacher.id == teacherId)
                    {
                        return teacher.getTeacherInfo();
                    }
                }
            }
        }
        throw "未找到对应课程的教师信息";
    }
    int getScoreByCourse(string courseName, string studentId) const
    {
        for (const auto &course : courses)
        {
            if (course.getCourseName() == courseName)
            {
                return course.getScoreByStudentId(studentId);
            }
        }
        throw "未找到对应课程的信息";
    }
    string getStudentInfoBySID(string studentId) const
    {
        for (const auto &student : students)
        {
            if (student.id == studentId)
            {
                return student.getStudentInfo();
            }
        }
        throw "未找到对应学生的信息";
    }
    void setScoreToCourse(string courseId, string studentId, int score)
    {
        for (auto &course : courses)
        {
            if (course.getCourseId() == courseId)
            {
                course.setScore(studentId, score);
                return;
            }
        }
        throw "未找到对应课程的信息";
    }
};

int main()
{
    vector<Student> studentList = {
        Student("李逵", "男", "2006.8", "20240801"),
        Student("花千羽", "女", "2004.10", "20221011"),
        Student("TF-BOY", "男", "2005.6", "20240601"),
        Student("冷冰冰", "女", "2005.12", "20241217")};
    vector<Teacher> teacherList = {
        Teacher("孙悟空", "男", "1968.8", "t20011211"),
        Teacher("张三丰", "男", "1989.10", "t20060708")};
    vector<Course> courseList = {
        Course("COM002", "自然语言理解", "t19971211"),
        Course("COM006", "面向对象技术与方法", "t20060708"),
        Course("COM016", "大数据处理", "t20160708")};
    searchManagement manager(studentList, teacherList, courseList);
    manager.addStudentToCourse("COM002", studentList[0]);
    manager.addStudentToCourse("COM006", studentList[1]);
    manager.addStudentToCourse("COM016", studentList[2]);
    manager.addStudentToCourse("COM006", studentList[3]);

    manager.setScoreToCourse("COM002", "20240801", 86);
    manager.setScoreToCourse("COM006", "20221011", 97);
    manager.setScoreToCourse("COM016", "20240601", 90);
    manager.setScoreToCourse("COM006", "20241217", 79);

    try
    {
        cout << manager.getTeacherByCourse("面向对象技术与方法") << endl;
        cout << "学生20240801在自然语言理解课程的成绩: " << manager.getScoreByCourse("自然语言理解", "20240801") << endl;
        manager.setScoreToCourse("COM006", "20221011", 95); // 测试修改成绩的情况
        cout<< "修改后的成绩: " << manager.getScoreByCourse("面向对象技术与方法", "20221011") << endl; // 测试修改成绩后查询成绩的情况
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
    try
    {
        manager.setScoreToCourse("COM999", "20240801", 85); // 测试设置成绩时课程不存在的情况
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
    try
    {
        cout << manager.getScoreByCourse("不存在的课程", "20240801") << endl; // 测试查询成绩时课程不存在的情况
    }
    catch (const char *msg)
    {
        cerr << msg << endl;
    }
    return 0;
}