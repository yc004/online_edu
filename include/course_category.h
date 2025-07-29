#ifndef COURSE_CATEGORY_H
#define COURSE_CATEGORY_H
#include <string>
#include <vector>

class CourseCategory {
private:
  static int nextID;
  int categoryID;
  std::string name;
  std::string description;
  int parentID; // 父分类ID，顶级为-1
  std::vector<CourseCategory *> subCategories;

public:
  CourseCategory(const std::string &name, const std::string &desc,
                 int parentID = -1);
  ~CourseCategory();
  int getCategoryID() const;
  std::string getName() const;
  std::string getDescription() const;
  int getParentID() const;
  void addSubCategory(CourseCategory *subCat);
  const std::vector<CourseCategory *> &getSubCategories() const;
  void setName(const std::string &n) { name = n; }
  void setDescription(const std::string &d) { description = d; }
};

#endif // COURSE_CATEGORY_H