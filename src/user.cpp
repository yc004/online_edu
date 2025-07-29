#include "../include/user.h"
#include <iostream>

int User::nextID = 1000;

User::User(const std::string &n, const std::string &contact)
    : userID(nextID++), name(n), contact(contact) {
    registerTime = std::time(nullptr);
    lastLoginTime = registerTime;
}

int User::getUserID() const { return userID; }
std::string User::getName() const { return name; }
std::string User::getContact() const { return contact; }
UserRole User::getRole() const { return role; }
std::time_t User::getRegisterTime() const { return registerTime; }
std::time_t User::getLastLoginTime() const { return lastLoginTime; }
void User::setLastLoginTime(std::time_t t) { lastLoginTime = t; }

void Admin::showMenu() {
    std::cout << "\n--- 管理员菜单 ---\n";
    std::cout << "1. 课程分类管理\n2. 课程管理\n3. 用户管理\n4. 权限管理\n5. "
            "数据统计\n6. 退出\n";
}

void Teacher::showMenu() {
    std::cout << "\n--- 教师菜单 ---\n";
    std::cout << "1. 我的课程\n2. 发布课程\n3. 学员管理\n4. 退出\n";
}

void Student::showMenu() {
    std::cout << "\n--- 学员菜单 ---\n";
    std::cout
            << "1. 课程浏览与搜索\n2. 我的学习\n3. 我的考试\n4. 个人中心\n5. 退出\n";
}
