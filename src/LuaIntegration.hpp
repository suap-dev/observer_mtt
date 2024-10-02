#ifndef LUA_INTEGRATION_HPP
#define LUA_INTEGRATION_HPP

#include <lua.hpp>
#include <string>
#include <iostream>

using namespace std;

class LuaIntegration {
public:
    // Constructor: Initializes Lua state
    LuaIntegration() {
        L = luaL_newstate();          // Create a new Lua state
        luaL_openlibs(L);             // Open standard libraries
    }

    // Destructor: Closes Lua state
    ~LuaIntegration() {
        if (L) lua_close(L);          // Close Lua state if it's open
    }

    // Load and execute Lua script
    bool loadScript(const string& script) {
        if (luaL_dofile(L, script.c_str()) != LUA_OK) {
            cerr << "Error loading Lua script: " << lua_tostring(L, -1) << endl;
            lua_pop(L, 1); // Remove error message from the stack
            return false;
        }
        return true;
    }

    // Call the Lua function 'OnEventReceived' with an event string
    void callLuaFunction(const string& event) {
        lua_getglobal(L, "OnEventReceived");  // Get the Lua function by name
        if (lua_isfunction(L, -1)) {          // Check if it's a valid function
            lua_pushstring(L, event.c_str()); // Push the event string argument
            if (lua_pcall(L, 1, 0, 0) != LUA_OK) { // Call Lua function with 1 argument and 0 return values
                cerr << "Error calling Lua function: " << lua_tostring(L, -1) << endl;
                lua_pop(L, 1);  // Remove error message from the stack
            }
        } else {
            cerr << "OnEventReceived is not a valid function!" << endl;
            lua_pop(L, 1); // Remove the invalid function from the stack
        }
    }

private:
    lua_State* L;  // Lua interpreter state
};

#endif // LUA_INTEGRATION_HPP
