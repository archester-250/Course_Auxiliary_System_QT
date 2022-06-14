
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
        cout << "时间格式错误" << endl;
        return true;
    }
    int len = student->getActivityArray()->getSize();
    Time tmp;
    tmp.inputTime(timestamp);
    for (int i = 0; i < student->getCourseSize(); i++){
        course cse;
        cse = student->getCourses()[i];
        for (int j = 0; j < cse.getTimeSize(); j++){
                    if (tmp.calculateWeekDay() == cse.getTime()[j].week &&\
                    tmp.hr >= cse.getTime()->starthour && \
                    tmp.hr < cse.getTime()->endhour) {
                        cout << "时间与课程" << cse.getName() << "冲突" << endl;
                        return true;
                    }
                }
    }
    for (int i = len - 1; i >= 0; i--){
        Activity activity = student->getActivityArray()->get(i);
        if (timestamp >= activity.getStartTime().timeStamp() && \
            timestamp < activity.getEndTime().timeStamp()) {
            QMessageBox::information(NULL, "CONFILICT", "To activity " + QString::fromStdString(activity.toString()));
//            cout << "时间与" << activity.toString() << "冲突" << endl;
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
    cout << "输入开始时间的字符串格式(如：22040715)" << endl;
    do {
        inTime = Input<int>();
    } while (time_conflict(inTime));
    startTime.inputTime(inTime);
    cout << "输入结束时间的字符串格式(如：22040718)" << endl;
    do {
        endTime.inputTime(Input<int>());
    } while (endTime.timeStamp() < inTime);
    cout << "输入活动地址" << endl;
    string address = Input<string>();
    cout << "输入除自己外的活动成员数" << endl;
    int memberCnt;
    do {
        memberCnt = Input<int>();
    } while (memberCnt >= 0);
    activity.setMemberCnt(memberCnt);
    while (memberCnt--) {
        cout << "添加成员：";
        string member = Input<string>();
        activity.getMembers()->push(member);
    }
    cout << "输入活动描述" << endl;
    string description = Input<string>();
    cout << "提前多少小时进行提醒全体成员(输入-1则不提醒)" << endl;
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
    clog << student->name << "添加事件：" << activity.toString() << endl;
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
    int c_count, all_count;//课程总数
    in >> c_count;
    course_size = c_count;
    courses = new course[c_count];
    prepocess p;
    course *allCourses = p.coursesInitialize(all_count);//done
    for (int i = 0; i < c_count; i++) {
        string course;
        int counts;//课程，作业布置次数
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
    printf("欢迎学生 %s，", getName().c_str());
    int choice = 0;
    do {
        updateTime();
        cout << "请选择要进入的系统(按0退出)\n";
        printf("1.课内信息管理系统\n");
        printf("2.课外信息管理系统\n");
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
                printf("输入错误，请重新输入\n");
                break;
        }
    } while (choice);
    return;
}

int Student::showCourseMenu() {
    updateTime();
    printf("欢迎进入课内管理系统!请选择要进行的操作:\n");
    printf("1.查看今日课程信息\n");
    printf("2.导出课程表\n");
    printf("3.搜索课程查看详情\n");
    printf("4.查看课程作业\n");
    printf("5.上传作业\n");
    printf("6.打开某一文件\n");
    printf("9.返回上一级\n");
    printf("0.返回主页\n");
    int choice = input::getOperatorNum();
    while (choice) {
        switch (choice) {
            case 1:
                showTodayCourse();//显示今日课程表
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
                printf("输入错误，请重新输入\n");
                break;
        }
        printf("欢迎进入课内管理系统!请选择要进行的操作:\n");
        printf("1.查看今日课程信息\n");
        printf("2.导出课程表并打开查看\n");
        printf("3.搜索课程查看详情\n");
        printf("4.查看课程作业\n");
        printf("5.上传作业\n");
        printf("6.打开某一文件\n");
        printf("9.返回上一级\n");
        printf("0.返回主页\n");
        choice = input::getOperatorNum();
    }
    return 1;
}

void Student::showDoc()
{
    cout << "请输入要查看文件的课程名称:" << endl;
    string courseName = Input<string>();
    course c;
    if((c = searchCourse(courses, course_size, courseName)).getName() != "null")
    {
        c.viewDocument(name);
    }
}

void Student::showTodayCourse() {
    cout << "今天是" << modtime.yr << "年" << modtime.mn << "月" << modtime.day << "日,星期";
    string week[7] = {"日", "一", "二", "三", "四", "五", "六"};
    int weekDay = modtime.calculateWeekDay();
    cout << week[weekDay] << endl;
    for (int i = 0; i < course_size; i++) {
        for (int j = 0; j < courses[i].getTimeSize(); j++) {
            if (courses[i].getTime()[j].week == weekDay) {
                printf("%s\t%d时--%d时\n", courses[i].getName().c_str(), courses[i].getTime()[j].starthour,
                       courses[i].getTime()[j].endhour);
            }
        }
    }
}

void Student::courseTable() {
    ofstream out("../documents/users/" + this->name + "/courseTable_" + name + ".csv");
    out << ",星期一,星期二,星期三,星期四,星期五,星期六,星期日\n";
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
    cout << "已经生成课程表。正在打开..." << endl;
    string cmd = "cd ..\\documents\\users\\" + this->name + " & courseTable_" + this->name + ".csv";
    system(cmd.c_str());
}

void Student::showCourseDetail()
{
    cout << "输入要搜索的课程名称:";
    string name = Input<string>();
    course result;
    result = searchCourse(courses, course_size, name);
    if(result.getName() == "null") printf("搜索的课程不存在!\n");
    else
    {
        string weekday[7] = {"周一", "周二", "周三", "周四", "周五", "周六", "周日"};
        cout << "课程名称:" << result.getName();
        cout << "上课时间:" << endl;
        for(int i = 0; i < result.getTimeSize(); i++)
        {
            cout << "\t" << i << "." << weekday[result.getTime()[i].week] << " " << result.getTime()[i].starthour << ":00-" << result.getTime()[i].endhour << ":00" << endl;
        }
        cout << "上课地点:" << result.getAddress() << endl;
        cout << "课程资料:" << endl;
        for(int i = 0; i < result.getDocumentsSize(); i++)
        {
            cout << "\t" << i << "." << result.getDocuments()[i] << endl;
        }
        cout << "课程作业:" << endl;
        for(int i = 0; i < result.getHomeWorkSize(); i++)
        {
            cout << "\t" << i + 1 << "." << result.getHomeWork()[i] << endl;
        }
        cout << "课程QQ群:" << result.getQQGroup() << endl;
    }
}

void Student::showCourseHw()
{
    cout << "输入要查看作业的课程名称:";
    string name = Input<string>();
    course result;
    result = searchCourse(courses, course_size, name);
    if(result.getName() == "null") printf("搜索的课程不存在!\n");
    else
    {
        cout << "作业完成情况:" << endl;
        for(int i = 0; i < result.getHomeWorkSize(); i++)
        {
            string s;
            if(result.getFinish()[i].finish) s = "已完成";
            else s = "未完成";
            cout << "\t" << i + 1 << "." << result.getHomeWork()[i] << ' ' << s << endl;
        }
    }
    
}

void Student::uploadHw()
{
    cout << "输入要上传作业的课程名称:";
    string courseName = Input<string>();
    course result;
    result = searchCourse(courses, course_size, courseName);
    if(result.getName() == "null") printf("搜索的课程不存在!\n");
    else if(result.getHomeWorkSize() == 0) printf("尚未布置作业!\n"); 
    else
    {
        cout << "输入要上传的作业路径(层级目录间以“\\”分隔):";
        string path = Input<string>();
        cout << "输入要上传第几次作业:(1-" << result.getHomeWorkSize() << ")";
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
                out << ' ' << courses[i].getFinish()[j].road << ' ' << courses[i].getFinish()[j].MD5 << endl;
            } else {
                out << endl;
            }
        }
    }
    out.close();
//    cout << "已自动保存学生" << name << "的课程信息" << endl;
}

int Student::showActivityMenu() {
    int choice;
    do {
        updateTime();
        printf("欢迎进入活动管理系统!请选择要进行的操作:\n");
        cout << "1.增加事件" << endl;
        cout << "2.事件一览(全部)" << endl;
        cout << "3.今日事件一览" << endl;
        cout << "4.增加(周期)闹钟" << endl;
        printf("9.返回上级\n");
        printf("0.返回主页\n");
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
                printf("输入错误，请重新输入\n");
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
		int i = 0;
        for (i = 0; i < Activities->getSize(); i++){
            if (Activities->get(i).getStartTime().timeStamp() > startTime){
                break;
            }
        }
        Activities->size++;
        for (int j = Activities->getSize() - 1; j >= i; j--){
            Activities->vals[j + 1] = Activities->vals[j];
        }
        Activities->vals[i] = activity;		
    }
    db.close();
    db = ifstream("../database/clocks/" + student->name);
    while (db >> startTime >> description) {
        Clock clock;
        clock.setTimestamp(startTime);
        clock.addEvent(description);
        student->getClocks()->put(startTime, clock);
//        clog << "读取本地闹钟：" << clock.timestamp << ":" << description << endl;
    }
}

void Student::showActivities(bool today) {
    int sz = Activities->size;
    for (int i = sz - 1; i >= 0; i--) {
        Activity activity = Activities->get(i);
        if (today && (activity.getStartTime().day != modtime.day || activity.getStartTime().mn != modtime.mn ||\
            activity.getStartTime().yr != modtime.yr) ) {
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
    cout << "[注意]只能给自己设置周期闹钟且不支持删除，请手动清理数据库文件" << endl;
    int timestamp = modtime.timeStamp(), rep = 0, interval = 1;
    Time time;

    cout << "从哪个时间开始（格式如：21010820）" << endl;
    timestamp = Input<int>();
    time.inputTime(timestamp);
    cout << "提醒间隔多少小时(提示：一周168小时）" << endl;
    interval = Input<int>();
    cout << "一共需要提醒多少次" << endl;
    rep = Input<int>();
    cout << "事件描述(提醒时输出)" << endl;
    string description = Input<string>();

    for (int i = 0; i < rep; i++) {
        Clock clock;
        clock.setTimestamp(time.timeStamp());
        clock.addEvent(description);
        student->getClocks()->put(time.timeStamp(), clock);
        clog << "已设置" << time.toString() << "的闹钟" << endl;
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
