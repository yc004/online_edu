#ifndef COURSE_H
#define COURSE_H
#include "course_category.h"
#include <string>
#include <vector>

// 课程状态枚举
enum class CourseStatus { Draft, UnderReview, Published, Unlisted };

// 课程章节
struct CourseChapter {
  int chapterID;
  std::string title;
  std::string content;
};

// 课程类
class Course {
protected:
  static int nextID;
  int courseID;
  std::string name;
  std::string description;
  double price;
  int hours;
  std::string difficulty;
  CourseStatus status;
  CourseCategory *category;
  std::vector<CourseChapter> chapters;

public:
  Course(const std::string &n, const std::string &desc, double p, int h,
         const std::string &diff, CourseCategory *cat);
  virtual ~Course() {}
  int getCourseID() const;
  std::string getName() const;
  std::string getDescription() const;
  double getPrice() const;
  int getHours() const;
  std::string getDifficulty() const;
  CourseStatus getStatus() const;
  CourseCategory *getCategory() const;
  const std::vector<CourseChapter> &getChapters() const;
  void setStatus(CourseStatus s);
  void addChapter(const CourseChapter &chapter);
  virtual void showInfo() const;
  void setName(const std::string &n) { name = n; }
  void setDescription(const std::string &d) { description = d; }
  void setPrice(double p) { price = p; }
  void setHours(int h) { hours = h; }
  void setDifficulty(const std::string &d) { difficulty = d; }
  void setCategory(CourseCategory *c) { category = c; }
};

#endif // COURSE_H