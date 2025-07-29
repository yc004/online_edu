#include "../include/community.h"
#include "../include/course.h"
#include "../include/course_category.h"
#include "../include/course_review.h"
#include "../include/exam.h"
#include "../include/recommendation.h"
#include "../include/statistics.h"
#include "../include/study_record.h"
#include "../include/user.h"
#include "../include/utils.h"
#include <direct.h>
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

// 模板类：通用容器
template<typename T>
class DataContainer {
private:
    std::vector<T> data;
    static int totalCount; // 静态成员
public:
    void add(const T &item) {
        data.push_back(item);
        totalCount++;
    }

    T &get(int index) { return data[index]; }
    int size() const { return data.size(); }
    static int getTotalCount() { return totalCount; }

    // 运算符重载
    DataContainer<T> &operator+=(const T &item) {
        add(item);
        return *this;
    }

    T &operator[](int index) { return data[index]; }
};

template<typename T>
int DataContainer<T>::totalCount = 0;

// 使用模板类
DataContainer<Course *> courseContainer;
DataContainer<User *> userContainer;

void showWelcome() {
    std::cout << "*欢迎您使用在线教育平台系统*\n";
    std::cout << "*1) 管理员\n*2) 用户\n*3) 退出系统\n";
    std::cout << "*请选择登录用户类型[1-3]: ";
}

// 管理员功能：课程分类管理
void adminCategoryManage(std::vector<CourseCategory *> &categories);

// 课程管理功能实现
void adminCourseManage(std::vector<Course *> &courses,
                       const std::vector<CourseCategory *> &categories);

// 用户管理功能实现
void adminUserManage(std::vector<User *> &users);

// 权限管理功能实现
void adminPermissionManage(std::vector<User *> &users);

// 数据统计功能实现
void adminStatistics(std::vector<Course *> &courses,
                     std::vector<StudyRecord> &studyRecords);

// 学员主菜单功能实现
void studentMenu(int studentID, std::vector<Course *> &courses,
                 std::vector<StudyRecord> &studyRecords,
                 std::vector<CourseReview> &reviews,
                 std::vector<ExamResult> &examResults) {
    int choice = 0;
    // 推荐系统和社区管理对象
    static RecommendationSystem recommender;
    static CommunityManager community;
    do {
        Utils::clearScreen();
        std::cout << "\n--- 学员菜单 ---\n";
        std::cout << "1. 课程浏览与搜索\n2. 我的学习\n3. 我的考试\n4. 个人中心\n5. "
                "学习推荐\n6. 社区\n7. 退出\n请选择[1-7]: ";
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "\n所有课程：\n";
            for (const auto &c: courses)
                c->showInfo();
        } else if (choice == 2) {
            int subChoice = 0;
            do {
                std::cout << "\n--- 我的学习 ---\n";
                std::cout << "1. 查看已购课程\n2. 录入学习进度\n3. 录入课程评价\n4. "
                        "学习统计\n5. 返回\n请选择[1-5]: ";
                std::cin >> subChoice;
                if (subChoice == 1) {
                    std::cout << "\n已购课程：\n";
                    for (const auto &r: studyRecords) {
                        if (r.getStudentID() == studentID) {
                            for (const auto &c: courses) {
                                if (c->getCourseID() == r.getCourseID()) {
                                    c->showInfo();
                                }
                            }
                        }
                    }
                } else if (subChoice == 2) {
                    int cid;
                    std::cout << "请输入课程ID: ";
                    std::cin >> cid;
                    for (auto &r: studyRecords) {
                        if (r.getStudentID() == studentID && r.getCourseID() == cid) {
                            std::cout << "输入学习开始时间(秒,可随意): ";
                            std::time_t st;
                            std::cin >> st; // 实际可用当前时间
                            r.startStudy();
                            std::cout << "输入学习结束时间(秒,可随意): ";
                            std::time_t et;
                            std::cin >> et;
                            r.endStudy();
                            int completed;
                            std::cout << "是否完成(1/0): ";
                            std::cin >> completed;
                            r.setCompleted(completed != 0);
                            std::cout << "录入完成！\n";
                        }
                    }
                } else if (subChoice == 3) {
                    int cid, rating;
                    std::string comment;
                    std::cout << "请输入课程ID: ";
                    std::cin >> cid;
                    std::cout << "请输入评分(1-5): ";
                    std::cin >> rating;
                    std::cout << "请输入评价: ";
                    std::cin >> comment;
                    reviews.emplace_back(studentID, cid, rating, comment);
                    std::cout << "评价录入成功！\n";
                } else if (subChoice == 4) {
                    double totalHours = 0;
                    int count = 0;
                    for (const auto &r: studyRecords) {
                        if (r.getStudentID() == studentID) {
                            totalHours += r.getStudyHours();
                            count++;
                        }
                    }
                    std::cout << "已学课程数: " << count << ", 总学习时长: " << totalHours
                            << " 小时\n";
                } else if (subChoice == 5) {
                    break;
                } else {
                    std::cout << "无效选择！\n";
                }
            } while (subChoice != 5);
        } else if (choice == 3) {
            int subChoice = 0;
            do {
                std::cout << "\n--- 我的考试 ---\n";
                std::cout << "1. 查看考试列表\n2. 录入考试成绩\n3. 考试统计\n4. "
                        "返回\n请选择[1-4]: ";
                std::cin >> subChoice;
                if (subChoice == 1) {
                    std::cout << "\n考试列表：\n";
                    // 这里可以显示该学员可以参加的考试
                    std::cout << "考试ID: 1, 课程: C++基础, 标题: 期末考试\n";
                    std::cout << "考试ID: 2, 课程: 数据结构, 标题: 期中考试\n";
                } else if (subChoice == 2) {
                    int examID;
                    double score;
                    std::cout << "请输入考试ID: ";
                    std::cin >> examID;
                    std::cout << "请输入考试成绩: ";
                    std::cin >> score;
                    std::cout << "成绩录入成功！\n";
                } else if (subChoice == 3) {
                    std::cout << "考试统计：\n";
                    double totalScore = 0;
                    int count = 0;
                    for (const auto &r: examResults) {
                        if (r.getStudentID() == studentID) {
                            totalScore += r.getScore();
                            count++;
                        }
                    }
                    if (count > 0) {
                        std::cout << "已参加考试数: " << count << std::endl;
                        std::cout << "平均分: " << (totalScore / count) << std::endl;
                    } else {
                        std::cout << "暂无考试记录\n";
                    }
                } else if (subChoice == 4) {
                    break;
                } else {
                    std::cout << "无效选择！\n";
                }
            } while (subChoice != 4);
        } else if (choice == 4) {
            int subChoice = 0;
            do {
                std::cout << "\n--- 个人中心 ---\n";
                std::cout << "1. 我的信息\n2. 消费记录\n3. 充值\n4. 修改密码\n5. "
                        "返回\n请选择[1-5]: ";
                std::cin >> subChoice;
                if (subChoice == 1) {
                    std::cout << "\n个人信息：\n";
                    std::cout << "学员ID: " << studentID << std::endl;
                    std::cout << "姓名: 张三\n";
                    std::cout << "联系方式: zhangsan@edu.com\n";
                    std::cout << "注册时间: 2024-01-01\n";
                    std::cout << "最后登录: 2024-01-15\n";
                } else if (subChoice == 2) {
                    std::cout << "\n消费记录：\n";
                    std::cout << "2024-01-10 购买C++基础课程 ￥99.00\n";
                    std::cout << "2024-01-12 购买数据结构课程 ￥129.00\n";
                    std::cout << "总消费: ￥228.00\n";
                } else if (subChoice == 3) {
                    double amount;
                    std::cout << "请输入充值金额: ";
                    std::cin >> amount;
                    std::cout << "充值成功！当前余额: ￥" << (100 + amount) << std::endl;
                } else if (subChoice == 4) {
                    std::string oldPwd, newPwd;
                    std::cout << "请输入原密码: ";
                    std::cin >> oldPwd;
                    std::cout << "请输入新密码: ";
                    std::cin >> newPwd;
                    std::cout << "密码修改成功！\n";
                } else if (subChoice == 5) {
                    break;
                } else {
                    std::cout << "无效选择！\n";
                }
            } while (subChoice != 5);
        } else if (choice == 5) {
            // 学习推荐功能演示
            recommender.analyzeUserInterest(studentID, studyRecords, reviews);
            auto recCourses = recommender.recommendCoursesByHistory(
                studentID, studyRecords, courses, 3);
            std::cout << "\n【为你推荐的课程】\n";
            for (auto c: recCourses) {
                c->showInfo();
            }
            auto recPaths =
                    recommender.recommendLearningPaths(studentID, studyRecords, 2);
            std::cout << "\n【为你推荐的学习路径】\n";
            for (const auto &path: recPaths) {
                std::cout << "路径: " << path.pathName << "，简介: " << path.description
                        << std::endl;
            }
            system("pause");
        } else if (choice == 6) {
            // 社区功能演示
            int cOpt = 0;
            do {
                Utils::clearScreen();
                std::cout << "\n--- 学员社区 ---\n";
                std::cout << "1. 查看讨论帖\n2. 发帖\n3. 返回\n请选择[1-3]: ";
                std::cin >> cOpt;
                if (cOpt == 1) {
                    auto posts = community.getPostsByType(PostType::Discussion);
                    std::cout << "\n【讨论区帖子列表】\n";
                    for (auto p: posts)
                        p->displayInfo();
                    system("pause");
                } else if (cOpt == 2) {
                    std::string title, content;
                    std::cout << "标题: ";
                    std::cin >> title;
                    std::cout << "内容: ";
                    std::cin >> content;
                    community.createPost(studentID, "学员", title, content,
                                         PostType::Discussion);
                    std::cout << "发帖成功！\n";
                    system("pause");
                } else if (cOpt == 3) {
                    break;
                }
            } while (cOpt != 3);
        } else if (choice == 7) {
            break;
        } else {
            std::cout << "无效选择！\n";
        }
    } while (choice != 7);
}

// 教师主菜单功能实现
void teacherMenu(int teacherID, std::vector<Course *> &courses,
                 std::vector<StudyRecord> &studyRecords) {
    int choice = 0;
    do {
        std::cout << "\n--- 教师菜单 ---\n";
        std::cout
                << "1. 我的课程\n2. 发布课程\n3. 学员管理\n4. 退出\n请选择[1-4]: ";
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "\n我的课程：\n";
            for (const auto &c: courses) {
                // 这里可以按教师ID筛选课程
                c->showInfo();
            }
        } else if (choice == 2) {
            std::cout << "\n发布课程功能：\n";
            std::cout << "课程发布功能已集成到管理员课程管理中\n";
        } else if (choice == 3) {
            std::cout << "\n学员管理：\n";
            std::cout << "查看学习进度、成绩等\n";
            for (const auto &r: studyRecords) {
                std::cout << "学员ID: " << r.getStudentID()
                        << ", 课程ID: " << r.getCourseID()
                        << ", 学习时长: " << r.getStudyHours()
                        << " 小时, 完成: " << (r.isCompleted() ? "是" : "否")
                        << std::endl;
            }
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "无效选择！\n";
        }
    } while (choice != 4);
}

int main() {
    // 设置控制台编码为UTF-8，解决中文乱码问题
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // 自动创建data文件夹
    _mkdir("data");
    std::vector<User *> users;
    std::vector<Course *> courses;
    std::vector<CourseCategory *> categories;
    std::vector<StudyRecord> studyRecords;
    std::vector<CourseReview> reviews;
    std::vector<ExamResult> examResults;
    // 启动时加载数据
    if (!Utils::loadUsers("data/users.csv", users)) {
        std::cout << "未找到用户数据，使用默认用户。\n";
        users.push_back(new Admin("超级管理员", "admin@edu.com"));
        users.push_back(new Student("张三", "zhangsan@edu.com"));
        users.push_back(new Teacher("李老师", "li@edu.com"));
    }
    if (!Utils::loadCourses("data/courses.csv", courses)) {
        std::cout << "未找到课程数据，课程列表为空。\n";
    }
    if (!Utils::loadCategories("data/categories.csv", categories)) {
        std::cout << "未找到课程分类数据，分类列表为空。\n";
    }
    if (!Utils::loadStudyRecords("data/study_records.csv", studyRecords)) {
        std::cout << "未找到学习记录数据，记录列表为空。\n";
    }
    if (!Utils::loadCourseReviews("data/reviews.csv", reviews)) {
        std::cout << "未找到课程评价数据，评价列表为空。\n";
    }
    if (!Utils::loadExamResults("data/exam_results.csv", examResults)) {
        std::cout << "未找到考试成绩数据，成绩列表为空。\n";
    }

    int choice = 0;
    while (true) {
        // 登录前显示所有用户信息
        std::cout << "\n系统已加载用户：\n";
        for (auto u: users) {
            std::cout << "用户名: " << u->getName() << "，邮箱: " << u->getContact()
                    << std::endl;
        }
        showWelcome();
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "请输入管理员用户名: ";
            std::string username;
            std::cin >> username;
            bool found = false;
            for (auto u: users) {
                if ((u->getName() == username || u->getContact() == username) &&
                    (u->getRole() == UserRole::SuperAdmin ||
                     u->getRole() == UserRole::CourseAdmin)) {
                    std::cout << "欢迎管理员：" << u->getName() << std::endl;
                    // 管理员功能主循环
                    int adminChoice = 0;
                    do {
                        u->showMenu();
                        std::cout << "请选择功能[1-6]: ";
                        std::cin >> adminChoice;
                        switch (adminChoice) {
                            case 1:
                                adminCategoryManage(categories);
                                break;
                            case 2:
                                adminCourseManage(courses, categories);
                                break;
                            case 3:
                                adminUserManage(users);
                                break;
                            case 4:
                                adminPermissionManage(users);
                                break;
                            case 5:
                                adminStatistics(courses, studyRecords);
                                break;
                            case 6:
                                std::cout << "退出管理员菜单\n";
                                break;
                            default:
                                std::cout << "无效选择，请重新输入！\n";
                        }
                    } while (adminChoice != 6);
                    found = true;
                    break;
                }
            }
            if (!found)
                std::cout << "管理员不存在！\n";
        } else if (choice == 2) {
            std::cout << "请输入用户名: ";
            std::string username;
            std::cin >> username;
            bool found = false;
            for (auto u: users) {
                if ((u->getName() == username || u->getContact() == username) &&
                    (u->getRole() == UserRole::Student ||
                     u->getRole() == UserRole::Teacher)) {
                    std::cout << "欢迎用户：" << u->getName() << std::endl;
                    if (u->getRole() == UserRole::Student) {
                        studentMenu(u->getUserID(), courses, studyRecords, reviews,
                                    examResults);
                    } else {
                        teacherMenu(u->getUserID(), courses, studyRecords);
                    }
                    found = true;
                    break;
                }
            }
            if (!found)
                std::cout << "用户不存在！\n";
        } else if (choice == 3) {
            std::cout << "感谢使用，再见！\n";
            break;
        } else {
            std::cout << "无效选择，请重新输入！\n";
        }
    }
    // 退出时保存数据
    Utils::saveUsers("data/users.csv", users);
    Utils::saveCourses("data/courses.csv", courses);
    Utils::saveCategories("data/categories.csv", categories);
    Utils::saveStudyRecords("data/study_records.csv", studyRecords);
    Utils::saveCourseReviews("data/reviews.csv", reviews);
    Utils::saveExamResults("data/exam_results.csv", examResults);
    // 释放内存
    for (auto u: users)
        delete u;
    for (auto c: courses)
        delete c;
    for (auto cat: categories)
        delete cat;
    return 0;
}

// 课程分类管理功能实现（后续补充具体操作）
void adminCategoryManage(std::vector<CourseCategory *> &categories) {
    int choice = 0;
    do {
        std::cout << "\n--- 课程分类管理 ---\n";
        std::cout << "1. 查看所有分类\n2. 新增分类\n3. 修改分类\n4. 删除分类\n5. "
                "返回上级菜单\n请选择[1-5]: ";
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "\n所有课程分类：\n";
            for (const auto &cat: categories) {
                std::cout << "ID: " << cat->getCategoryID()
                        << ", 名称: " << cat->getName()
                        << ", 描述: " << cat->getDescription()
                        << ", 父ID: " << cat->getParentID() << std::endl;
            }
        } else if (choice == 2) {
            int parentID;
            std::string name, desc;
            std::cout << "请输入分类名称: ";
            std::cin >> name;
            std::cout << "请输入分类描述: ";
            std::cin >> desc;
            std::cout << "请输入父分类ID(顶级为-1): ";
            std::cin >> parentID;
            categories.push_back(new CourseCategory(name, desc, parentID));
            std::cout << "添加成功！\n";
        } else if (choice == 3) {
            // 修改分类前，先输出所有分类信息
            std::cout << "\n所有课程分类：\n";
            for (const auto &cat: categories) {
                std::cout << "ID: " << cat->getCategoryID()
                        << ", 名称: " << cat->getName()
                        << ", 描述: " << cat->getDescription()
                        << ", 父ID: " << cat->getParentID() << std::endl;
            }
            int id;
            std::cout << "请输入要修改的分类ID: ";
            std::cin >> id;
            bool found = false;
            for (auto &cat: categories) {
                if (cat->getCategoryID() == id) {
                    std::string name, desc;
                    std::cout << "新名称: ";
                    std::cin >> name;
                    std::cout << "新描述: ";
                    std::cin >> desc;
                    cat->setName(name);
                    cat->setDescription(desc);
                    std::cout << "修改成功！\n";
                    found = true;
                    break;
                }
            }
            if (!found)
                std::cout << "未找到该分类！\n";
        } else if (choice == 4) {
            int id;
            std::cout << "请输入要删除的分类ID: ";
            std::cin >> id;
            bool found = false;
            for (auto it = categories.begin(); it != categories.end(); ++it) {
                if ((*it)->getCategoryID() == id) {
                    delete *it;
                    categories.erase(it);
                    std::cout << "删除成功！\n";
                    found = true;
                    break;
                }
            }
            if (!found)
                std::cout << "未找到该分类！\n";
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "无效选择！\n";
        }
    } while (choice != 5);
}

// 课程管理功能实现
void adminCourseManage(std::vector<Course *> &courses,
                       const std::vector<CourseCategory *> &categories) {
    int choice = 0;
    do {
        std::cout << "\n--- 课程管理 ---\n";
        std::cout << "1. 查看所有课程\n2. 新增课程\n3. 修改课程\n4. 删除课程\n5. "
                "章节管理\n6. 返回上级菜单\n请选择[1-6]: ";
        std::cin >> choice;
        if (choice == 1) {
            for (const auto &c: courses)
                c->showInfo();
        } else if (choice == 2) {
            // 新增课程前，先输出所有课程分类信息
            std::cout << "\n所有课程分类：\n";
            for (const auto &cat: categories) {
                std::cout << "ID: " << cat->getCategoryID()
                        << ", 名称: " << cat->getName()
                        << ", 描述: " << cat->getDescription()
                        << ", 父ID: " << cat->getParentID() << std::endl;
            }
            int hours, catID;
            double price;
            std::string name, desc, diff;
            std::cout << "名称: ";
            std::cin >> name;
            std::cout << "描述: ";
            std::cin >> desc;
            std::cout << "价格: ";
            std::cin >> price;
            std::cout << "课时: ";
            std::cin >> hours;
            std::cout << "难度: ";
            std::cin >> diff;
            std::cout << "分类ID: ";
            std::cin >> catID;
            CourseCategory *cat = nullptr;
            for (auto c: categories)
                if (c->getCategoryID() == catID)
                    cat = c;
            courses.push_back(new Course(name, desc, price, hours, diff, cat));
            Utils::saveCourses("data/courses.csv", courses);
            std::cout << "添加成功！\n";
        } else if (choice == 3) {
            // 修改课程前，先输出所有课程信息
            std::cout << "\n所有课程：\n";
            for (const auto &c: courses)
                c->showInfo();
            int id;
            std::cout << "要修改的课程ID: ";
            std::cin >> id;
            bool found = false;
            for (auto &c: courses) {
                if (c->getCourseID() == id) {
                    std::string name, desc, diff;
                    int hours, catID;
                    double price;
                    std::cout << "新名称: ";
                    std::cin >> name;
                    std::cout << "新描述: ";
                    std::cin >> desc;
                    std::cout << "新价格: ";
                    std::cin >> price;
                    std::cout << "新课时: ";
                    std::cin >> hours;
                    std::cout << "新难度: ";
                    std::cin >> diff;
                    std::cout << "新分类ID: ";
                    std::cin >> catID;
                    c->setName(name);
                    c->setDescription(desc);
                    c->setPrice(price);
                    c->setHours(hours);
                    c->setDifficulty(diff);
                    for (auto cc: categories)
                        if (cc->getCategoryID() == catID)
                            c->setCategory(cc);
                    std::cout << "修改成功！\n";
                    found = true;
                    break;
                }
            }
            if (!found)
                std::cout << "未找到该课程！\n";
        } else if (choice == 4) {
            int id;
            std::cout << "要删除的课程ID: ";
            std::cin >> id;
            bool found = false;
            for (auto it = courses.begin(); it != courses.end(); ++it) {
                if ((*it)->getCourseID() == id) {
                    delete *it;
                    courses.erase(it);
                    std::cout << "删除成功！\n";
                    found = true;
                    break;
                }
            }
            if (!found)
                std::cout << "未找到该课程！\n";
        } else if (choice == 5) {
            int id;
            std::cout << "请输入课程ID: ";
            std::cin >> id;
            Course *course = nullptr;
            for (auto c: courses)
                if (c->getCourseID() == id)
                    course = c;
            if (!course) {
                std::cout << "未找到该课程！\n";
                continue;
            }
            int chChoice = 0;
            do {
                std::cout << "\n--- 章节管理 ---\n";
                std::cout << "1. 查看章节\n2. 新增章节\n3. 返回课程管理\n请选择[1-3]: ";
                std::cin >> chChoice;
                if (chChoice == 1) {
                    for (const auto &ch: course->getChapters()) {
                        std::cout << "章节ID: " << ch.chapterID << ", 标题: " << ch.title
                                << ", 内容: " << ch.content << std::endl;
                    }
                } else if (chChoice == 2) {
                    int chid;
                    std::string title, content;
                    std::cout << "章节ID: ";
                    std::cin >> chid;
                    std::cout << "标题: ";
                    std::cin >> title;
                    std::cout << "内容: ";
                    std::cin >> content;
                    course->addChapter({chid, title, content});
                    std::cout << "添加成功！\n";
                } else if (chChoice == 3) {
                    break;
                } else {
                    std::cout << "无效选择！\n";
                }
            } while (chChoice != 3);
        } else if (choice == 6) {
            break;
        } else {
            std::cout << "无效选择！\n";
        }
    } while (choice != 6);
}

// 用户管理功能实现
void adminUserManage(std::vector<User *> &users) {
    int choice = 0;
    do {
        std::cout << "\n--- 用户管理 ---\n";
        std::cout << "1. 查看所有用户\n2. 新增用户\n3. 修改用户\n4. 删除用户\n5. "
                "返回上级菜单\n请选择[1-5]: ";
        std::cin >> choice;
        if (choice == 1) {
            for (const auto &u: users) {
                std::cout << "ID: " << u->getUserID() << ", 姓名: " << u->getName()
                        << ", 联系方式: " << u->getContact()
                        << ", 角色: " << (int) u->getRole() << std::endl;
            }
        } else if (choice == 2) {
            std::string name, contact;
            int roleInt;
            std::cout << "姓名: ";
            std::cin >> name;
            std::cout << "联系方式: ";
            std::cin >> contact;
            std::cout << "角色(0-超级管理员,1-课程管理员,2-教师,3-学员): ";
            std::cin >> roleInt;
            UserRole role = static_cast<UserRole>(roleInt);
            if (role == UserRole::SuperAdmin)
                users.push_back(new Admin(name, contact));
            else if (role == UserRole::Teacher)
                users.push_back(new Teacher(name, contact));
            else if (role == UserRole::Student)
                users.push_back(new Student(name, contact));
            else
                users.push_back(new Admin(name, contact));
            std::cout << "添加成功！\n";
        } else if (choice == 3) {
            // 修改用户前，先输出所有用户信息
            std::cout << "\n所有用户：\n";
            for (const auto &u: users) {
                std::cout << "ID: " << u->getUserID() << ", 姓名: " << u->getName()
                        << ", 联系方式: " << u->getContact()
                        << ", 角色: " << (int) u->getRole() << std::endl;
            }
            int id;
            std::cout << "要修改的用户ID: ";
            std::cin >> id;
            bool found = false;
            for (auto &u: users) {
                if (u->getUserID() == id) {
                    std::string name, contact;
                    int roleInt;
                    std::cout << "新姓名: ";
                    std::cin >> name;
                    std::cout << "新联系方式: ";
                    std::cin >> contact;
                    std::cout << "新角色(0-超级管理员,1-课程管理员,2-教师,3-学员): ";
                    std::cin >> roleInt;
                    u->setName(name);
                    u->setContact(contact);
                    u->setRole(static_cast<UserRole>(roleInt));
                    std::cout << "修改成功！\n";
                    found = true;
                    break;
                }
            }
            if (!found)
                std::cout << "未找到该用户！\n";
        } else if (choice == 4) {
            int id;
            std::cout << "要删除的用户ID: ";
            std::cin >> id;
            bool found = false;
            for (auto it = users.begin(); it != users.end(); ++it) {
                if ((*it)->getUserID() == id) {
                    delete *it;
                    users.erase(it);
                    std::cout << "删除成功！\n";
                    found = true;
                    break;
                }
            }
            if (!found)
                std::cout << "未找到该用户！\n";
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "无效选择！\n";
        }
    } while (choice != 5);
}

// 权限管理功能实现
void adminPermissionManage(std::vector<User *> &users) {
    int choice = 0;
    do {
        std::cout << "\n--- 权限管理 ---\n";
        std::cout
                << "1. 查看用户权限\n2. 修改用户角色\n3. 返回上级菜单\n请选择[1-3]: ";
        std::cin >> choice;
        if (choice == 1) {
            for (const auto &u: users) {
                std::cout << "ID: " << u->getUserID() << ", 姓名: " << u->getName()
                        << ", 角色: ";
                switch (u->getRole()) {
                    case UserRole::SuperAdmin:
                        std::cout << "超级管理员";
                        break;
                    case UserRole::CourseAdmin:
                        std::cout << "课程管理员";
                        break;
                    case UserRole::Teacher:
                        std::cout << "教师";
                        break;
                    case UserRole::Student:
                        std::cout << "学员";
                        break;
                }
                std::cout << std::endl;
            }
        } else if (choice == 2) {
            int id, roleInt;
            std::cout << "请输入用户ID: ";
            std::cin >> id;
            std::cout << "新角色(0-超级管理员,1-课程管理员,2-教师,3-学员): ";
            std::cin >> roleInt;
            UserRole role = static_cast<UserRole>(roleInt);
            bool found = false;
            for (auto &u: users) {
                if (u->getUserID() == id) {
                    std::string name = u->getName();
                    std::string contact = u->getContact();
                    delete u;
                    if (role == UserRole::SuperAdmin)
                        u = new Admin(name, contact);
                    else if (role == UserRole::Teacher)
                        u = new Teacher(name, contact);
                    else if (role == UserRole::Student)
                        u = new Student(name, contact);
                    else
                        u = new Admin(name, contact);
                    std::cout << "角色修改成功！\n";
                    found = true;
                    break;
                }
            }
            if (!found)
                std::cout << "未找到该用户！\n";
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "无效选择！\n";
        }
    } while (choice != 3);
}

// 数据统计功能实现
void adminStatistics(std::vector<Course *> &courses,
                     std::vector<StudyRecord> &studyRecords) {
    int choice = 0;
    do {
        std::cout << "\n--- 数据统计 ---\n";
        std::cout << "1. 课程学习进度统计\n2. 用户活跃度分析\n3. 课程收入统计\n4. "
                "返回上级菜单\n请选择[1-4]: ";
        std::cin >> choice;
        if (choice == 1) {
            for (const auto &c: courses) {
                double rate = Statistics::calcCourseCompletionRate(c->getCourseID(),
                                                                   studyRecords);
                std::cout << "课程: " << c->getName() << " 完成率: " << (rate * 100)
                        << "%\n";
            }
        } else if (choice == 2) {
            auto activity = Statistics::calcStudentActivity(studyRecords);
            std::cout << "学员活跃度(学员ID:总时长):\n";
            for (const auto &p: activity) {
                std::cout << p.first << ": " << p.second << " 小时\n";
            }
        } else if (choice == 3) {
            for (const auto &c: courses) {
                double income = Statistics::calcCourseIncome(c->getCourseID(), courses,
                                                             studyRecords);
                std::cout << "课程: " << c->getName() << " 收入: " << income << " 元\n";
            }
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "无效选择！\n";
        }
    } while (choice != 4);
}
