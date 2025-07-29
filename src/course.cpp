#include "../include/course.h"
#include <iostream>

int Course::nextID = 1;

Course::Course(const std::string &n, const std::string &desc, double p, int h,
               const std::string &diff, CourseCategory *cat)
    : courseID(nextID++), name(n), description(desc), price(p), hours(h),
      difficulty(diff), status(CourseStatus::Draft), category(cat) {}

int Course::getCourseID() const { return courseID; }
std::string Course::getName() const { return name; }
std::string Course::getDescription() const { return description; }
double Course::getPrice() const { return price; }
int Course::getHours() const { return hours; }
std::string Course::getDifficulty() const { return difficulty; }
CourseStatus Course::getStatus() const { return status; }
CourseCategory *Course::getCategory() const { return category; }

const std::vector<CourseChapter> &Course::getChapters() const {
  return chapters;
}

void Course::setStatus(CourseStatus s) { status = s; }

void Course::addChapter(const CourseChapter &chapter) {
  chapters.push_back(chapter);
}

void Course::showInfo() const {
  std::cout << "课程ID: " << courseID << "\n名称: " << name
            << "\n描述: " << description << "\n价格: " << price
            << "\n课时: " << hours << "\n难度: " << difficulty << "\n状态: ";
  switch (status) {
  case CourseStatus::Draft:
    std::cout << "草稿";
    break;
  case CourseStatus::UnderReview:
    std::cout << "审核中";
    break;
  case CourseStatus::Published:
    std::cout << "已发布";
    break;
  case CourseStatus::Unlisted:
    std::cout << "已下架";
    break;
  }
  std::cout << "\n分类: " << (category ? category->getName() : "无")
            << "\n章节数: " << chapters.size() << std::endl;
}
