#include "admin.h"
// #define DEBUG

Admin * admin;

Admin::Admin(/* args */)
{
    this->name = "null";
    this->course_size = 0;
    this->courses = NULL;
    this->student_size = 0;
    this->students = NULL;
}

Admin::~Admin()
{
    if(this->courses != NULL)
    {
        delete [] this->courses;
        this->courses = NULL;
        this->course_size = 0;
    }
    if(this->students != NULL)
    {
        delete [] this->students;
        this->students = NULL;
        this->student_size = 0;
    }
}

Admin::Admin(string name)
{
    this->name = name;
    int all_count;
    prepocess p;
    courses = p.coursesInitialize(all_count);
    this->course_size = all_count;
    ifstream in("../database/Administer.data");
    int student_count;
    in >> student_count;
    if (student_count)
        students = new Student[student_count];
    this->student_size = student_count;
    for(int i = 0; i < student_count; i++)
    {
        string stuname;
        in >> stuname;
        clog << "��ȡѧ��" << stuname << "�γ�\n";
        Student s(stuname);
        students[i].setName(stuname);
        students[i].setCourseSize(s.getCourseSize());
        students[i].setCourses(s.getCourses(), s.getCourseSize());
    }
    in.close();
}

int Admin::getCourse_size()
{
    return this->course_size;
}

void Admin::setCourse_size(int course_size)
{
    this->course_size = course_size;
}

course * Admin::getCourses()
{
    return this->courses;
}

void Admin::setCourses(course * courses)
{
    if(this->courses != NULL)
    {
        delete [] this->courses;
        this->courses = NULL;
    }
    this->courses = new course[course_size];
    for (int i = 0; i < course_size; i++) {
        this->courses[i] = courses[i];
    }
}

void Admin::addCourse()
{
    
    //done
    course * newArray = new course[getCourse_size() + 1];
    for (int i = 0; i < getCourse_size() - 1; i++)
    {
        newArray[i] = courses[i];
    }
    cout << "������γ����ƣ�";
    string courseName = Input<string>();
    newArray[getCourse_size() - 1].setName(courseName);
    cout << "������ÿ�ܿγ̴�����";
    newArray[getCourse_size() - 1].setTimeSize(Input<int>());
    course_time * newTime = new course_time[newArray[getCourse_size() - 1].getTimeSize()];
    for (int i = 0; i < newArray[getCourse_size() - 1].getTimeSize(); i++)
    {
        cout << "�������" << i + 1 << "�ογ����ܼ��ϿΣ�(����1-7)";
        newTime[i].week = Input<int>() - 1;
        cout << "�������" << i + 1 << "�ογ̵Ŀ�ʼʱ�䣺";
        newTime[i].starthour = Input<int>();
        cout << "�������" << i + 1 << "�ογ̵Ľ���ʱ�䣺";
        newTime[i].endhour = Input<int>();
        for(int j = 0; j < course_size; j++)
        {
            for(int k = 0; k < courses[j].getTimeSize(); k++)
            {
                if(newTime[i].week == courses[j].getTime()[k].week && 
                (newTime[i].starthour >= courses[j].getTime()[k].starthour && newTime[i].starthour < courses[j].getTime()[k].endhour) ||
                (newTime[i].endhour > courses[j].getTime()[k].starthour && newTime[i].endhour <= courses[j].getTime()[k].endhour))
                {
                    cout << "�γ�ʱ���ͻ������������\n";
                    i--;
                    return;
                }
            }
        }
    }
    newArray[getCourse_size() - 1].setTime(newTime, newArray[getCourse_size() - 1].getTimeSize());
    cout << "������γ̵ص㣺";
    newArray[getCourse_size() - 1].setAddress(Input<string>());
    cout << "�����뵱ǰ�γ̽��ȣ�";
    newArray[getCourse_size() - 1].setCurrent(Input<string>());
    string * newDocuments = NULL;
    newArray[getCourse_size() - 1].setDocuments(newDocuments, 0);
    cout << "������γ�QQȺ:";
    newArray[getCourse_size() - 1].setQQGroup(Input<string>());
    Time t;
    t.yr = 0; t.mn = 0; t.day = 0; t.hr = 0;
    cout << "�����뿼��ʱ��(��ʽ��:21010820)" << endl;
    int exam_time = Input<int>();
    t.inputTime(exam_time);
    newArray[getCourse_size() - 1].setExtime(t);
    cout << "�����뿼�Եص㣺";
    newArray[getCourse_size() - 1].setExaddress(Input<string>());
    newArray[getCourse_size() - 1].setHomeWork(newDocuments, 0);
    string stuname;
    //����ѧ������
    do
    {
        cout << "�������Ͽ�ѧ������,����0����:";
        stuname = Input<string>();
        fstream in("../database/users.data");
        string name, temp;
        bool flag = false;
        while(in >> name >> temp)
        {
            if(!OurStr::StrCmp(stuname, name))
            {
                flag = true;
                break;
            }
        }
        in.close();
        if(flag)
        {
            string cmd = "mkdir ..\\documents\\users\\" + stuname + "\\" + newArray[getCourse_size() - 1].getName();
            system(cmd.c_str());
            for(int i = 0; i < student_size; i++)
            {
                if(!OurStr::StrCmp(students[i].getName(), stuname))
                {
                    students[i].setCourseSize(students[i].getCourseSize() + 1);
                    course * newCourse = new course[students[i].getCourseSize()];
                    for(int j = 0; j < students[i].getCourseSize() - 1; j++)
                    {
                        newCourse[j] = students[i].getCourses()[j];
                    }
                    newCourse[students[i].getCourseSize() - 1] = newArray[getCourse_size() - 1];
                    students[i].setCourses(newCourse, students[i].getCourseSize());
                    delete [] newCourse;
                }
            }
        }
        else
        {
            cout << "û���ҵ���ѧ��!" << endl;
        }
    }while(stuname != "" && stuname != "0");
    cout << "��ӳɹ���" << endl;
    string cmd = "mkdir ..\\documents\\public\\" + courseName;
    system(cmd.c_str());
    delete[] newTime;
    delete[] newDocuments;
    setCourse_size(getCourse_size() + 1);
    setCourses(newArray);
    delete[] newArray;
}

/**
 * @brief �ϴ��γ�����
 * 
 * @param road �ϴ�·��
 */
string Admin::uploadDocument()
{
    string road, course_name;
    cout << "������Ҫ�ϴ�������·��(�㼶Ŀ¼���ԡ�\\���ָ�)��";
    road = Input<string>();
    cout << "������γ����ƣ�";
    course_name = Input<string>();
    Student s;
    course c = s.searchCourse(courses, course_size, course_name);
    if(c.getName() == "null")
    {
        cout << "û���ҵ��ÿγ̣�" << endl;
        return "null";
    }
    for(int i = 0; i < c.getDocumentsSize(); i++)
    {
        if(!OurStr::StrCmp(c.getDocuments()[i], OurStr::getFilename(road)))
        {
            cout << "�������Ѵ��ڣ�" << endl;
            return "null";
        }
    }
    if(OurStr::getSuffix(road) == "txt")
    {
        string outRoad = "..\\documents\\public\\" + course_name + "\\" + OurStr::getFilename(road).substr(0, OurStr::getFilename(road).length() - 4);
        compression com;
        cout << "����ѹ���ļ�..." << endl;
        if(com.Code(road, outRoad))
        {
            cout << "ѹ���ϴ��ɹ�" << endl;
        }
        else
        {
            cout << "ѹ���ϴ�ʧ��" << endl;
        }
    }
    else
    {
        cout << "��⵽����txt�ļ�,ȡ��ѹ��" << endl;
        string cmd = "copy " + road + " ..\\documents\\public\\" + course_name;
        system(cmd.c_str());
    }
    for(int i = 0; i < course_size; i++)
    {
        if(!OurStr::StrCmp(courses[i].getName(), course_name))
        {
            string * newDocuments = new string[courses[i].getDocumentsSize() + 1];
            for(int j = 0; j < courses[i].getDocumentsSize(); j++)
            {
                newDocuments[j] = courses[i].getDocuments()[j];
            }
            newDocuments[courses[i].getDocumentsSize()] = OurStr::getFilename(road);
            courses[i].setDocuments(newDocuments, courses[i].getDocumentsSize() + 1);
            delete [] newDocuments;
        }
    }
    return OurStr::getFilename(road);
}

void Admin::addHomework()
{
    string Course_name,Homework;
    cout << "������γ����ƣ�";
    Course_name = Input<string>();
    Student s;
    course c = s.searchCourse(courses, course_size, Course_name);
    if(c.getName() == "null")
    {
        cout << "û���ҵ��ÿγ�!" << endl;
        return;
    }
    cout << "��������ҵ���ƣ�";
    Homework = Input<string>();
    bool flag = false;
    for(int j = 0; j < c.getHomeWorkSize(); j++)
    {
        if(!OurStr::StrCmp(Homework, c.getHomeWork()[j]))
        {
            flag = true;
            break;
        }
    }
    if(flag)
    {
        cout << "����ҵ�Ѵ���!" << endl;
        return;
    }
    for(int i = 0; i < course_size; i++)
    {
        if(!OurStr::StrCmp(courses[i].getName(), Course_name))
        {
            courses[i].setHomeWorkSize(courses[i].getHomeWorkSize() + 1);
            string * newHomework = new string[courses[i].getHomeWorkSize()];
            for(int j = 0; j < courses[i].getHomeWorkSize() - 1; j++)
            {
                newHomework[j] = courses[i].getHomeWork()[j];
            }
            newHomework[courses[i].getHomeWorkSize() - 1] = Homework;
            courses[i].setHomeWork(newHomework, courses[i].getHomeWorkSize());
            delete [] newHomework;
            break;
        }
    }
    for(int i = 0; i < student_size; i++)
    {
        course c;
        c = students[i].searchCourse(students[i].getCourses(), students[i].getCourseSize(), Course_name);
        #ifdef DEBUG
        for(int j = 0; j < students[i].getCourseSize(); j++)
        {
            if(!OurStr::StrCmp(students[i].getCourses()[j].getName(), Course_name))
            {
                for(int k = 0; k < students[i].getCourses()[j].getTimeSize(); k++)
                {
                    cout << students[i].getCourses()[j].getTime()[k].week << endl;
                }
            }
        }
        #endif
        if(c.getName() != "null")
        {
            c.setHomeWorkSize(c.getHomeWorkSize() + 1);
            string * newArray = new string[c.getHomeWorkSize()];
            for(int j = 0; j < c.getHomeWorkSize() - 1; j++)
            {
                newArray[j] = c.getHomeWork()[j];
            }
            newArray[c.getHomeWorkSize() - 1] = Homework;
            c.setHomeWork(newArray, c.getHomeWorkSize());
            delete[] newArray;
            string cmd = "mkdir ..\\documents\\users\\" + students[i].getName() + "\\" + Course_name + "\\" + to_string(c.getHomeWorkSize());
            system(cmd.c_str());
            c.setFinishSize(c.getFinishSize() + 1);
            hw_con * newArray2 = new hw_con[c.getFinishSize()];
            for(int j = 0; j < c.getFinishSize() - 1; j++)
            {
                newArray2[j].finish = c.getFinish()[j].finish;
                if(c.getFinish()[j].finish)
                {
                    newArray2[j].road = c.getFinish()[j].road;
                    newArray2[j].MD5 = c.getFinish()[j].MD5;
                }
            }
            newArray2[c.getFinishSize() - 1].finish = false;
            c.setFinish(newArray2, c.getFinishSize());
            delete[] newArray2;
            for(int j = 0; j < students[i].getCourseSize(); j++)
            {
                if(!OurStr::StrCmp(students[i].getCourses()[j].getName(), Course_name))
                {
                    students[i].getCourses()[j] = c;
                    break;
                }
            }
        }
    }
    cout << "��ӳɹ���" << endl;
}

void Admin::showMenu()
{
    updateTime();
    printf("��ӭ����Ա%s\n", name.c_str());
    printf("1.�鿴���пγ�\n");
    printf("2.�鿴����ѧ��\n");
    printf("3.��ӿγ�\n");
    printf("4.�����ҵ\n");
    printf("5.�鿴�γ�����\n");
    printf("6.�ϴ��γ�����\n");
    printf("0.�˳�����Աϵͳ\n");
    printf("����������ѡ��");
    int choice = input::getOperatorNum();
    while(choice)
    {
        switch(choice)
        {
            case 1:
                cout << "���пγ̣�" << endl;
                for(int i = 0; i < course_size; i++)
                {
                    printf("%s\t", courses[i].getName().c_str());
                }
                cout << endl;
                break;
            case 2:
                cout << "����ѧ����" << endl;
                for(int i = 0; i < student_size; i++)
                {
                    printf("%s\t", students[i].getName().c_str());
                }
                cout << endl;
                break;
            case 3:
                addCourse();
                break;
            case 4:
                addHomework();
                break;
            case 5:
                showDocument();
                break;
            case 6:
                uploadDocument();
                break;
            case 0:
                return;
            default:
                printf("����������������룡\n");
                break;
        }
        printf("��ӭ����Ա%s\n", name.c_str());
        printf("1.�鿴���пγ�\n");
        printf("2.�鿴����ѧ��\n");
        printf("3.��ӿγ�\n");
        printf("4.�����ҵ\n");
        printf("5.�鿴�γ�����\n");
        printf("6.�ϴ��γ�����\n");
        printf("0.�˳�����Աϵͳ\n");
        printf("����������ѡ��");
        choice = input::getOperatorNum();
    }
}

void Admin::showDocument()
{
    string Course_name;
    cout << "������γ����ƣ�";
    Course_name = Input<string>();
    Student s;
    course c = s.searchCourse(courses, course_size, Course_name);
    if(c.getName() == "null")
    {
        cout << "û���ҵ��ÿγ�!" << endl;
        return;
    }
    cout << "�γ��������£�" << endl;
    for(int i = 0; i < c.getDocumentsSize(); i++)
    {
        printf("%s\t", c.getDocuments()[i].c_str());
    }
}

void Admin::saveAdminInfo()
{
    saveCourseInfo();
    for(int i = 0; i < student_size; i++)
    {
        students[i].saveStuInfo();
    }
    cout << "����Ա��Ϣ������ɣ�" << endl;
}

void Admin::saveCourseInfo()
{
    ofstream out("../database/course.data");
    out << course_size << endl;
    for(int i = 0; i < course_size; i++)
    {
        out << courses[i].getName() << endl;
        out << courses[i].getTimeSize() << endl;
        for(int j = 0; j < courses[i].getTimeSize(); j++)
        {
            out << courses[i].getTime()[j].week << " " << courses[i].getTime()[j].starthour << " " << courses[i].getTime()[j].endhour << endl;
        }
        out << courses[i].getAddress() << endl;
        out << courses[i].getDocumentsSize() << ' ';
        for(int j = 0; j < courses[i].getDocumentsSize(); j++)
        {
            out << courses[i].getDocuments()[j] << ' ';
        }
        out << endl;
        out << courses[i].getCurrent() << endl;
        out << courses[i].getHomeWorkSize() << endl;
        for(int j = 0; j < courses[i].getHomeWorkSize(); j++)
        {
            out << courses[i].getHomeWork()[j] << ' ';
        }
        out << endl;
        out << courses[i].getQQGroup() << endl;
        out << courses[i].getExtime().yr << ' ' << courses[i].getExtime().mn << ' ' << courses[i].getExtime().day << ' ' << courses[i].getExtime().hr << endl;
        out << courses[i].getExaddress() << endl;
    }
    out.close();
}