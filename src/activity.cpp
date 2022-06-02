#include "activity.h"

using namespace std;


const Time &Activity::getStartTime() const {
    return startTime;
}

void Activity::setStartTime(Time startTime) {
    Activity::startTime = startTime;
}

const Time &Activity::getEndTime() const {
    int time;
    return endTime;
}

void Activity::setEndTime(Time endTime) {

    Activity::endTime = endTime;

}


const string &Activity::getDescription() const {
    return description;
}

void Activity::setDescription(const string &description) {
    Activity::description = description;
}

const string &Activity::getAddress() const {
    return address;
}

void Activity::setAddress(const string &address) {
    Activity::address = address;
}

string Activity::toString() {
    return "from " + startTime.toString() + " to " + endTime.toString() + ": "\
            "In " + address + ":" + description;
}


Activity::Activity() {}

string Activity::storeStr() {
    return to_string(startTime.timeStamp()) + " " + to_string(endTime.timeStamp()) + " " + address +\
    " " + description + " " + to_string(clk);
}

Activity::~Activity() {}

int Activity::getClk() const {
    return clk;
}

void Activity::setClk(int clk) {
    Activity::clk = clk;
}

int Activity::getMemberCnt() const {
    return memberCnt;
}

void Activity::setMemberCnt(int memberCnt) {
    Activity::memberCnt = memberCnt;
    this->members = new Array<string>(memberCnt);
}

Array<string> *Activity::getMembers() const {
    return members;
}

void Activity::setMembers(Array<string> *members) {
    Activity::members = members;
};
