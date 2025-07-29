#include "../include/recommendation.h"
#include <algorithm>
#include <cmath>
#include <iostream>

RecommendationSystem::RecommendationSystem() { initializeData(); }

void RecommendationSystem::initializeData() {
  // 初始化兴趣标签
  interestTags = {{1, "编程基础", 1.0}, {2, "数据结构", 1.0},
                  {3, "算法设计", 1.0}, {4, "面向对象", 1.0},
                  {5, "数据库", 1.0},   {6, "网络编程", 1.0},
                  {7, "前端开发", 1.0}, {8, "后端开发", 1.0},
                  {9, "移动开发", 1.0}, {10, "人工智能", 1.0}};

  // 初始化学习路径
  learningPaths = {
      {1, "C++开发工程师", "从零开始学习C++编程", {1, 2, 3, 4}, 3.5, 200},
      {2, "Web全栈开发", "前后端一体化开发", {1, 7, 8, 5}, 4.0, 300},
      {3, "算法工程师", "算法与数据结构专精", {2, 3, 10}, 4.5, 250},
      {4, "移动应用开发", "移动端开发技能", {1, 9, 6}, 3.0, 180}};
}

std::vector<Course *> RecommendationSystem::recommendCoursesByHistory(
    const int userID, const std::vector<StudyRecord> &studyRecords,
    const std::vector<Course *> &allCourses, const int limit) {

  std::vector<Course *> recommendations;
  std::map<int, double> courseScores;

  // 获取用户已学习的课程
  std::vector<int> learnedCourses;
  for (const auto &record : studyRecords) {
    if (record.getStudentID() == userID) {
      learnedCourses.push_back(record.getCourseID());
    }
  }

  // 为每个未学习的课程计算推荐分数
  for (const auto &course : allCourses) {
    if (std::find(learnedCourses.begin(), learnedCourses.end(),
                  course->getCourseID()) == learnedCourses.end()) {

      double score = 0.0;

      // 基于已学课程的相似度计算分数
      for (const int learnedID : learnedCourses) {
        for (const auto &otherCourse : allCourses) {
          if (otherCourse->getCourseID() == learnedID) {
            score += calculateCourseSimilarity(course, otherCourse);
            break;
          }
        }
      }

      courseScores[course->getCourseID()] = score;
    }
  }

  // 按分数排序并返回前limit个推荐
  std::vector<std::pair<int, double>> sortedScores(courseScores.begin(),
                                                   courseScores.end());
  std::sort(sortedScores.begin(), sortedScores.end(),
            [](const auto &a, const auto &b) { return a.second > b.second; });

  for (int i = 0; i < std::min(limit, static_cast<int>(sortedScores.size())); ++i) {
    for (const auto &course : allCourses) {
      if (course->getCourseID() == sortedScores[i].first) {
        recommendations.push_back(course);
        break;
      }
    }
  }

  return recommendations;
}

std::vector<Course *> RecommendationSystem::recommendCoursesByInterest(
    const int userID, const std::vector<Course *> &allCourses, int limit) {

  std::vector<Course *> recommendations;
  std::map<int, double> courseScores;

  // 计算每个课程与用户兴趣的匹配度
  for (const auto &course : allCourses) {
    const double matchScore = calculateUserCourseMatch(userID, course);
    courseScores[course->getCourseID()] = matchScore;
  }

  // 按匹配度排序并返回前limit个推荐
  std::vector<std::pair<int, double>> sortedScores(courseScores.begin(),
                                                   courseScores.end());
  std::sort(sortedScores.begin(), sortedScores.end(),
            [](const auto &a, const auto &b) { return a.second > b.second; });

  for (int i = 0; i < std::min(limit, static_cast<int>(sortedScores.size())); ++i) {
    for (const auto &course : allCourses) {
      if (course->getCourseID() == sortedScores[i].first) {
        recommendations.push_back(course);
        break;
      }
    }
  }

  return recommendations;
}

std::vector<LearningPath> RecommendationSystem::recommendLearningPaths(
    const int userID, const std::vector<StudyRecord> &studyRecords, const int limit) const {

  std::vector<LearningPath> recommendations;
  std::map<int, double> pathScores;

  // 获取用户已学习的课程
  std::vector<int> learnedCourses;
  for (const auto &record : studyRecords) {
    if (record.getStudentID() == userID) {
      learnedCourses.push_back(record.getCourseID());
    }
  }

  // 为每个学习路径计算推荐分数
  for (const auto &path : learningPaths) {
    double score = 0.0;
    int completedCourses = 0;

    // 计算路径完成度
    for (int courseID : path.courseSequence) {
      if (std::find(learnedCourses.begin(), learnedCourses.end(), courseID) !=
          learnedCourses.end()) {
        completedCourses++;
      }
    }

    // 完成度越高，推荐分数越高
    score = static_cast<double>(completedCourses) / path.courseSequence.size();

    // 考虑路径难度与用户水平的匹配
    const double userLevel =
        static_cast<double>(learnedCourses.size()) / 10.0; // 简化的用户水平计算
    score *= (1.0 - std::abs(path.difficulty - userLevel) / 5.0);

    pathScores[path.pathID] = score;
  }

  // 按分数排序并返回前limit个推荐
  std::vector<std::pair<int, double>> sortedScores(pathScores.begin(),
                                                   pathScores.end());
  std::sort(sortedScores.begin(), sortedScores.end(),
            [](const auto &a, const auto &b) { return a.second > b.second; });

  for (int i = 0; i < std::min(limit, static_cast<int>(sortedScores.size())); ++i) {
    for (const auto &path : learningPaths) {
      if (path.pathID == sortedScores[i].first) {
        recommendations.push_back(path);
        break;
      }
    }
  }

  return recommendations;
}

void RecommendationSystem::analyzeUserInterest(
    const int userID, const std::vector<StudyRecord> &studyRecords,
    const std::vector<CourseReview> &reviews) {

  // 基于学习记录分析兴趣
  for (const auto &record : studyRecords) {
    if (record.getStudentID() == userID) {
      // 根据学习时长和完成情况推断兴趣
      if (record.getStudyHours() > 10 && record.isCompleted()) {
        // 假设课程ID对应兴趣标签ID（简化处理）
        const int tagID = (record.getCourseID() % 10) + 1;
        addUserInterest(userID, tagID, record.getStudyHours() / 10.0);
      }
    }
  }

  // 基于评价分析兴趣
  for (const auto &review : reviews) {
    if (review.getStudentID() == userID && review.getRating() >= 4) {
      const int tagID = (review.getCourseID() % 10) + 1;
      addUserInterest(userID, tagID, review.getRating() / 5.0);
    }
  }
}

void RecommendationSystem::addUserInterest(const int userID, const int tagID,
                                           const double weight) {
  userInterests[userID].push_back(tagID);
  userPreferences[userID].push_back(weight);
}

std::vector<InterestTag> RecommendationSystem::getUserInterests(const int userID) {
  std::vector<InterestTag> interests;

  if (userInterests.find(userID) != userInterests.end()) {
    const auto &tagIDs = userInterests[userID];
    const auto &weights = userPreferences[userID];

    for (size_t i = 0; i < tagIDs.size(); ++i) {
      for (const auto &tag : interestTags) {
        if (tag.tagID == tagIDs[i]) {
          InterestTag userTag = tag;
          userTag.weight = weights[i];
          interests.push_back(userTag);
          break;
        }
      }
    }
  }

  return interests;
}

double RecommendationSystem::calculateCourseSimilarity(const Course *course1,
                                                       const Course *course2) {
  double similarity = 0.0;

  // 基于分类的相似度
  if (course1->getCategory() && course2->getCategory() &&
      course1->getCategory()->getCategoryID() ==
          course2->getCategory()->getCategoryID()) {
    similarity += 0.5;
  }

  // 基于难度的相似度
  if (course1->getDifficulty() == course2->getDifficulty()) {
    similarity += 0.3;
  }

  // 基于价格的相似度
  double priceDiff = std::abs(course1->getPrice() - course2->getPrice());
  double maxPrice = std::max(course1->getPrice(), course2->getPrice());
  if (maxPrice > 0) {
    similarity += (1.0 - priceDiff / maxPrice) * 0.2;
  }

  return similarity;
}

double RecommendationSystem::calculateUserCourseMatch(int userID,
                                                      const Course *course) {
  double matchScore = 0.0;

  // 获取用户兴趣
  auto interests = getUserInterests(userID);

  // 基于兴趣标签计算匹配度
  for (const auto &interest : interests) {
    // 简化的匹配逻辑：根据课程ID和兴趣标签ID的关系
    if (course->getCourseID() % 10 == interest.tagID - 1) {
      matchScore += interest.weight;
    }
  }

  // 考虑课程难度与用户水平的匹配
  double userLevel = interests.size() * 0.5; // 简化的用户水平
  // 简化难度匹配逻辑
  if (course->getDifficulty() == "初级" && userLevel < 2.0) {
    matchScore *= 1.2;
  } else if (course->getDifficulty() == "中级" && userLevel >= 2.0 &&
             userLevel < 4.0) {
    matchScore *= 1.2;
  } else if (course->getDifficulty() == "高级" && userLevel >= 4.0) {
    matchScore *= 1.2;
  }

  return matchScore;
}