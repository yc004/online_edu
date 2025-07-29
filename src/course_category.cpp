#include "../include/course_category.h"

int CourseCategory::nextID = 1;

CourseCategory::CourseCategory(const std::string &name, const std::string &desc,
                               int parentID)
    : categoryID(nextID++), name(name), description(desc), parentID(parentID) {}

CourseCategory::~CourseCategory() {
  for (auto sub : subCategories) {
    delete sub;
  }
}

int CourseCategory::getCategoryID() const { return categoryID; }
std::string CourseCategory::getName() const { return name; }
std::string CourseCategory::getDescription() const { return description; }
int CourseCategory::getParentID() const { return parentID; }
void CourseCategory::addSubCategory(CourseCategory *subCat) {
  subCategories.push_back(subCat);
}
const std::vector<CourseCategory *> &CourseCategory::getSubCategories() const {
  return subCategories;
}