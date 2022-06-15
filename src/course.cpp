#include "course.h"

course::course( string name,
                course_time * time,
                int t_size,
                string address,
                string * documents,
                int doc_count,
                string current,
                string * homeWork,
                int hw_size,
                string QQGroup,
                Time extime,
                string exaddress)
{
    this->name = name;
    this->time = new course_time[t_size];//构造函数新建另一个对象，而非直接赋值
    this->t_size = t_size;
    for(int i = 0; i < t_size; i++)
    {
        this->time[i] = time[i];
    }
    this->address = address;
    this->current = current;
    this->documents = new string[doc_count];
    this->doc_size = doc_count;
    for(int i = 0; i < doc_count; i++)
    {
        this->documents[i] = documents[i];
    }
    this->exaddress = exaddress;
    this->extime = extime;
    this->homeWork = new string[hw_size];
    this->hw_size = hw_size;
    for(int i = 0; i < hw_size; i++)
    {
        this->homeWork[i] = homeWork[i];
    }
    this->QQGroup = QQGroup;
}

course::course()
{
    name = "null";
    time = new course_time[0];
    t_size = 0;
    address = "null";
    documents = new string[0];
    doc_size = 0;
    current = "null";
    homeWork = new string[0];
    hw_size = 0;
    QQGroup = "null";
    exaddress = "null";
    finish_con = new hw_con[0];
    finish_size = 0;
}

course& course::operator =(const course& c)
{
    address = c.address;
    name = c.name;
    if(t_size > 0)
    {
        delete [] time;
        time = NULL;
        t_size = 0;
    }
    time = new course_time[c.t_size];
    t_size = c.t_size;
    for(int i = 0; i < t_size; i++)
    {
        time[i] = c.time[i];
    }
    if(doc_size > 0)
    {
        delete [] documents;
        documents = NULL;
        doc_size = 0;
    }
    documents = new string[c.doc_size];
    doc_size = c.doc_size;
    for(int i = 0; i < doc_size; i++)
    {
        this->documents[i] = c.documents[i];
    }
    current = c.current;
    for(int i = 0; i < hw_size; i++)
    {
        cout << homeWork[i] << endl;
    }
    if(hw_size > 0)
    {
        delete [] homeWork;
        homeWork = nullptr;
        hw_size = 0;
    }
    homeWork = new string[c.hw_size];
    hw_size = c.hw_size;
    for(int i = 0; i < hw_size; i++)
    {
        this->homeWork[i] = c.homeWork[i];
    }
    if(finish_size > 0)
    {
        delete [] finish_con;
        finish_con = nullptr;
        finish_size = 0;
    }
    finish_con = new hw_con[c.finish_size];
    finish_size = c.finish_size;
    for(int i = 0; i < finish_size; i++)
    {
        finish_con[i] = c.finish_con[i];
    }
    extime = c.extime;
    exaddress = c.exaddress;
    QQGroup = c.QQGroup;
    return *this;
}//使用了深拷贝

string course::getName(){return name;}
void course::setName(string name){this->name = name;}
course_time * course::getTime(){return time;}
void course::setTime(course_time * time, int size){
    this->time = new course_time[size];
    for(int i = 0; i < size; i++)
    {
        this->time[i].endhour = time[i].endhour;
        this->time[i].starthour = time[i].starthour;
        this->time[i].week = time[i].week;
    }
}
int course::getTimeSize(){return t_size;}
void course::setTimeSize(int size){this->t_size = size;}
string course::getAddress(){return address;}
void course::setAddress(string address){this->address = address;}
string* course::getDocuments(){return documents;}
void course::setDocuments(string * documents, int size)
{
    if(this->documents != NULL)
    {
        delete [] this->documents;
        this->documents = NULL;
        doc_size = 0;
    }
    this->documents = new string[size];
    doc_size = size;
    for(int i = 0; i < size; i++)
        this->documents[i] = documents[i];
}
int course::getDocumentsSize(){return doc_size;}
void course::setDocumentsSize(int size){this->doc_size = size;}
string course::getCurrent(){return current;}
void course::setCurrent(string current){this->current = current;}
string * course::getHomeWork(){return this->homeWork;}
void course::setHomeWork(string * homeWork, int size)
{
    if(this->homeWork != NULL)
    {
        delete [] this->homeWork;
        this->homeWork = NULL;
        hw_size = 0;
    }
    this->homeWork = new string[size];
    hw_size = size;
    for(int i = 0; i < size; i++)
        this->homeWork[i] = homeWork[i];
}
int course::getHomeWorkSize(){return hw_size;}
void course::setHomeWorkSize(int size){this->hw_size = size;}
Time course::getExtime(){return extime;}
void course::setExtime(Time extime){this->extime = extime;}
string course::getExaddress(){return exaddress;}
void course::setExaddress(string exaddress){this->exaddress = exaddress;}
string course::getQQGroup(){return QQGroup;}
void course::setQQGroup(string QQGroup){this->QQGroup = QQGroup;}
hw_con * course::getFinish(){return finish_con;}
void course::setFinish(hw_con * finish_con, int size)
{
    if(this->finish_con != NULL)
    {
        delete [] this->finish_con;
        this->finish_con = NULL;
        finish_size = 0;
    }
    if(size == 0)
    {
        this->finish_con = NULL;
        finish_size = 0;
        return;
    }
    this->finish_con = new hw_con[size];
    for(int i = 0; i < size; i++)
    {
        this->finish_con[i].finish = finish_con[i].finish;
        this->finish_con[i].road = finish_con[i].road;
        this->finish_con[i].MD5 = finish_con[i].MD5;
    }
    this->finish_size = size;
}
int course::getFinishSize(){return finish_size;}
void course::setFinishSize(int size){this->finish_size = size;}

/**
 * @brief 上传学生作业
 * 
 * @param road 
 * @return string 
 */
void course::uploadHomework(string road, string stuName, int no)
{
    for(int i = 0; i < road.length(); i++)
    {
        if(road[i] == '/')
        {
            road[i] = '\\';
        }
    }
    string input;
    unsigned char decrypt[16];
    ifstream in(road);
    char c;
    while(in.get(c))
    {
        input += c;
    }
    in.close();
    MD5 md5;
    md5.MD5Update(md5.getContext(), (unsigned char *)input.c_str(), input.length());
    md5.MD5Final(md5.getContext(), decrypt);
    string md5str = "";
    for(int i = 0; i < 16; i++)
    {
        if(decrypt[i] != ' ' && decrypt[i] != '\n' && decrypt[i] != '\r')
        {
            md5str += decrypt[i];
        }
    }
    if(!OurStr::StrCmp(md5str, finish_con[no].MD5))
    {
        QMessageBox::information(NULL, "Error", "已上传过重复文件，请勿重复上传！");
        return;
    }
    else
    {
        if(finish_con[no].finish)
        {
            QMessageBox::StandardButton result = QMessageBox::question(NULL, "提示", "注意:此操作将覆盖旧文件,请确认是否继续？");
            if(result == QMessageBox::Yes)
            {
                string inroad = "..\\documents\\users\\" + stuName + "\\" + name + "\\" + to_string(no + 1) + "\\" +  OurStr::getFilename(road).substr(0, OurStr::getFilename(road).rfind('.'));
                system(("del " + inroad).c_str());
                QMessageBox::information(NULL, "通知", "覆盖成功！");
            }
        }
        if(OurStr::getSuffix(road) == "txt" || OurStr::getSuffix(road) == "TXT")
        {
            string outRoad = "..\\documents\\users\\" + stuName + "\\" + name + "\\" + to_string(no + 1) + "\\" +  OurStr::getFilename(road).substr(0, OurStr::getFilename(road).rfind('.'));
            compression c;
            if(c.Code(road, outRoad))
            {
                QMessageBox::information(NULL, "通知", "压缩上传成功！");
                finish_con[no].finish = true;
                finish_con[no].road = OurStr::getFilename(road);
                finish_con[no].MD5 = md5str;
            }
            else
            {
                QMessageBox::information(NULL, "Error", "压缩上传失败！请联系开发者");
            }
        }
        else
        {
            string cmd = "copy \"" + road + "\" ..\\documents\\users\\" + stuName + "\\" + name + "\\" + to_string(no + 1) + "\\" +  OurStr::getFilename(road);
            system(cmd.c_str());
            finish_con[no].finish = true;
            finish_con[no].road = OurStr::getFilename(road);
            finish_con[no].MD5 = md5str;
            QMessageBox::information(NULL, "通知", "非压缩上传成功！");
        }
    }
    
}

void course::viewDocument(string stuName)
{
    cout << "请选择要查看的类型:" << endl;
    printf("1.课程资料\t2.课程作业\n");
    int type = input::getOperatorNum();
    if(type == 1)
    {
        cout << "请选择要查看的资料:" << endl;
        for(int i = 0; i < doc_size; i++)
        {
            cout << i + 1 << "." << documents[i] << endl;
        }
        int no = input::getOperatorNum() - 1;
        string inroad = "..\\documents\\public\\" + name + "\\" + documents[no].substr(0, documents[no].rfind('.'));
        string outroad = "..\\documents\\public\\" + name + "\\" + documents[no];
        compression c;
        if(c.Decode(inroad, outroad))
        {
            cout << "解压成功,正在打开文件..." << endl;
            system(("..\\documents\\public\\" + name + "\\" + documents[no]).c_str());
            cout << "浏览结束,自动删除解压文件" << endl;
            system(("del ..\\documents\\public\\" + name + "\\" + documents[no]).c_str());
        }
        else
        {
            cout << "解压失败" << endl;
        }
    }
    else if(type == 2)
    {
        cout << "请选择要查看的作业:" << endl;
        for(int i = 0; i < hw_size; i++)
        {
            cout << i + 1 << "." << homeWork[i] << endl;
        }
        int no = input::getOperatorNum() - 1;
        printf(homeWork[no].c_str());
        string inroad = "..\\documents\\users\\" + stuName + "\\" + name + "\\" + to_string(no + 1) + '\\' + finish_con[no].road.substr(0, finish_con[no].road.rfind('.'));
        string outroad = "..\\documents\\users\\" + stuName + "\\" + name + "\\" + to_string(no + 1) + '\\' + finish_con[no].road;
        compression c;
        if(c.Decode(inroad, outroad))
        {
            cout << "解压成功,正在打开文件..." << endl;
            system(("..\\documents\\users\\" + stuName + "\\" + name + "\\" + to_string(no + 1) + '\\' + finish_con[no].road).c_str());
            cout << "浏览结束,自动删除解压文件" << endl;
            system(("del ..\\documents\\users\\" + stuName + "\\" + name + "\\" + to_string(no + 1) + '\\' + finish_con[no].road).c_str());
        }
        else
        {
            cout << "解压失败" << endl;
        }
    }
}
