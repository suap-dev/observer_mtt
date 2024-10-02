#ifndef LUA_OBSERVER_HPP
#define LUA_OBSERVER_HPP

#include "Observer.hpp"
#include "LuaIntegration.hpp"
#include <string>
#include <memory>

using namespace std;

class LuaObserver : public Observer {
public:
    LuaObserver(shared_ptr<LuaIntegration> luaIntegration)
        : luaIntegration(luaIntegration) {}

    // Implement the update method for Lua observers
    void update(const string& event) override {
        luaIntegration->callLuaFunction(event);  // Call the Lua function with the event
    }

private:
    shared_ptr<LuaIntegration> luaIntegration;  // Holds the Lua integration for calling Lua functions
};

#endif // LUA_OBSERVER_HPP
