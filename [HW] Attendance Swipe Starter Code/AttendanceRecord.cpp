#include <string>
#include <iostream>
#include "AttendanceRecord.h"
#include "Date.h"

using std::cout;
//default constructor
AttendanceRecord::AttendanceRecord(std::string course_id, std::string student_id, Date time) : course_id(course_id), student_id(student_id), time(time){

}

//getCourseID()
std::string AttendanceRecord::getCourseID() const{
    return course_id;
}
std::string AttendanceRecord::getStudentID() const{
    return student_id;
}
Date AttendanceRecord::getDate() const{
    return time;
}
