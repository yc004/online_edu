#include "../include/community.h"
#include <algorithm>
#include <iomanip>
#include <iostream>

// Post类实现
Post::Post(const int id, const int author, const std::string &name,
           const std::string &t, const std::string &c, const PostType pt)
    : postID(id), authorID(author), authorName(name), title(t), content(c),
      type(pt), createTime(time(nullptr)), updateTime(time(nullptr)),
      viewCount(0), likeCount(0), replyCount(0), isSticky(false),
      isClosed(false) {
}

void Post::displayInfo() const {
    std::cout << "【" << postID << "】" << (isSticky ? "[置顶]" : "")
            << (isClosed ? "[已关闭]" : "") << " " << title << std::endl;
    std::cout << "作者: " << authorName << " | 浏览: " << viewCount
            << " | 点赞: " << likeCount << " | 回复: " << replyCount
            << std::endl;
}

void Post::displayContent() const {
    std::cout << "\n=== " << title << " ===" << std::endl;
    time_t t = createTime;
    std::cout << "作者: " << authorName << " | 发布时间: " << std::ctime(&t);
    std::cout << "浏览: " << viewCount << " | 点赞: " << likeCount
            << " | 回复: " << replyCount << std::endl;
    std::cout << "\n" << content << std::endl;
}

// QuestionPost类实现
QuestionPost::QuestionPost(const int id, const int author,
                           const std::string &name, const std::string &t,
                           const std::string &c, const std::string &course,
                           const int cid)
    : Post(id, author, name, t, c, PostType::Question), courseName(course),
      courseID(cid), isResolved(false), bestAnswerID(-1) {
}

void QuestionPost::displayInfo() const {
    std::cout << "【" << getPostID() << "】" << (getIsSticky() ? "[置顶]" : "")
            << (getIsClosed() ? "[已关闭]" : "")
            << (isResolved ? "[已解决]" : "[未解决]") << " " << getTitle()
            << std::endl;
    std::cout << "作者: " << getAuthorName() << " | 课程: " << courseName
            << " | 浏览: " << getViewCount() << " | 回复: " << getReplyCount()
            << std::endl;
}

void QuestionPost::displayContent() const {
    std::cout << "\n=== " << getTitle() << " ===" << std::endl;
    const time_t t = getCreateTime();
    std::cout << "作者: " << getAuthorName() << " | 课程: " << courseName
            << " | 发布时间: " << std::ctime(&t);
    std::cout << "状态: " << (isResolved ? "已解决" : "未解决") << std::endl;
    std::cout << "浏览: " << getViewCount() << " | 回复: " << getReplyCount()
            << std::endl;
    std::cout << "\n" << getContent() << std::endl;
}

// AnswerPost类实现
AnswerPost::AnswerPost(const int id, const int author, const std::string &name,
                       const std::string &t, const std::string &c, int qid)
    : Post(id, author, name, t, c, PostType::Answer), questionID(qid),
      isAccepted(false) {
}

void AnswerPost::displayInfo() const {
    std::cout << "【" << getPostID() << "】" << (isAccepted ? "[最佳答案]" : "")
            << " " << getTitle() << std::endl;
    std::cout << "作者: " << getAuthorName() << " | 点赞: " << getLikeCount();
    time_t t = getCreateTime();
    std::cout << " | 回复时间: " << std::ctime(&t);
}

void AnswerPost::displayContent() const {
    std::cout << "\n=== " << getTitle() << " ===" << std::endl;
    std::cout << "作者: " << getAuthorName();
    time_t t = getCreateTime();
    std::cout << " | 回复时间: " << std::ctime(&t);
    std::cout << "状态: " << (isAccepted ? "最佳答案" : "普通回答") << std::endl;
    std::cout << "点赞: " << getLikeCount() << std::endl;
    std::cout << "\n" << getContent() << std::endl;
}

// CommunityManager类实现
CommunityManager::CommunityManager() : nextPostID(1) {
}

CommunityManager::~CommunityManager() {
    for (auto post: posts) {
        delete post;
    }
    for (auto question: questions) {
        delete question;
    }
    for (auto answer: answers) {
        delete answer;
    }
}

Post *CommunityManager::createPost(int authorID, const std::string &authorName,
                                   const std::string &title,
                                   const std::string &content, PostType type) {
    Post *post =
            new Post(nextPostID++, authorID, authorName, title, content, type);
    posts.push_back(post);
    userPosts[authorID].push_back(post->getPostID());
    return post;
}

QuestionPost *CommunityManager::createQuestion(
    int authorID, const std::string &authorName, const std::string &title,
    const std::string &content, const std::string &courseName, int courseID) {
    QuestionPost *question = new QuestionPost(
        nextPostID++, authorID, authorName, title, content, courseName, courseID);
    questions.push_back(question);
    posts.push_back(question);
    userPosts[authorID].push_back(question->getPostID());
    courseQuestions[courseID].push_back(question->getPostID());
    return question;
}

AnswerPost *CommunityManager::createAnswer(int authorID,
                                           const std::string &authorName,
                                           const std::string &title,
                                           const std::string &content,
                                           int questionID) {
    AnswerPost *answer = new AnswerPost(nextPostID++, authorID, authorName, title,
                                        content, questionID);
    answers.push_back(answer);
    posts.push_back(answer);
    userPosts[authorID].push_back(answer->getPostID());

    // 更新问题回复数
    for (auto question: questions) {
        if (question->getPostID() == questionID) {
            question->incrementReply();
            break;
        }
    }

    return answer;
}

std::vector<Post *> CommunityManager::getPostsByType(PostType type) {
    std::vector<Post *> result;
    for (auto post: posts) {
        if (post->getType() == type) {
            result.push_back(post);
        }
    }
    return result;
}

std::vector<Post *> CommunityManager::getPostsByAuthor(int authorID) {
    std::vector<Post *> result;
    for (auto post: posts) {
        if (post->getAuthorID() == authorID) {
            result.push_back(post);
        }
    }
    return result;
}

std::vector<QuestionPost *>
CommunityManager::getQuestionsByCourse(int courseID) {
    std::vector<QuestionPost *> result;
    for (auto question: questions) {
        if (question->getCourseID() == courseID) {
            result.push_back(question);
        }
    }
    return result;
}

std::vector<AnswerPost *>
CommunityManager::getAnswersByQuestion(int questionID) {
    std::vector<AnswerPost *> result;
    for (auto answer: answers) {
        if (answer->getQuestionID() == questionID) {
            result.push_back(answer);
        }
    }
    return result;
}

std::vector<Post *> CommunityManager::searchPosts(const std::string &keyword) {
    std::vector<Post *> result;
    for (auto post: posts) {
        if (post->getTitle().find(keyword) != std::string::npos ||
            post->getContent().find(keyword) != std::string::npos) {
            result.push_back(post);
        }
    }
    return result;
}

Post *CommunityManager::getPostByID(int postID) {
    for (auto post: posts) {
        if (post->getPostID() == postID) {
            return post;
        }
    }
    return nullptr;
}

void CommunityManager::deletePost(int postID) {
    for (auto it = posts.begin(); it != posts.end(); ++it) {
        if ((*it)->getPostID() == postID) {
            delete *it;
            posts.erase(it);
            break;
        }
    }
}

void CommunityManager::stickyPost(int postID, bool sticky) {
    Post *post = getPostByID(postID);
    if (post) {
        post->setSticky(sticky);
    }
}

void CommunityManager::closePost(int postID, bool close) {
    Post *post = getPostByID(postID);
    if (post) {
        post->setClosed(close);
    }
}

void CommunityManager::acceptAnswer(int answerID) {
    for (auto answer: answers) {
        if (answer->getPostID() == answerID) {
            answer->setAccepted(true);

            // 更新对应问题状态
            for (auto question: questions) {
                if (question->getPostID() == answer->getQuestionID()) {
                    question->setResolved(true);
                    question->setBestAnswer(answerID);
                    break;
                }
            }
            break;
        }
    }
}

std::map<int, int> CommunityManager::getUserPostCounts() const {
    std::map<int, int> counts;
    for (const auto &pair: userPosts) {
        counts[pair.first] = pair.second.size();
    }
    return counts;
}

std::vector<Post *> CommunityManager::getHotPosts(int limit) {
    std::vector<Post *> sortedPosts = posts;
    std::sort(sortedPosts.begin(), sortedPosts.end(),
              [](const Post *a, const Post *b) {
                  return a->getViewCount() > b->getViewCount();
              });

    std::vector<Post *> result;
    for (int i = 0; i < std::min(limit, (int) sortedPosts.size()); ++i) {
        result.push_back(sortedPosts[i]);
    }
    return result;
}

std::vector<QuestionPost *>
CommunityManager::getUnresolvedQuestions(int limit) {
    std::vector<QuestionPost *> unresolved;
    for (auto question: questions) {
        if (!question->getIsResolved()) {
            unresolved.push_back(question);
        }
    }

    std::sort(unresolved.begin(), unresolved.end(),
              [](const QuestionPost *a, const QuestionPost *b) {
                  return a->getCreateTime() > b->getCreateTime();
              });

    std::vector<QuestionPost *> result;
    for (int i = 0; i < std::min(limit, (int) unresolved.size()); ++i) {
        result.push_back(unresolved[i]);
    }
    return result;
}
