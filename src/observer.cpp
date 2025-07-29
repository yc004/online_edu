#include "../include/observer.h"
#include <algorithm>
#include <string>

void Subject::addObserver(Observer *obs) { observers.push_back(obs); }

void Subject::removeObserver(Observer *obs) {
  observers.erase(std::remove(observers.begin(), observers.end(), obs),
                  observers.end());
}

void Subject::notifyObservers(const std::string &msg) const {
  for (const auto obs : observers) {
    if (obs)
      obs->update(msg);
  }
}
