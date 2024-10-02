#include "EventSystem.hpp"
#include "LuaObserver.hpp"
#include "LuaIntegration.hpp"
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

// Global mutex for synchronizing access to Lua states
mutex luaMutex;

// Function for each thread to run its Lua state and handle events
void threadFunction(shared_ptr<LuaIntegration> luaIntegration, int threadID)
{
    cout << "Thread " << threadID << " started." << endl;

    // Load the Lua script (each thread has its own Lua state)
    if (!luaIntegration->loadScript("lua-scripts/observer.lua"))
    {
        cerr << "Thread " << threadID << ": Failed to load Lua script." << endl;
        return;
    }

    cout << "Thread " << threadID << " ready to receive events." << endl;
}

// Function to create and run Lua observers in worker threads
void createLuaWorker(shared_ptr<LuaIntegration> luaIntegration, int threadID, EventSystem &eventSystem)
{
    // Create a LuaObserver for this worker
    shared_ptr<Observer> luaObserver = make_shared<LuaObserver>(luaIntegration);

    // Register observer to the global EventSystem
    eventSystem.registerObserver(luaObserver);

    // Run thread function to set up Lua state
    thread workerThread(threadFunction, luaIntegration, threadID);
    workerThread.detach(); // Detach thread to keep it running in the background
}

int main()
{
    // Number of Lua workers (threads)
    const int numWorkers = 4;

    // Create the global EventSystem in the main thread
    EventSystem eventSystem;

    // Vector to store LuaIntegration objects for each worker
    vector<shared_ptr<LuaIntegration>> luaIntegrations;

    // Create worker threads with individual Lua states
    for (int i = 0; i < numWorkers; ++i)
    {
        auto luaIntegration = make_shared<LuaIntegration>();
        luaIntegrations.push_back(luaIntegration);

        // Create and register a Lua observer for each thread
        createLuaWorker(luaIntegration, i, eventSystem);
    }

    // Sleep to prepare worker threads
    this_thread::sleep_for(chrono::seconds(1));

    // Main thread triggers events in the global EventSystem
    for (int i = 0; i < 5; ++i)
    {
        string event = "Global Event " + to_string(i);
        cout << "Main thread: Triggering " << event << endl;

        // Trigger event in the global EventSystem
        eventSystem.notifyObservers(event);

        // Sleep to simulate time between events
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
