#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include "course.h"
#include "course_review.h"
#include "study_record.h"
#include <map>
#include <string>
#include <vector>

// 学习兴趣标签
struct InterestTag {
  int tagID;
  std::string tagName;
  double weight; // 兴趣权重
};

// 学习路径
struct LearningPath {
  int pathID;
  std::string pathName;
  std::string description;
  std::vector<int> courseSequence; // 课程ID序列
  double difficulty;               // 难度等级
  int estimatedHours;              // 预计学习时长
};

// 推荐系统类
class RecommendationSystem {
private:
  std::vector<InterestTag> interestTags;
  std::vector<LearningPath> learningPaths;
  std::map<int, std::vector<int>> userInterests; // 用户ID -> 兴趣标签ID列表
  std::map<int, std::vector<double>> userPreferences; // 用户ID -> 偏好权重

public:
  RecommendationSystem();

  // 初始化推荐系统数据
  void initializeData();

  // 基于学习历史推荐课程
  static std::vector<Course *> recommendCoursesByHistory(
      int userID, const std::vector<StudyRecord> &studyRecords,
      const std::vector<Course *> &allCourses, int limit = 5);

  // 基于兴趣推荐课程
  std::vector<Course *> recommendCoursesByInterest(
      int userID, const std::vector<Course *> &allCourses, int limit = 5);

  // 推荐学习路径
  std::vector<LearningPath> recommendLearningPaths(
      int userID, const std::vector<StudyRecord> &studyRecords, int limit = 3) const;

  // 分析用户兴趣
  void analyzeUserInterest(int userID,
                           const std::vector<StudyRecord> &studyRecords,
                           const std::vector<CourseReview> &reviews);

  // 添加用户兴趣标签
  void addUserInterest(int userID, int tagID, double weight = 1.0);

  // 获取用户兴趣标签
  std::vector<InterestTag> getUserInterests(int userID);

  // 计算课程相似度
  static double calculateCourseSimilarity(const Course *course1,
                                          const Course *course2);

  // 计算用户与课程的匹配度
  double calculateUserCourseMatch(int userID, const Course *course);
};

#endif