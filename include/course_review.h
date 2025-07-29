#ifndef COURSE_REVIEW_H
#define COURSE_REVIEW_H
#include <string>

class CourseReview {
private:
  int studentID;
  int courseID;
  int rating; // 1-5分
  std::string comment;

public:
  CourseReview(int sid, int cid, int r, const std::string &cmt);
  int getStudentID() const;
  int getCourseID() const;
  int getRating() const;
  std::string getComment() const;
};

#endif // COURSE_REVIEW_H