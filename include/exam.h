#ifndef EXAM_H
#define EXAM_H
#include <string>
#include <vector>

class Exam {
private:
  int examID;
  int courseID;
  std::string title;

public:
  Exam(int eid, int cid, const std::string &t);
  int getExamID() const;
  int getCourseID() const;
  std::string getTitle() const;
};

class ExamResult {
private:
  int examID;
  int studentID;
  double score;

public:
  ExamResult(int eid, int sid, double s);
  int getExamID() const;
  int getStudentID() const;
  double getScore() const;
};

#endif // EXAM_H