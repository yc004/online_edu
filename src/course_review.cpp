#include "../include/course_review.h"

CourseReview::CourseReview(const int sid, const int cid, const int r,
                           const std::string &cmt)
    : studentID(sid), courseID(cid), rating(r), comment(cmt) {}

int CourseReview::getStudentID() const { return studentID; }
int CourseReview::getCourseID() const { return courseID; }
int CourseReview::getRating() const { return rating; }
std::string CourseReview::getComment() const { return comment; }
