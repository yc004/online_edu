#ifndef UTILS_H
#define UTILS_H
#include "course.h"
#include "course_review.h"
#include "exam.h"
#include "study_record.h"
#include "user.h"
#include <string>
#include <vector>

namespace Utils {
// 用户数据
bool saveUsers(const std::string &filename, const std::vector<User *> &users);
bool loadUsers(const std::string &filename, std::vector<User *> &users);
// 课程数据
bool saveCourses(const std::string &filename,
                 const std::vector<Course *> &courses);
bool loadCourses(const std::string &filename, std::vector<Course *> &courses);
// 学习记录
bool saveStudyRecords(const std::string &filename,
                      const std::vector<StudyRecord> &records);
bool loadStudyRecords(const std::string &filename,
                      std::vector<StudyRecord> &records);
// 课程评价
bool saveCourseReviews(const std::string &filename,
                       const std::vector<CourseReview> &reviews);
bool loadCourseReviews(const std::string &filename,
                       std::vector<CourseReview> &reviews);
// 考试成绩
bool saveExamResults(const std::string &filename,
                     const std::vector<ExamResult> &results);
bool loadExamResults(const std::string &filename,
                     std::vector<ExamResult> &results);
// 课程分类
bool saveCategories(const std::string &filename,
                    const std::vector<CourseCategory *> &categories);
bool loadCategories(const std::string &filename,
                    std::vector<CourseCategory *> &categories);
void clearScreen();
} // namespace Utils

#endif // UTILS_H