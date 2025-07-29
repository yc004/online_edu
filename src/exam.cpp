#include "../include/exam.h"

Exam::Exam(const int eid, const int cid, const std::string &t)
    : examID(eid), courseID(cid), title(t) {}

int Exam::getExamID() const { return examID; }
int Exam::getCourseID() const { return courseID; }
std::string Exam::getTitle() const { return title; }

ExamResult::ExamResult(const int eid, const int sid, const double s)
    : examID(eid), studentID(sid), score(s) {}

int ExamResult::getExamID() const { return examID; }
int ExamResult::getStudentID() const { return studentID; }
double ExamResult::getScore() const { return score; }
