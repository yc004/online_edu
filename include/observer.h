#ifndef OBSERVER_H
#define OBSERVER_H
#include <string>
#include <vector>

// 观察者接口
class Observer {
public:
    virtual void update(const std::string& msg) = 0;
    virtual ~Observer() {}
};

// 被观察者接口
class Subject {
protected:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* obs);
    void removeObserver(Observer* obs);
    void notifyObservers(const std::string& msg) const;
};

#endif // OBSERVER_H 