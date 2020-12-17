#include <iostream>
#include <sstream>
#include <string>
#include "Student.h"

using std::cout, std::endl;

Student::Student(std::string student_id, std::string name) {
  this->id = student_id;
  this->name = name;
}
void Student::addCourse(std::string course_id) {
  for (long unsigned int i = 0; i < this->course_ids.size(); ++i) {
    if (course_id == this->course_ids.at(i)) {
      throw std::invalid_argument("Course already exists in vector");
    }
  }
  this->course_ids.push_back(course_id);
}
void Student::listCourses(std::ostream& os) const {
  os << "Courses for " << this->id << std::endl;
  if(this->course_ids.size() == 0) {
    os << "No courses" << std::endl;
  }
  for (long unsigned int i = 0; i < this->course_ids.size(); ++i) {
    os << this->course_ids.at(i) << endl;
  }
}
std::string Student::get_id() const {
  std::stringstream ss;
  ss << this->id;
  return ss.str();
}
std::string Student::get_name() const {
  std::stringstream ss;
  ss << this->name;
  return ss.str();
}
std::ostream& operator<<(std::ostream& os, const Student& s) {
  return os << s.get_id() << "," << s.get_name();
}

// int main() {
//   Student nayab("528000730","Nayab");
//   nayab.addCourse("CSCE 121");
//   nayab.addCourse("CSCE 181");
//   nayab.addCourse("CSCE 222");
//   nayab.addCourse("ATMO 201");
//   nayab.addCourse("ATMO 202");
//   nayab.addCourse("GEOG 203");
//
//   nayab.listCourses(std::cout);
//   return 0;
// }
