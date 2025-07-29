#include "../include/utils.h"
#include <cstdlib>
#include <fstream>
#include <sstream>

namespace Utils {
// 用户数据
bool saveUsers(const std::string &filename, const std::vector<User *> &users) {
  std::ofstream ofs(filename);
  if (!ofs)
    return false;
  for (const auto &u : users) {
    ofs << u->getUserID() << ',' << u->getName() << ',' << u->getContact()
        << ',' << (int)u->getRole() << ',' << u->getRegisterTime() << ','
        << u->getLastLoginTime() << '\n';
  }
  return true;
}
bool loadUsers(const std::string &filename, std::vector<User *> &users) {
  std::ifstream ifs(filename);
  if (!ifs)
    return false;
  users.clear();
  std::string line;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    int id, roleInt;
    std::string name, contact;
    std::time_t reg, last;
    char comma;
    iss >> id >> comma;
    std::getline(iss, name, ',');
    std::getline(iss, contact, ',');
    iss >> roleInt >> comma >> reg >> comma >> last;
    UserRole role = static_cast<UserRole>(roleInt);
    if (role == UserRole::SuperAdmin) {
      auto p = new Admin(name, contact);
      p->setRole(role);
      users.push_back(p);
    } else if (role == UserRole::Teacher) {
      auto p = new Teacher(name, contact);
      p->setRole(role);
      users.push_back(p);
    } else if (role == UserRole::Student) {
      auto p = new Student(name, contact);
      p->setRole(role);
      users.push_back(p);
    }
    // 其他角色可扩展
  }
  return true;
}
// 课程数据
bool saveCourses(const std::string &filename,
                 const std::vector<Course *> &courses) {
  std::ofstream ofs(filename);
  if (!ofs)
    return false;
  for (const auto &c : courses) {
    ofs << c->getCourseID() << ',' << c->getName() << ',' << c->getDescription()
        << ',' << c->getPrice() << ',' << c->getHours() << ','
        << c->getDifficulty() << ',' << (int)c->getStatus() << '\n';
  }
  return true;
}
bool loadCourses(const std::string &filename, std::vector<Course *> &courses) {
  std::ifstream ifs(filename);
  if (!ifs)
    return false;
  courses.clear();
  std::string line;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    int id, hours, statusInt;
    double price;
    std::string name, desc, diff;
    char comma;
    iss >> id >> comma;
    std::getline(iss, name, ',');
    std::getline(iss, desc, ',');
    iss >> price >> comma >> hours >> comma;
    std::getline(iss, diff, ',');
    iss >> statusInt;
    // 分类信息和章节可扩展
    courses.push_back(new Course(name, desc, price, hours, diff, nullptr));
    courses.back()->setStatus(static_cast<CourseStatus>(statusInt));
  }
  return true;
}
// 学习记录
bool saveStudyRecords(const std::string &filename,
                      const std::vector<StudyRecord> &records) {
  std::ofstream ofs(filename);
  if (!ofs)
    return false;
  for (const auto &r : records) {
    ofs << r.getStudentID() << ',' << r.getCourseID() << ','
        << r.getStudyHours() << ',' << r.getStartTime() << ',' << r.getEndTime()
        << ',' << r.isCompleted() << '\n';
  }
  return true;
}
bool loadStudyRecords(const std::string &filename,
                      std::vector<StudyRecord> &records) {
  std::ifstream ifs(filename);
  if (!ifs)
    return false;
  records.clear();
  std::string line;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    int sid, cid, completedInt;
    double hours;
    std::time_t st, et;
    char comma;
    iss >> sid >> comma >> cid >> comma >> hours >> comma >> st >> comma >>
        et >> comma >> completedInt;
    StudyRecord rec(sid, cid);
    rec.addHours(hours);
    // 直接设置时间和完成状态
    // 需要友元或set方法，这里假设有setCompleted
    rec.setCompleted(completedInt != 0);
    records.push_back(rec);
  }
  return true;
}
// 课程评价
bool saveCourseReviews(const std::string &filename,
                       const std::vector<CourseReview> &reviews) {
  std::ofstream ofs(filename);
  if (!ofs)
    return false;
  for (const auto &r : reviews) {
    ofs << r.getStudentID() << ',' << r.getCourseID() << ',' << r.getRating()
        << ',' << r.getComment() << '\n';
  }
  return true;
}
bool loadCourseReviews(const std::string &filename,
                       std::vector<CourseReview> &reviews) {
  std::ifstream ifs(filename);
  if (!ifs)
    return false;
  reviews.clear();
  std::string line;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    int sid, cid, rating;
    std::string comment;
    char comma;
    iss >> sid >> comma >> cid >> comma >> rating >> comma;
    std::getline(iss, comment);
    reviews.emplace_back(sid, cid, rating, comment);
  }
  return true;
}
// 考试成绩
bool saveExamResults(const std::string &filename,
                     const std::vector<ExamResult> &results) {
  std::ofstream ofs(filename);
  if (!ofs)
    return false;
  for (const auto &r : results) {
    ofs << r.getExamID() << ',' << r.getStudentID() << ',' << r.getScore()
        << '\n';
  }
  return true;
}
bool loadExamResults(const std::string &filename,
                     std::vector<ExamResult> &results) {
  std::ifstream ifs(filename);
  if (!ifs)
    return false;
  results.clear();
  std::string line;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    int eid, sid;
    double score;
    char comma;
    iss >> eid >> comma >> sid >> comma >> score;
    results.emplace_back(eid, sid, score);
  }
  return true;
}
bool saveCategories(const std::string &filename,
                    const std::vector<CourseCategory *> &categories) {
  std::ofstream ofs(filename);
  if (!ofs)
    return false;
  for (const auto &cat : categories) {
    ofs << cat->getCategoryID() << ',' << cat->getName() << ','
        << cat->getDescription() << ',' << cat->getParentID() << '\n';
  }
  return true;
}
bool loadCategories(const std::string &filename,
                    std::vector<CourseCategory *> &categories) {
  std::ifstream ifs(filename);
  if (!ifs)
    return false;
  categories.clear();
  std::string line;
  while (std::getline(ifs, line)) {
    std::istringstream iss(line);
    int id, parentID;
    std::string name, desc;
    char comma;
    iss >> id >> comma;
    std::getline(iss, name, ',');
    std::getline(iss, desc, ',');
    iss >> parentID;
    categories.push_back(new CourseCategory(name, desc, parentID));
  }
  return true;
}
void clearScreen() { system("cls"); }
} // namespace Utils