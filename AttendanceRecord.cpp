#include <string>
#include <iostream>
#include "AttendanceRecord.h"
#include "Date.h"

using std::cout, std::endl;
using std::string, std::ifstream;
using std::istringstream, std::stringstream;

AttendanceRecord::AttendanceRecord(std::string course_id, std::string student_id, Date time) :course_id(course_id), student_id(student_id), time(time)  { //try this method of time(time) from zybooks it should fix the error

}
