#ifndef STUDY_RECORD_H
#define STUDY_RECORD_H
#include <string>
#include <ctime>

class StudyRecord {
private:
    int studentID;
    int courseID;
    double studyHours;
    std::time_t startTime;
    std::time_t endTime;
    bool completed;
public:
    StudyRecord(int sid, int cid);
    void startStudy();
    void endStudy();
    void setCompleted(bool c);
    void addHours(double h);
    int getStudentID() const;
    int getCourseID() const;
    double getStudyHours() const;
    std::time_t getStartTime() const;
    std::time_t getEndTime() const;
    bool isCompleted() const;
};

#endif // STUDY_RECORD_H 