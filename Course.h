#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include "Date.h"
#include "AttendanceRecord.h"

class Course {
private:
  std::string id;
  std::string title;
  Date startTime;
  Date endTime;
  std::vector<AttendanceRecord> attendanceRecords;

public:
  Course(std::string id, std::string title, Date startTime, Date endTime);
  std::string getID() const {return id;}
  std::string getTitle() const {return title;}
  Date getStartTime() const {return startTime;}
  Date getEndTime() const {return endTime;}
  void addAttendanceRecord(AttendanceRecord ar);
  void outputAttendance(std::ostream& os) const;
  void outputAttendance(std::ostream& os, std::string student_id) const;
  bool operator==(const Course& rhs) const;
  std::vector<AttendanceRecord> getAttendanceRecords() const {return attendanceRecords;}

};

std::ostream& operator<<(std::ostream& os, const Course& c);
#endif
