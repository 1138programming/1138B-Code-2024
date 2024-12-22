#include "taskmanager/taskwrapper.hpp"

TaskWrapper::TaskWrapper(void (*func)(void*), void* param, const char* name)
    : taskFunction(func), taskParam(param), taskName(name), taskHandle(nullptr) {}

void TaskWrapper::start() {
    if (taskHandle == nullptr) {
        taskHandle = new pros::Task(taskFunction, taskParam, taskName);
    }
}

void TaskWrapper::stop() {
    if (taskHandle != nullptr) {
        taskHandle->remove();
        delete taskHandle;
        taskHandle = nullptr;
    }
}

void TaskWrapper::restart() {
    stop();
    start();
}

bool TaskWrapper::isRunning() const {
    return taskHandle != nullptr;
}

const char* TaskWrapper::getTaskName() const {
    return taskName;
}

TaskWrapper::~TaskWrapper() {
    stop();
}
