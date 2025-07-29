#ifndef COMMUNITY_H
#define COMMUNITY_H

#include <ctime>
#include <map>
#include <string>
#include <vector>


// 帖子类型
enum class PostType {
  Discussion,  // 讨论帖
  Question,    // 问答帖
  Answer,      // 回答帖
  Announcement // 公告帖
};

// 帖子类
class Post {
protected:
  int postID;
  int authorID;
  std::string authorName;
  std::string title;
  std::string content;
  PostType type;
  time_t createTime;
  time_t updateTime;
  int viewCount;
  int likeCount;
  int replyCount;
  bool isSticky;
  bool isClosed;
  std::vector<int> tags; // 标签ID列表

public:
  Post(int id, int author, const std::string &name, const std::string &t,
       const std::string &c, PostType pt);
  virtual ~Post() {}

  // Getters
  int getPostID() const { return postID; }
  int getAuthorID() const { return authorID; }
  std::string getAuthorName() const { return authorName; }
  std::string getTitle() const { return title; }
  std::string getContent() const { return content; }
  PostType getType() const { return type; }
  time_t getCreateTime() const { return createTime; }
  time_t getUpdateTime() const { return updateTime; }
  int getViewCount() const { return viewCount; }
  int getLikeCount() const { return likeCount; }
  int getReplyCount() const { return replyCount; }
  bool getIsSticky() const { return isSticky; }
  bool getIsClosed() const { return isClosed; }
  std::vector<int> getTags() const { return tags; }

  // Setters
  void setTitle(const std::string &t) {
    title = t;
    updateTime = time(nullptr);
  }
  void setContent(const std::string &c) {
    content = c;
    updateTime = time(nullptr);
  }
  void setSticky(bool sticky) { isSticky = sticky; }
  void setClosed(bool closed) { isClosed = closed; }
  void addTag(int tagID) { tags.push_back(tagID); }

  // 操作方法
  void incrementView() { viewCount++; }
  void incrementLike() { likeCount++; }
  void incrementReply() { replyCount++; }

  // 显示帖子信息
  virtual void displayInfo() const;
  virtual void displayContent() const;
};

// 问答帖类
class QuestionPost : public Post {
private:
  std::string courseName;
  int courseID;
  bool isResolved;
  int bestAnswerID;

public:
  QuestionPost(int id, int author, const std::string &name,
               const std::string &t, const std::string &c,
               const std::string &course, int cid);

  std::string getCourseName() const { return courseName; }
  int getCourseID() const { return courseID; }
  bool getIsResolved() const { return isResolved; }
  int getBestAnswerID() const { return bestAnswerID; }

  void setResolved(bool resolved) { isResolved = resolved; }
  void setBestAnswer(int answerID) { bestAnswerID = answerID; }

  void displayInfo() const override;
  void displayContent() const override;
};

// 回答帖类
class AnswerPost : public Post {
private:
  int questionID;
  bool isAccepted;

public:
  AnswerPost(int id, int author, const std::string &name, const std::string &t,
             const std::string &c, int qid);

  int getQuestionID() const { return questionID; }
  bool getIsAccepted() const { return isAccepted; }

  void setAccepted(bool accepted) { isAccepted = accepted; }

  void displayInfo() const override;
  void displayContent() const override;
};

// 社区管理类
class CommunityManager {
private:
  std::vector<Post *> posts;
  std::vector<QuestionPost *> questions;
  std::vector<AnswerPost *> answers;
  std::map<int, std::vector<int>> userPosts;       // 用户ID -> 帖子ID列表
  std::map<int, std::vector<int>> courseQuestions; // 课程ID -> 问题ID列表
  int nextPostID;

public:
  CommunityManager();
  ~CommunityManager();

  // 帖子管理
  Post *createPost(int authorID, const std::string &authorName,
                   const std::string &title, const std::string &content,
                   PostType type);
  QuestionPost *createQuestion(int authorID, const std::string &authorName,
                               const std::string &title,
                               const std::string &content,
                               const std::string &courseName, int courseID);
  AnswerPost *createAnswer(int authorID, const std::string &authorName,
                           const std::string &title, const std::string &content,
                           int questionID);

  // 查询功能
  std::vector<Post *> getPostsByType(PostType type);
  std::vector<Post *> getPostsByAuthor(int authorID);
  std::vector<QuestionPost *> getQuestionsByCourse(int courseID);
  std::vector<AnswerPost *> getAnswersByQuestion(int questionID);
  std::vector<Post *> searchPosts(const std::string &keyword);
  Post *getPostByID(int postID);

  // 管理功能
  void deletePost(int postID);
  void stickyPost(int postID, bool sticky);
  void closePost(int postID, bool close);
  void acceptAnswer(int answerID);

  // 统计功能
  int getTotalPosts() const { return posts.size(); }
  int getTotalQuestions() const { return questions.size(); }
  int getTotalAnswers() const { return answers.size(); }
  std::map<int, int> getUserPostCounts() const; // 用户发帖统计

  // 热门内容
  std::vector<Post *> getHotPosts(int limit = 10);
  std::vector<QuestionPost *> getUnresolvedQuestions(int limit = 10);
};

#endif