#include <iostream>
#include <string>
#include "Student.h"

using std::cout, std::endl;

//default constructor
Student::Student(std::string student_id, std::string name) : id(student_id), name(name){
    //std::vector<std::string> course_ids;
}
//get_id()
std::string Student::get_id() const{
    return id;
}
//get_name()
std::string Student::get_name() const{
    return name;
}
//addCourse
void Student::addCourse(std::string course_id){
    for(unsigned int i = 0; i < course_ids.size(); i++){
        if(course_ids.at(i) == course_id){
            throw std::invalid_argument("repeated course ID\n");
        }
    }
    course_ids.push_back(course_id);
}

//listCourses
void Student::listCourses(std::ostream& os) const{
    os << "Courses for " << get_id() << '\n';
    //if the student is registered for 0 courses
    if (course_ids.size() == 0){
        os << "No courses" << '\n';
    }
    //otherwise, output all courses the student has added   
    else{
        for (size_t i = 0; i < course_ids.size(); i++){
            os << course_ids.at(i) << '\n';
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Student& s){
    s.listCourses(os);
    return os;
}