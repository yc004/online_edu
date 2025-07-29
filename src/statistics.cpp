#include "../include/statistics.h"
#include <algorithm>
#include <map>

// 统计某课程的学习进度（已完成/总人数）
double
Statistics::calcCourseCompletionRate(const int courseID,
                                     const std::vector<StudyRecord> &records) {
    int total = 0, completed = 0;
    for (const auto &rec: records) {
        if (rec.getCourseID() == courseID) {
            ++total;
            if (rec.isCompleted())
                ++completed;
        }
    }
    return total > 0 ? static_cast<double>(completed) / total : 0.0;
}

// 统计学员活跃度（学习时长排名，返回<学员ID, 总时长>，按时长降序）
std::vector<std::pair<int, double> >
Statistics::calcStudentActivity(const std::vector<StudyRecord> &records) {
    std::map<int, double> activity;
    for (const auto &rec: records) {
        activity[rec.getStudentID()] += rec.getStudyHours();
    }
    std::vector<std::pair<int, double> > result(activity.begin(), activity.end());
    std::sort(result.begin(), result.end(),
              [](const auto &a, const auto &b) { return a.second > b.second; });
    return result;
}

// 统计课程收入（假设每个完成学习的学员都付费一次）
double Statistics::calcCourseIncome(const int courseID,
                                    const std::vector<Course *> &courses,
                                    const std::vector<StudyRecord> &records) {
    double price = 0.0;
    for (const auto &c: courses) {
        if (c->getCourseID() == courseID) {
            price = c->getPrice();
            break;
        }
    }
    int count = 0;
    for (const auto &rec: records) {
        if (rec.getCourseID() == courseID && rec.isCompleted()) {
            ++count;
        }
    }
    return price * count;
}

// 统计考试平均分
double
Statistics::calcExamAverageScore(const int examID,
                                 const std::vector<ExamResult> &results) {
    double sum = 0.0;
    int cnt = 0;
    for (const auto &r: results) {
        if (r.getExamID() == examID) {
            sum += r.getScore();
            ++cnt;
        }
    }
    return cnt > 0 ? sum / cnt : 0.0;
}
