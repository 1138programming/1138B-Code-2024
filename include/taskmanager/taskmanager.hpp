#include <vector>
#include "TaskWrapper.hpp"

class TaskManager {
private:
    struct ManagedTask {
        TaskWrapper* task;
        bool shouldBeRunning;
    };

    std::vector<ManagedTask> tasks;

public:
    void addTask(TaskWrapper* task);
    void startTask(TaskWrapper* task);
    void stopTask(TaskWrapper* task);
    void restartTask(TaskWrapper* task);
    void startAllTasks();
    void stopAllTasks();
    void checkAndRestartTasks();
    bool isTaskRunning(TaskWrapper* task) const;
};