#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "School.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::ifstream, std::istringstream, std::endl, std::cout;

// one method is provided to students; students implement all other methods
//addStudents
void School::addStudents(string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("addStudents: can't open file");
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail()) {
        Student student(uin, name);
        bool exists = false;
        for (Student s : students) {
            if (s == student) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            students.push_back(student);
        }
    }
  }
}

//isEnrolled
bool School::isEnrolled(std::string student_id) const{
  for (size_t i = 0; i < students.size(); ++i){
    if (students[i].get_id() == student_id){
      return true;  
    }
  }
  return false;
}

//listStudents
void School::listStudents(std::ostream& os) const{
  if (students.size() == 0){
    os << "No students" << '\n';
  }
  else{
    for(size_t j = 0; j < students.size(); ++j){
      os << students[j].get_id() << "," << students[j].get_name() << '\n';
    }
  }
}

//addCourses
void School::addCourses(std::string filename){
  ifstream ifs(filename);
  if(!ifs.is_open()) {
    throw std::invalid_argument("addCourses: can't open file");
  }
  while(!ifs.eof()) {
    string line;
    string id;
    string title;
    string startTimeStamp;
    string endTimeStamp;
    string startHours;
    string startMinutes;
    string endHours;
    string endMinutes;
    int seconds = 0;
    bool preexisting = false;

    getline(ifs, line);
    istringstream ss(line);
    getline(ss, id, ','); 
    getline(ss, startTimeStamp, ',');
    getline(ss, endTimeStamp, ',');
    getline(ss, title);

    if(!ss.fail()){
      ss.clear();
      ss.str(startTimeStamp);
      getline(ss, startHours, ':'); 
      getline(ss, startMinutes);
      Date startTime(std::stoi(startHours), std::stoi(startMinutes), seconds);

      ss.clear();
      ss.str(endTimeStamp);
      getline(ss, endHours, ':');
      getline(ss, endMinutes);
      Date endTime(std::stoi(endHours), std::stoi(endMinutes), seconds);

      Course newCourse(id, title, startTime, endTime);
      for(Course c : courses){
        if(c.getID() == newCourse.getID()){
          preexisting = true;
        }
      }
      if(!preexisting){
        courses.push_back(newCourse);
      }
    }
  }
}

//listCourses
void School::listCourses(std::ostream& os) const{
  if(courses.size() == 0){
    os << "No courses" << '\n';
    return;
  }
  for(Course c : courses){
    os << c.getID() << ',';
    if(c.getStartTime().getHour() < 10){
      if(c.getStartTime().getHour() == 0){
        os << "00";
      }
      else{
        os << '0' << c.getStartTime().getHour();
      }
    }
    else{
      os << c.getStartTime().getHour();
    }
    os << ':';
    if(c.getStartTime().getMin() < 10){
      if(c.getStartTime().getMin() == 0){
        os << "00";
      }
      else{
        os << '0' << c.getStartTime().getMin();
      }
    }
    else{
      os << c.getStartTime().getMin();
    } 
    os << ',';
    if(c.getEndTime().getHour() < 10){
      if(c.getEndTime().getHour() == 0){
        os << "00";
      }
      else{
        os << '0' << c.getEndTime().getHour();
      }
    }
    else{
      os << c.getEndTime().getHour();
    }
    os << ':';
    if(c.getEndTime().getMin() < 10){
      if(c.getEndTime().getMin() == 0){
        os << "00";
      }
      else{
        os << '0' << c.getEndTime().getMin();
      }
    }
    else{
      os << c.getEndTime().getMin();
    } 
    os << ',' << c.getTitle() << '\n';
  }
}

unsigned int School::addAttendanceData(string filename){
  unsigned int invalidRecords = 0;
  ifstream ifs(filename);
  if(!ifs.is_open()) {
    throw std::invalid_argument("addAttendanceData: can't open file");
  }
  while (!ifs.eof()){
    //declare placeholder vars
    string line;
    string year;
    string month;
    string day;
    string hour;
    string minute;
    string second;
    string courseID;
    string studentID;

    //construct objects
    getline(ifs, line);
    istringstream ss(line);

    //slice accordingly
    getline(ss, year, '-');
    getline(ss, month, '-');
    getline(ss, day, ' ');
    getline(ss, hour, ':');
    getline(ss, minute, ':');
    getline(ss, second, ',');
    getline(ss, courseID, ',');
    getline(ss, studentID);

    if(!ss.fail()){
      bool alreadyStudent = false;
      for(Student c : students){
        if(c.get_id() == studentID){
          alreadyStudent = true;
          break;
        }
      }
      if(!alreadyStudent){
        invalidRecords++;
      }

      bool alreadyCourse = false;
      for(Course c : courses){
        if(c.getID() == courseID){
          alreadyCourse = true;
          break;
        }
      }
      if(alreadyStudent && !alreadyCourse){ 
        invalidRecords++;
      }

      bool dateValid = true;
      Date attendanceDate(std::stoi(year), std::stoi(month), std::stoi(day), 
          std::stoi(hour), std::stoi(minute), std::stoi(second));
      if(!attendanceDate.isValid()){
        dateValid = false;
        if(alreadyStudent && alreadyCourse && !dateValid){
          invalidRecords++;
        }
      }

      if(alreadyStudent && alreadyCourse && dateValid){
        AttendanceRecord newRecord(courseID, studentID, attendanceDate);
        for(size_t i = 0; i < courses.size(); i++){
          if(courses.at(i).getID() == courseID){
            courses.at(i).addAttendanceRecord(newRecord);
          }
        }
      } 
    } 
  } 
  return invalidRecords;
}

void School::outputCourseAttendance(std::ostream& os, std::string course_id) const{
  //check if it appears
  for (size_t i = 0; i < courses.size(); i++){
    if (course_id == courses[i].getID()){
      courses[i].outputAttendance(std::cout);
      return;
    }
  }
  throw std::invalid_argument("Course does not exist");
}

void School::outputStudentAttendance(std::ostream& os, std::string student_id, std::string course_id) const{
  for (size_t i = 0; i < courses.size(); i++){
    if (course_id == courses[i].getID()){
      courses[i].outputAttendance(std::cout, student_id);
      return;
    }
  }
  os << "No records" << '\n';
}