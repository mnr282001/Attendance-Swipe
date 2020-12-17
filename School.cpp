#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "School.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::ifstream, std::istringstream, std::endl, std::cout;

// one method is provided to students; students implement all other methods
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
bool School::isEnrolled(std::string student_id) const {
  for(long unsigned int i = 0; i < students.size(); ++i) {
    if(students[i].get_id() == student_id) {
      return true;
    }
  }
  return false;
}
void School::listStudents(std::ostream& os) const {
  if (students.size() == 0) {
    os << "No students" << std::endl;
    return;
  }
  for(long unsigned int i = 0; i < students.size(); ++i) {
    os << students[i].get_id() << "," << students[i].get_name() << std::endl;
  }
}
void School::listCourses(std::ostream& os) const {
  if (this->courses.size() > 0) {
    for (size_t i =0; i < this->courses.size(); ++i) {
      os << this->courses[i].getID() << ",";
      os << this->courses[i].getStartTime().getTime(false) << ",";
      os << this->courses[i].getEndTime().getTime(false) << ",";
      os << this->courses[i].getTitle() << endl;
    }
  } else {
    os << "No courses" << endl;
  }
}
void School::addCourses(std::string filename) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("error in opening the file");
  }
  string line;
  while (getline(ifs,line)) {
    istringstream iss(line);
    string cID;
    getline(iss, cID, ',');
    string startHr;
    getline(iss, startHr, ':');
    string startMin;
    getline(iss,startMin, ',');
    //use stoi to convert int
    Date startTiming(stoi(startHr), stoi(startMin));
    string endHr;
    getline(iss, endHr, ':');
    string endMin;
    getline(iss,endMin, ',');
    //use stoi to convert int
    Date endTiming(stoi(endHr), stoi(endMin));
    string titleCourse;
    getline(iss,titleCourse);
    Course course(cID, titleCourse, startTiming, endTiming);
    this->courses.push_back(course);
  }
}
unsigned int School::addAttendanceData(std::string filename) {
    ifstream ifs(filename);
    if(!ifs.is_open()) {
        throw std::invalid_argument("addCourses: can't open file");
    }
    string line;
    int incorrectNumber = 0;
    while (getline(ifs, line)) {
        istringstream iss(line);
        string yr;
        getline(iss, yr, '-');
        string mth;
        getline(iss, mth, '-');
        string dy;
        getline(iss, dy, ' ');
        string hr;
        getline(iss, hr, ':');
        string min;
        getline(iss, min, ':');
        string sec;
        getline(iss, sec, ',');
        Date time(stoi(yr), stoi(mth), stoi(dy), stoi(hr), stoi(min), stoi(sec));
        if (time.isValid() == false) {
            ++incorrectNumber;
            continue;
        }
        bool showsUp = false;
        int correctCourse = 0;
        string id2;
        getline(iss, id2, ',');
        for (size_t i = 0; i < this->courses.size();i++) {
            if (this->courses[i].getID() == id2) {
                showsUp = true;
                correctCourse = i;
            }
        }
        if (showsUp == false) {
            ++incorrectNumber;
            continue;
        }
        bool showsUp2 = false;
        string stuID;
        getline(iss, stuID);
        for(size_t i = 0; i < this->students.size(); i++) {
            if (this->students[i].get_id() == stuID) {
                showsUp2 = true;
            }
        }
        if (showsUp2 == false) {
            ++incorrectNumber;
            continue;
        }
        try {
            AttendanceRecord ar(id2, stuID, time);
            this->courses[correctCourse].addAttendanceRecord(ar);

        } catch(std::invalid_argument()) {
        }
    }
    return incorrectNumber;
}

void School::outputCourseAttendance(std::ostream& os, std::string course_id) const {
    bool qualify =false;
    for (size_t i = 0; i < this->courses.size(); i++) {
        if (this->courses[i].getID() == course_id) {
            qualify = true;
            if (this->courses[i].getAttendanceRecords().size() > 0) {
                this->courses[i].outputAttendance(os);
            }
        }
    }
    if (qualify == false) {
        os << "No records." << endl;
        throw std::invalid_argument("course is not found");
    }
}

void School::outputStudentAttendance(std::ostream& os, std::string student_id, std::string course_id) const {
    bool qualify = false;
    for (size_t i = 0; i < this->courses.size(); i++) {
        if (this->courses[i].getID() == course_id) {
            qualify = true;
            if (this->courses[i].getAttendanceRecords().size() > 0) {
                this->courses[i].outputAttendance(os, student_id);
            }
        }
    }
    if (qualify == false) {
        os << "No records." << endl;
        throw std::invalid_argument("course is not found");//----------------------------------------------------------------------
    }
}
