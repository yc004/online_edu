#include "../include/factory.h"
#include "../include/course.h"
#include <iostream>

// 这里可以根据type扩展不同课程子类
Course *CourseFactory::createCourse(int id, const std::string &name,
                                    const std::string &desc, double price,
                                    const int hours, const std::string &diff,
                                    CourseCategory *cat,
                                    const std::string &type) {
  // 目前只有基础Course类，可扩展如VideoCourse、LiveCourse等
  if (type == "base" || type == "Course") {
    return new Course(name, desc, price, hours, diff, cat);
  }
  // 其他类型可扩展
  std::cerr << "未知课程类型: " << type << std::endl;
  return nullptr;
}