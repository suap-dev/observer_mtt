#ifndef EVENT_SYSTEM_HPP
#define EVENT_SYSTEM_HPP

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include "Observer.hpp"

using namespace std;

class EventSystem {
public:
    // Register an observer
    void registerObserver(shared_ptr<Observer> observer) {
        observers.push_back(observer);
    }

    // Remove an observer (correct version)
    void removeObserver(shared_ptr<Observer> observer) {
        auto it = find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            iter_swap(it, observers.end() - 1);  // Swap the observer with the last element
            observers.pop_back();  // Remove the last element (the one we wanted to remove)
        }
    }

    // Notify all observers with an event
    void notifyObservers(const string& event) {
        for (const auto& observer : observers) {
            observer->update(event);  // Call the observer's update method
        }
    }

private:
    vector<shared_ptr<Observer>> observers;  // List of observers
};

#endif // EVENT_SYSTEM_HPP
