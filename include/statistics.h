#ifndef STATISTICS_H
#define STATISTICS_H
#include "course.h"
#include "exam.h"
#include "study_record.h"
#include "user.h"
#include <vector>

class Statistics {
public:
  // 统计某课程的学习进度（已完成/总人数）
  static double
  calcCourseCompletionRate(int courseID,
                           const std::vector<StudyRecord> &records);
  // 统计学员活跃度（学习时长排名）
  static std::vector<std::pair<int, double>>
  calcStudentActivity(const std::vector<StudyRecord> &records);
  // 统计课程收入
  static double calcCourseIncome(int courseID,
                                 const std::vector<Course *> &courses,
                                 const std::vector<StudyRecord> &records);
  // 统计考试平均分
  static double calcExamAverageScore(int examID,
                                     const std::vector<ExamResult> &results);
};

#endif // STATISTICS_H