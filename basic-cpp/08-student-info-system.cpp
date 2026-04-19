// 结构体 : https://www.yuque.com/lianlianfengchen-cvvh2/zack/rg6gy6gnhihummqh

// Project : 简单学生信息管理系统
// 这个项目结合struct的知识点，创建一个简单的学生信息管理系统，允许添加、显示和查找学生信息。

// 需求分析
/* 
● 添加新学生的信息（ID、姓名、成绩）
● 显示所有学生的信息
● 根据学生ID查找学生信息
*/


#include<iostream>
#include<string>
#include<vector>

using namespace std;

struct Student {
    string ID;
    string name;
    double grade;
};

void print_all_info(vector<Student *> students)
{
    for (Student * stu : students)
    {
        cout << stu->ID << '\t' << stu->name << '\t' << stu->grade << endl;
    }
}

void clear_stu_info(vector<Student *> students)
{
    for (Student * stu : students)
    {
        delete stu;
    }
}

int main()
{
    vector<Student *> students;
    char command;

    cout << "================== 学生管理系统已启动!!! ==================="  << endl;
    while(true)
    {
        cout << "请输入(i:插入学生信息, p:显示所有学生信息, f:查找学生信息, e:退出系统):";
        cin >> command;
        
        if (command == 'i')
        {
            Student* stu = new Student;
            cout << "请输入学生ID: "; cin >> stu->ID;
            cout << "请输入学生姓名: "; cin >> stu->name;
            cout << "请输入学生成绩: "; cin >> stu->grade;
            students.push_back(stu);
            cout << "新增学生信息完成" << endl;
        }
        else if (command == 'p')
        {
            print_all_info(students);
        }
        else if (command == 'f')
        {
            cout << "请输入学生学号或姓名: ";
            string in;
            bool flag = false;
            cin >> in;
            for (Student * stu : students)
            {
                if (in == stu->ID || in == stu->name)
                {
                    flag = true;
                    cout << stu->ID << '\t' << stu->name << '\t' << stu->grade << endl;
                }
            }
            if (!flag)  cout << "没有找到该学生信息" << endl;

        }
        else if (command == 'e')
        {
            cout << "================== 学生管理系统已退出!!! ==================="  << endl;
            clear_stu_info(students);
            break;
        }
        else
        {
            cout << "此功能正在开发中..." << endl;
        }
    }

    return 0;
}
