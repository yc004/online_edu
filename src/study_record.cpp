#include "../include/study_record.h"
#include <ctime>

StudyRecord::StudyRecord(const int sid, const int cid)
    : studentID(sid), courseID(cid), studyHours(0), startTime(0), endTime(0),
      completed(false) {
}

void StudyRecord::startStudy() { startTime = std::time(nullptr); }

void StudyRecord::endStudy() {
    endTime = std::time(nullptr);
    if (startTime > 0 && endTime > startTime) {
        studyHours += (endTime - startTime) / 3600.0; // 秒转小时
    }
}

void StudyRecord::setCompleted(const bool c) { completed = c; }

void StudyRecord::addHours(const double h) { studyHours += h; }

int StudyRecord::getStudentID() const { return studentID; }
int StudyRecord::getCourseID() const { return courseID; }
double StudyRecord::getStudyHours() const { return studyHours; }
std::time_t StudyRecord::getStartTime() const { return startTime; }
std::time_t StudyRecord::getEndTime() const { return endTime; }
bool StudyRecord::isCompleted() const { return completed; }
