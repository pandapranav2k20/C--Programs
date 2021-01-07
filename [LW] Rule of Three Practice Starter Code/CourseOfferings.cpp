#include <iostream>
#include <string>
#include "Course.h"
#include "Section.h"
#include "CourseOfferings.h"

using std::string, std::endl;

/* TODO-STUDENT: implement the Rule of Three member functions:
** copy constructor, copy assignment operator, destructor
*/
CourseOfferings::CourseOfferings(const CourseOfferings& other){
	capacity = other.capacity;
	nbSections = other.capacity;
	course = other.course;
	year = other.year;
	semester = other.semester;
	sectionList = new Section[capacity];
	for (size_t i = 0; i < nbSections; ++i){
		this->sectionList[i] = other.sectionList[i];
	}
}
CourseOfferings::~CourseOfferings(){
	delete[] sectionList;
}

CourseOfferings& CourseOfferings::operator=(const CourseOfferings& other){
	if (this != &other) {
		course = other.course;
		year = other.year;
		semester = other.semester;
		nbSections = other.nbSections;
		capacity = other.capacity;
		delete[] sectionList;
		sectionList = new Section[capacity];
		for (size_t i = 0; i < nbSections; i++) {
			this->sectionList[i] = other.sectionList[i];
		}
	}
	return *this;
}
 /*CourseOfferings& CourseOfferings::operator=(const CourseOfferings& objToCopy){
if (&objToCopy != this){
    delete [] sectionList;
    sectionList = nullptr;
    year = objToCopy.year;
    semester = objToCopy.semester;
    nbSections = objToCopy.nbSections;
    capacity = objToCopy.capacity;

    sectionList = new Section[capacity];
    for (size_t i = 0; i < nbSections; i++){
        sectionList[i] = objToCopy.sectionList[i];
    }

}
return *this;

}*/
/* TODO-STUDENT: implement this function
** Parameters: none
** Return value: none
** Functionality: It updates the object to increase the capacity
**                of the atribute member sessionList.
**                If capacity is zero, it becomes one.
**                If capacity is greater than zero, it is doubled.
*/
void CourseOfferings::increaseSectionListCapacity() {
	// student will implement this one
	if (capacity == 0){
		//set capacity equal to one
		capacity = 1;
	}
	else if (capacity > 0){
		capacity = capacity * 2;
	}
	Section* newSection = new Section[capacity];
	for (size_t i = 0; i < nbSections; i++){
		newSection[i] = sectionList[i];
	}
	delete[] sectionList;
	sectionList = newSection;
}

/* TODO-STUDENT: implement this function
** Parameters: none
** Return value: none
** Functionality: it updates the object so that nbSections becomes zero.
*/
void CourseOfferings::clearSections() {
	// student will implement this one
	nbSections = 0;
}

/* TODO-STUDENT: implement this function
** Parameters: none
** Return value: none
** Functionality: it updates the object so that nbSessions and capacity become zero,
**                updating sessionList accordingly.
*/
void CourseOfferings::fullClearSections() {
	// student will implement this one
	nbSections = 0;
	capacity = 0;
	delete[] sectionList;
	sectionList = new Section[capacity];
}

/* TODO-STUDENT: implement this function
*/
std::ostream& operator<<(std::ostream& os, const CourseOfferings& co) {
	// student will implement this one
	os << "Year: " << co.getYear() << "Semester: " << co.getSemester() << "Course ID: " << co.getCourse().getId() << endl;
	os << "Course title: " << co.getCourse().getTitle() << endl;
	os << "Sections: " << endl;
	Section* sections = co.getSectionList();
	for (size_t i = 0; i < co.getNumberSections(); i++) {
		os << sections[i].getId() << " " << sections[i].getTime() << " " << sections[i].getLocation() << " " << sections[i].getInstructor() << endl;
	}
	return os;
}

CourseOfferings::CourseOfferings(Course c, unsigned int year, char semester) 
	: course(c), year(year), semester(semester) {
  capacity = 0;
  nbSections = 0;
  sectionList = nullptr;
}


CourseOfferings::CourseOfferings(unsigned int year, char semester, 
		const CourseOfferings& co)
		 : CourseOfferings(co) {
  this->year = year;
  this->semester = semester;
}

void CourseOfferings::addSection(const Section& s) {
	if (nbSections == capacity) {
		increaseSectionListCapacity();
	}
	sectionList[nbSections++] = s;
}

size_t CourseOfferings::findSection(string section) {
	for (size_t i = 0; i < nbSections; i++) {
		if (sectionList[i].getId() == section) {
			return i;
		}
	}
	return npos;
}

void CourseOfferings::replaceInstructor(string section, string instructor) {
	size_t idx = findSection(section);
	if (idx == npos) {
		throw std::invalid_argument("section not found");	
	} else {
		sectionList[idx].setInstructor(instructor);
	}
}

string CourseOfferings::getInstructor(string section) {
	size_t idx = findSection(section);
	if (idx == npos) {
		throw std::invalid_argument("section not found");	
	} else {
		return sectionList[idx].getInstructor();
	}
}

bool operator==(const CourseOfferings& lhs, const CourseOfferings& rhs) {
  if (! (lhs.getYear() == rhs.getYear()
      && lhs.getSemester() == rhs.getSemester()
      && lhs.getCourse().getId() == rhs.getCourse().getId()
      && lhs.getCourse().getTitle() == rhs.getCourse().getTitle()
      && lhs.getNumberSections() == rhs.getNumberSections()
      && lhs.getSectionListCapacity() == rhs.getSectionListCapacity())) {
  	return false;
  }

  // checking sections
  for (size_t i = 0; i < lhs.getNumberSections(); i++) {
  	Section ls = lhs.getSectionList()[i];
  	Section rs = rhs.getSectionList()[i];
  	if (!(ls.getId() == rs.getId()
	    	&& ls.getTime() == rs.getTime()
	    	&& ls.getLocation() == rs.getLocation()
	    	&& ls.getInstructor() == rs.getInstructor())) {
  		return false;
  	}
  }
  return true;
}
