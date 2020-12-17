
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::endl, std::cout;
Course::Course(string id, string title, Date startTime, Date endTime) : startTime(startTime), endTime(endTime) {
  this->id = id;
  this->title = title;
  // this->startTime = startTime;
  // this->endTime = endTime;
}

bool Course::operator==(const Course& rhs) const{

  return this->id == rhs.id && this->title == rhs.title && startTime >= rhs.startTime && endTime >= rhs.endTime && startTime <= rhs.startTime && endTime <= rhs.endTime;
}

void Course::addAttendanceRecord(AttendanceRecord ar) {
  if ((getStartTime() <= ar.getDate()) && (ar.getDate() <= getEndTime())){
    this->attendanceRecords.push_back(ar);
  } else {
    throw std::invalid_argument("time is invalid");
  }
}

void Course::outputAttendance(std::ostream& os, std::string student_id) const {
  if (this->attendanceRecords.size() == 0) {
    os << "No records" << endl;
    return;
  }
  bool idValid = false;
  for (unsigned int i = 0; i < this->attendanceRecords.size(); ++i) {
    if (student_id == this->attendanceRecords[i].getStudentID()) {
      idValid = true;
      os << this->attendanceRecords[i].getDate().getDateTime() << ",";
      os << this->attendanceRecords[i].getCourseID() << ",";
      os << this->attendanceRecords[i].getStudentID() << endl;
    }
  }
  if (idValid == false) {
    os << "No records" << endl;
  }
}

void Course::outputAttendance(std::ostream& os) const {
  if (this->attendanceRecords.size() == 0) {
    os << "No records" << endl;
    return;
  }
//  bool idValid = false;
  for (unsigned int i = 0; i < this->attendanceRecords.size(); ++i) {
    // if (student_id == this->attendanceRecords[i].getStudentID()) {
    //   idValid = true;
      os << this->attendanceRecords[i].getDate().getDateTime() << ",";
      os << this->attendanceRecords[i].getCourseID() << ",";
      os << this->attendanceRecords[i].getStudentID() << endl;
    //}
  }
  // if (idValid == false) {
  //   os << "No records" << endl;
  // }
}

// vector<AttendanceRecord> Course::getAttendanceRecords() const {
//   // return this->attendanceRecords;
// }

std::ostream& operator<<(std::ostream& os, const Course& c) {
  return os << c.getID() << "," << c.getStartTime() << "," << c.getEndTime() << "," << c.getTitle();

}
