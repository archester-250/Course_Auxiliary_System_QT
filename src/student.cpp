
#include <cassert>
#include "hashMap.h"
#include "activity.h"
#include "student.h"
#include "course.h"
#include "utils.h"
#include "prepocess.h"
#include "input.h"

using namespace std;

extern void updateTime();

extern HashMap<string, Student> students;
Student *student;

string Student::getName() {
    return name;
}

void Student::setName(string name) {
    this->name = name;
}
/* return true if conflict */
bool time_conflict(int timestamp){
    if (timestamp < 20000000){
        cout << "ʱ���ʽ����" << endl;
        return true;
    }
    int len = student->getActivityArray()->getSize();
    Time tmp;
    tmp.inputTime(timestamp);
    for (int i = 0; i < student->getCourseSize(); i++){
        course cse = student->getCourses()[i];
        if (tmp.calculateWeekDay() == cse.getTime()->week &&\
            tmp.hr >= cse.getTime()->starthour && \
            tmp.hr < cse.getTime()->endhour) {
            cout << "ʱ����γ�" << cse.getName() << "��ͻ" << endl;
            return true;
        }
    }
    for (int i = 0; i < len; i++){
        Activity activity = student->getActivityArray()->get(i);
        if (timestamp >= activity.getStartTime().timeStamp() && \
            timestamp < activity.getEndTime().timeStamp()) {
            cout << "ʱ����" << activity.toString() << "��ͻ" << endl;
            return true;
        }
    }
    return false;
}

void Student::addActivity() {
    Activity activity;
    Time startTime, endTime;
    int clk = 0;
    int inTime;
    cout << "���뿪ʼʱ����ַ�����ʽ(�磺22040715)" << endl;
    do {
        inTime = Input<int>();
    } while (time_conflict(inTime));
    startTime.inputTime(inTime);
    cout << "�������ʱ����ַ�����ʽ(�磺22040718)" << endl;
    do {
        endTime.inputTime(Input<int>());
    } while (endTime.timeStamp() < inTime);
    cout << "������ַ" << endl;
    string address = Input<string>();
    cout << "������Լ���Ļ��Ա��" << endl;
    int memberCnt;
    do {
        memberCnt = Input<int>();
    } while (memberCnt >= 0);
    activity.setMemberCnt(memberCnt);
    while (memberCnt--) {
        cout << "��ӳ�Ա��";
        string member = Input<string>();
        activity.getMembers()->push(member);
    }
    cout << "��������" << endl;
    string description = Input<string>();
    cout << "��ǰ����Сʱ��������ȫ���Ա(����-1������)" << endl;
    clk = Input<int>();
    activity.setStartTime(startTime);
    activity.setEndTime(endTime);
    activity.setAddress(address);
    activity.setDescription(description);
    activity.setClk(clk);
    if (clk >= 0) {
        Time time = startTime.desc(clk);
        if (student->getClocks()->get(time.timeStamp())->first) {
            student->getClocks()->get(time.timeStamp())->second.addEvent(activity.toString());
        } else {
            Clock clock;
            clock.setTimestamp(time.timeStamp());
            clock.addEvent(activity.toString());
            student->getClocks()->put(time.timeStamp(), clock);
        }
    }
    clog << student->name << "����¼���" << activity.toString() << endl;
    ofstream _config("../database/activities/" + student->name, ios::app);
    assert(_config);
    _config << activity.storeStr() << endl;
    _config.close();
    for (int i = 0; i < activity.getMemberCnt(); i++) {
        _config.open("../database/activities/" + activity.getMembers()->get(i), ios::app);
        assert(_config);
        _config << activity.storeStr() << endl;
        _config.close();
    }
    Activities->push(activity);
}

course Student::searchCourse(course c[], int size, string name) {
    course temp;
    for (int i = 0; i < size; i++) {
        if (!OurStr::StrCmp(c[i].getName(), name)) {
            temp = c[i];
            return temp;
        }
    }
    return temp;
}

course *Student::getCourses() {
    return this->courses;
}

void Student::setCourses(course *courses, int c_count) {
    if(this->courses) {
        delete[] this->courses;
        this->courses = NULL;
        course_size = 0;
    }
    this->courses = new course[c_count];
    this->course_size = c_count;
    for (int i = 0; i < c_count; i++) {
        this->courses[i] = courses[i];
    }
}

int Student::getCourseSize() {
    return this->course_size;
}

void Student::setCourseSize(int course_size) {
    this->course_size = course_size;
}

Student::Student(string name) {
    this->name = name;
    ifstream in("../documents/users/" + name + "/" + name + ".data");
    int c_count, all_count;//�γ�����
    in >> c_count;
    course_size = c_count;
    courses = new course[c_count];
    prepocess p;
    course *allCourses = p.coursesInitialize(all_count);//done
    for (int i = 0; i < c_count; i++) {
        string course;
        int counts;//�γ̣���ҵ���ô���
        in >> course >> counts;
        courses[i].setFinishSize(counts);
        for (int j = 0; j < all_count; j++) {
            if (!OurStr::StrCmp(allCourses[j].getName(), course)) {
                courses[i] = allCourses[j];
                break;
            }
        }
        hw_con *b = new hw_con[counts];
        for (int j = 0; j < counts; j++) {
            in >> b[j].finish;
            if (b[j].finish) {
                in >> b[j].road;
                in >> b[j].MD5;
            }
        }
        courses[i].setFinish(b, counts);
        delete[] b;
    }
    delete[] allCourses;
    in.close();
}

void Student::showMenu() {
    printf("��ӭѧ�� %s��", getName().c_str());
    int choice = 0;
    do {
        updateTime();
        cout << "��ѡ��Ҫ�����ϵͳ(��0�˳�)\n";
        printf("1.������Ϣ����ϵͳ\n");
        printf("2.������Ϣ����ϵͳ\n");
        choice = input::getOperatorNum();
        switch (choice) {
            case 1:
                choice = showCourseMenu();
                break;
            case 2:
                choice = showActivityMenu();
                break;
            case 0:
                return;
            default:
                printf("�����������������\n");
                break;
        }
    } while (choice);
    return;
}

int Student::showCourseMenu() {
    updateTime();
    printf("��ӭ������ڹ���ϵͳ!��ѡ��Ҫ���еĲ���:\n");
    printf("1.�鿴���տγ���Ϣ\n");
    printf("2.�����γ̱�\n");
    printf("3.�����γ̲鿴����\n");
    printf("4.�鿴�γ���ҵ\n");
    printf("5.�ϴ���ҵ\n");
    printf("6.��ĳһ�ļ�\n");
    printf("9.������һ��\n");
    printf("0.������ҳ\n");
    int choice = input::getOperatorNum();
    while (choice) {
        switch (choice) {
            case 1:
                showTodayCourse();//��ʾ���տγ̱�
                break;
            case 2:
                courseTable();//done
                break;
            case 3:
                showCourseDetail();//done
                break;
            case 4:
                showCourseHw();//done
                break;
            case 5:
                uploadHw();//lack compress function
                break;
            case 6:
                showDoc();//done
                break;
            case 9:
                return 1;
            case 0:
                return 0;
            default:
                printf("�����������������\n");
                break;
        }
        printf("��ӭ������ڹ���ϵͳ!��ѡ��Ҫ���еĲ���:\n");
        printf("1.�鿴���տγ���Ϣ\n");
        printf("2.�����γ̱��򿪲鿴\n");
        printf("3.�����γ̲鿴����\n");
        printf("4.�鿴�γ���ҵ\n");
        printf("5.�ϴ���ҵ\n");
        printf("6.��ĳһ�ļ�\n");
        printf("9.������һ��\n");
        printf("0.������ҳ\n");
        choice = input::getOperatorNum();
    }
    return 1;
}

void Student::showDoc()
{
    cout << "������Ҫ�鿴�ļ��Ŀγ�����:" << endl;
    string courseName = Input<string>();
    course c;
    if((c = searchCourse(courses, course_size, courseName)).getName() != "null")
    {
        c.viewDocument(name);
    }
}

void Student::showTodayCourse() {
    cout << "������" << modtime.yr << "��" << modtime.mn << "��" << modtime.day << "��,����";
    string week[7] = {"��", "һ", "��", "��", "��", "��", "��"};
    int weekDay = modtime.calculateWeekDay();
    cout << week[weekDay] << endl;
    for (int i = 0; i < course_size; i++) {
        for (int j = 0; j < courses[i].getTimeSize(); j++) {
            if (courses[i].getTime()[j].week == weekDay) {
                printf("%s\t%dʱ--%dʱ\n", courses[i].getName().c_str(), courses[i].getTime()[j].starthour,
                       courses[i].getTime()[j].endhour);
            }
        }
    }
}

void Student::courseTable() {
    ofstream out("../documents/users/" + this->name + "/courseTable_" + name + ".csv");
    out << ",����һ,���ڶ�,������,������,������,������,������\n";
    string table[14][7];
    for (int i = 0; i < course_size; i++) {
        for (int j = 0; j < courses[i].getTimeSize(); j++) {
            for (int k = courses[i].getTime()[j].starthour; k <= courses[i].getTime()[j].endhour; k++) {
                table[k - 8][(courses[i].getTime()[j].week + 6) % 7] = courses[i].getName();
            }
        }
    }
    for (int i = 0; i < 14; i++) {
        out << i + 8 << ":00";
        for (int j = 0; j < 7; j++) {
            out << ',' << table[i][j];
        }
        out << endl;
    }
    out.close();
    cout << "�Ѿ����ɿγ̱����ڴ�..." << endl;
    string cmd = "cd ..\\documents\\users\\" + this->name + " & courseTable_" + this->name + ".csv";
    system(cmd.c_str());
}

void Student::showCourseDetail()
{
    cout << "����Ҫ�����Ŀγ�����:";
    string name = Input<string>();
    course result;
    result = searchCourse(courses, course_size, name);
    if(result.getName() == "null") printf("�����Ŀγ̲�����!\n");
    else
    {
        string weekday[7] = {"��һ", "�ܶ�", "����", "����", "����", "����", "����"};
        cout << "�γ�����:" << result.getName();
        cout << "�Ͽ�ʱ��:" << endl;
        for(int i = 0; i < result.getTimeSize(); i++)
        {
            cout << "\t" << i << "." << weekday[result.getTime()[i].week] << " " << result.getTime()[i].starthour << ":00-" << result.getTime()[i].endhour << ":00" << endl;
        }
        cout << "�Ͽεص�:" << result.getAddress() << endl;
        cout << "�γ�����:" << endl;
        for(int i = 0; i < result.getDocumentsSize(); i++)
        {
            cout << "\t" << i << "." << result.getDocuments()[i] << endl;
        }
        cout << "�γ���ҵ:" << endl;
        for(int i = 0; i < result.getHomeWorkSize(); i++)
        {
            cout << "\t" << i + 1 << "." << result.getHomeWork()[i] << endl;
        }
        cout << "�γ�QQȺ:" << result.getQQGroup() << endl;
    }
}

void Student::showCourseHw()
{
    cout << "����Ҫ�鿴��ҵ�Ŀγ�����:";
    string name = Input<string>();
    course result;
    result = searchCourse(courses, course_size, name);
    if(result.getName() == "null") printf("�����Ŀγ̲�����!\n");
    else
    {
        cout << "��ҵ������:" << endl;
        for(int i = 0; i < result.getHomeWorkSize(); i++)
        {
            string s;
            if(result.getFinish()[i].finish) s = "�����";
            else s = "δ���";
            cout << "\t" << i + 1 << "." << result.getHomeWork()[i] << ' ' << s << endl;
        }
    }
    
}

void Student::uploadHw()
{
    cout << "����Ҫ�ϴ���ҵ�Ŀγ�����:";
    string courseName = Input<string>();
    course result;
    result = searchCourse(courses, course_size, courseName);
    if(result.getName() == "null") printf("�����Ŀγ̲�����!\n");
    else if(result.getHomeWorkSize() == 0) printf("��δ������ҵ!\n"); 
    else
    {
        cout << "����Ҫ�ϴ�����ҵ·��(�㼶Ŀ¼���ԡ�\\���ָ�):";
        string path = Input<string>();
        cout << "����Ҫ�ϴ��ڼ�����ҵ:(1-" << result.getHomeWorkSize() << ")";
        int num = Input<int>();
        result.uploadHomework(path, name, num - 1);
    }
    for(int i = 0; i < course_size; i++)
    {
        if(courses[i].getName() == courseName)
        {
            courses[i] = result;
            break;
        }
    }
}

void Student::saveStuInfo() {
    ofstream out("../documents/users/" + this->name + "/" + this->name + ".data");
    out << course_size << endl;
    for (int i = 0; i < course_size; i++) {
        out << courses[i].getName() << ' ';
        out << courses[i].getFinishSize() << endl;
        for (int j = 0; j < courses[i].getFinishSize(); j++) {
            out << courses[i].getFinish()[j].finish;
            if (courses[i].getFinish()[j].finish) {
                cout << courses[i].getFinish()[j].road << endl;//BUG
                cout << courses[i].getFinish()[j].MD5 << endl;
                out << ' ' << courses[i].getFinish()[j].road << ' ' << courses[i].getFinish()[j].MD5 << endl;
            } else {
                out << endl;
            }
        }
    }
    out.close();
    cout << "���Զ�����ѧ��" << name << "�Ŀγ���Ϣ" << endl;
}

int Student::showActivityMenu() {
    int choice;
    do {
        updateTime();
        //����finish
        printf("��ӭ��������ϵͳ!��ѡ��Ҫ���еĲ���:\n");
        cout << "1.�����¼�" << endl;
        cout << "2.�¼�һ��(ȫ��)" << endl;
        cout << "3.�����¼�һ��" << endl;
        cout << "4.����(����)����" << endl;
        printf("9.�����ϼ�\n");
        printf("0.������ҳ\n");
        choice = input::getOperatorNum();
        switch (choice) {
            case 1:
                student->addActivity();
                break;
            case 2:
                student->showActivities(false);
                break;
            case 3:
                student->showActivities(true);
                break;
            case 4:
                student->addClocks();
                break;
            case 9:
                return 1;
            case 0:
                student->Activities->size = 0;
                return 0;
            default:
                printf("�����������������\n");
                break;
        }
    } while (choice);
    return 1;
}

Student::Student() {
    name = "null";
    courses = NULL;
    course_size = 0;
}

HashMap<int, Activity> *Student::getActivities() const {
    return activities;
}

void Student::InitStudent() {
    ifstream db("../database/activities/" + student->name);
    int startTime, endTime, clk;
    string address, description;
    while (db >> startTime >> endTime >> address >> description >> clk) {
        Activity activity;
        Time start, end;
        start.inputTime(startTime);
        end.inputTime(endTime);
        activity.setStartTime(start);
        activity.setEndTime(end);
        activity.setAddress(address);
        activity.setDescription(description);
        activity.setClk(clk);
        student->getActivities()->put(activity.getStartTime().timeStamp(), activity);
        if (clk >= 0) {
            Time time = start.desc(clk);
            if (clocks->get(time.timeStamp())->first) {
                clocks->get(time.timeStamp())->second.addEvent(activity.toString());
            } else {
                Clock clock;
                clock.setTimestamp(time.timeStamp());
                clock.addEvent(activity.toString());
                clocks->put(time.timeStamp(), clock);
            }
        }
        clog << "��ȡ���ػ��" << activity.toString() << endl;
        Activities->push(activity);
    }
    db.close();
    db = ifstream("../database/clocks/" + student->name);
    while (db >> startTime >> description) {
        Clock clock;
        clock.setTimestamp(startTime);
        clock.addEvent(description);
        student->getClocks()->put(startTime, clock);
        clog << "��ȡ�������ӣ�" << clock.timestamp << ":" << description << endl;
    }
}

void Student::showActivities(bool today) {
    int sz = Activities->size;
    for (int i = 0; i < sz; i++) {
        Activity activity = Activities->get(i);
        if (today && activity.getStartTime().day != modtime.day) {
            continue;
        }
        cout << Activities->get(i).toString() << endl;
    }
}

HashMap<int, Clock> *Student::getClocks() const {
    return clocks;
}

void Student::addClocks() {
    updateTime();
    cout << "[ע��]ֻ�ܸ��Լ��������������Ҳ�֧��ɾ�������ֶ��������ݿ��ļ�" << endl;
    int timestamp = modtime.timeStamp(), rep = 0, interval = 1;
    Time time;

    cout << "���ĸ�ʱ�俪ʼ����ʽ�磺21010820��" << endl;
    timestamp = Input<int>();
    time.inputTime(timestamp);
    cout << "���Ѽ������Сʱ(��ʾ��һ��168Сʱ��" << endl;
    interval = Input<int>();
    cout << "һ����Ҫ���Ѷ��ٴ�" << endl;
    rep = Input<int>();
    cout << "�¼�����(����ʱ���)" << endl;
    string description = Input<string>();

    for (int i = 0; i < rep; i++) {
        Clock clock;
        clock.setTimestamp(time.timeStamp());
        clock.addEvent(description);
        student->getClocks()->put(time.timeStamp(), clock);
        clog << "������" << time.toString() << "������" << endl;
        time.incre(interval);
        ofstream _config("../database/clocks/" + student->name, ios::app);
        assert(_config);
        _config << clock.timestamp << " " << description << endl;
        _config.close();
    }
    return;
}

Array<Activity> *Student::getActivityArray() {
    return Activities;
}
