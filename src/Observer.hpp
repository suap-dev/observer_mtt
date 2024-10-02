#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <string>

using namespace std;

class Observer {
public:
    virtual ~Observer() {}  // Virtual destructor for proper cleanup in derived classes

    // Pure virtual function to be implemented by concrete observers
    virtual void update(const string& event) = 0;
};

#endif // OBSERVER_HPP
