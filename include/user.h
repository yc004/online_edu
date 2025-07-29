#ifndef USER_H
#define USER_H
#include <ctime>
#include <string>
#include <vector>

// 用户角色枚举
enum class UserRole { SuperAdmin, CourseAdmin, Teacher, Student };

// 用户基类
class User {
protected:
  static int nextID;
  int userID;
  std::string name;
  std::string contact;
  UserRole role;
  std::time_t registerTime;
  std::time_t lastLoginTime;

public:
  User(const std::string &n, const std::string &contact);
  virtual ~User() {}
  int getUserID() const;
  std::string getName() const;
  std::string getContact() const;
  UserRole getRole() const;
  std::time_t getRegisterTime() const;
  std::time_t getLastLoginTime() const;
  void setLastLoginTime(std::time_t t);
  void setName(const std::string &n) { name = n; }
  void setContact(const std::string &c) { contact = c; }
  void setRole(UserRole r) { role = r; }
  virtual void showMenu() = 0; // 纯虚函数，不同角色菜单不同
};

// 管理员类
class Admin : public User {
public:
  Admin(const std::string &n, const std::string &contact) : User(n, contact) {
    role = UserRole::SuperAdmin;
  }
  void showMenu() override;
};

// 教师类
class Teacher : public User {
public:
  Teacher(const std::string &n, const std::string &contact) : User(n, contact) {
    role = UserRole::Teacher;
  }
  void showMenu() override;
};

// 学员类
class Student : public User {
public:
  Student(const std::string &n, const std::string &contact) : User(n, contact) {
    role = UserRole::Student;
  }
  void showMenu() override;
};

#endif // USER_H
