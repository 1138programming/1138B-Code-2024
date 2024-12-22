#include "pros/rtos.hpp"

class TaskWrapper {
private:
    pros::Task* taskHandle;
    void (*taskFunction)(void*);
    void* taskParam;
    const char* taskName;

public:
    TaskWrapper(void (func)(void*), void* param = nullptr, const char* name = "");
    void start();
    void stop();
    void restart();
    bool isRunning() const;
    const char* getTaskName() const;
    ~TaskWrapper();
};
