#ifndef FACTORY_H
#define FACTORY_H
#include <string>

class Course;
class CourseCategory;

class CourseFactory {
public:
  // 工厂方法：根据类型创建课程对象
  static Course *createCourse(int id, const std::string &name,
                              const std::string &desc, double price, int hours,
                              const std::string &diff, CourseCategory *cat,
                              const std::string &type);
};

#endif // FACTORY_H
