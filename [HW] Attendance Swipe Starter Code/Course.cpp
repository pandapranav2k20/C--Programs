#include <iostream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::endl, std::cout;

//default constructor
Course::Course(std::string id, std::string title, Date startTime, Date endTime): id(id), title(title), startTime(startTime), endTime(endTime){

}

//getID()
std::string Course::getID() const{
    return id;
}

//getTitle()
std::string Course::getTitle() const{
    return title;
}

//getStartTime()
Date Course::getStartTime() const{
    return startTime;
}

//getEndTime()
Date Course::getEndTime() const{
    return endTime;
}

//addAttendanceRecord
void Course::addAttendanceRecord(AttendanceRecord ar){
    if(!ar.getDate().isValid()){
        throw std::invalid_argument("Course.cpp: 1 Attendance Date was Invalid\n");
        return;
    }
    if(ar.getDate().getHour() == startTime.getHour() && ar.getDate().getHour() == endTime.getHour()){
        if(ar.getDate().getMin() >= startTime.getMin() && ar.getDate().getMin() <= endTime.getMin()){
            attendanceRecords.push_back(ar);
            return;
        }
        else{
            throw std::invalid_argument("Course.cpp: 2 Attendance Date was Invalid\n");
            return;
        }
    }
    else if(ar.getDate().getHour() >= startTime.getHour() && ar.getDate().getHour() <= endTime.getHour()){
        if(ar.getDate().getHour() == startTime.getHour()){
            if(ar.getDate().getMin() > startTime.getMin()){
                attendanceRecords.push_back(ar);
                return;
            }
            if(ar.getDate().getMin() == startTime.getMin()){
                if(ar.getDate().getSec() >= startTime.getSec()){
                    attendanceRecords.push_back(ar);
                    return;
                }
            }
            throw std::invalid_argument("Course.cpp: 3 Attendance Date was Invalid\n");
            return;
        }
        else if(ar.getDate().getHour() == endTime.getHour()){ 
            if(ar.getDate().getMin() < endTime.getMin()){
                attendanceRecords.push_back(ar);
                return;
            }
            if(ar.getDate().getMin() == endTime.getMin()){
                if(ar.getDate().getSec() <= endTime.getSec()){
                    attendanceRecords.push_back(ar);
                    return;
                }
                else{
                    throw std::invalid_argument("Course.cpp: 4 Attendance Date was Invalid\n");
                    return;
                }
            }
        }
        else{
            attendanceRecords.push_back(ar);
            return;
        }
    }
    else{
        throw std::invalid_argument("Course.cpp: 5 Attendance Date was Invalid\n");
        return;
    }
}

//outputAttendance
void Course::outputAttendance(std::ostream& os) const{
    if(attendanceRecords.size() == 0){
        os << "No records\n";
        return;
    }
    for(AttendanceRecord A : attendanceRecords){
        os << A.getDate().getMonth() << '/' << A.getDate().getDay() << '/' << A.getDate().getYear() << ' ';
        if(A.getDate().getHour() == 0){
            os << "00";
        }
        else if(A.getDate().getHour() < 10){
            os << '0' << A.getDate().getHour();
        }
        else{
            os << A.getDate().getHour();
        }
        os << ':';
        if(A.getDate().getMin() == 0){
            os << "00";
        }
        else if(A.getDate().getMin() < 10){
            os << '0' << A.getDate().getMin();
        }
        else{
            os << A.getDate().getMin();
        }
        os << ':';
        if(A.getDate().getSec() == 0){
            os << "00";
        }
        else if(A.getDate().getSec() < 10){
            os << '0' << A.getDate().getSec();
        }
        else{
            os << A.getDate().getSec();
        }
        os << ',' << A.getCourseID() << ',' << A.getStudentID() << '\n';
    }
}

//same thing given a student id
void Course::outputAttendance(std::ostream& os, std::string student_id) const{
    if(attendanceRecords.size() == 0){
        os << "No records" << '\n';
        return;
    }
    unsigned int numRecs = 0;
    for(AttendanceRecord A : attendanceRecords){ 
        if(A.getStudentID() == student_id){
            numRecs++;
            os << A.getDate().getMonth() << '/' << A.getDate().getDay() << '/' << A.getDate().getYear() << ' ';
            if(A.getDate().getHour() == 0){
                os << "00";
            }
            else if(A.getDate().getHour() < 10){
                os << '0' << A.getDate().getHour();
            }
            else{
                os << A.getDate().getHour();
            }
            os << ':';
            if(A.getDate().getMin() == 0){
                os << "00";
            }
            else if(A.getDate().getMin() < 10){
                os << '0' << A.getDate().getMin();
            }
            else{
                os << A.getDate().getMin();
            }
            os << ':';
            if(A.getDate().getSec() == 0){
                os << "00";
            }
            else if(A.getDate().getSec() < 10){
                os << '0' << A.getDate().getSec();
            }
            else{
                os << A.getDate().getSec();
            }
            os << ',' << A.getCourseID() << ',' << A.getStudentID() << '\n';
        } 
    }
    if(numRecs == 0){
        os << "No records" << '\n';
    }
}