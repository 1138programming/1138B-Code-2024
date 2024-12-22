#include "taskmanager/taskmanager.hpp"

void TaskManager::addTask(TaskWrapper* task) {
    tasks.push_back({task, false});
}

void TaskManager::startTask(TaskWrapper* task) {
    for (auto& managedTask : tasks) {
        if (managedTask.task == task) {
            managedTask.task->start();
            managedTask.shouldBeRunning = true;
            break;
        }
    }
}

void TaskManager::stopTask(TaskWrapper* task) {
    for (auto& managedTask : tasks) {
        if (managedTask.task == task) {
            managedTask.task->stop();
            managedTask.shouldBeRunning = false;
            break;
        }
    }
}

void TaskManager::restartTask(TaskWrapper* task) {
    for (auto& managedTask : tasks) {
        if (managedTask.task == task) {
            managedTask.task->restart();
            managedTask.shouldBeRunning = true;
            break;
        }
    }
}

void TaskManager::startAllTasks() {
    for (auto& managedTask : tasks) {
        managedTask.task->start();
        managedTask.shouldBeRunning = true;
    }
}

void TaskManager::stopAllTasks() {
    for (auto& managedTask : tasks) {
        managedTask.task->stop();
        managedTask.shouldBeRunning = false;
    }
}

void TaskManager::checkAndRestartTasks() {
    for (auto& managedTask : tasks) {
        if (managedTask.shouldBeRunning && !managedTask.task->isRunning()) {
            managedTask.task->restart();
            // pros::lcd::print(2, "Restarted Task: %s", managedTask.task->getTaskName());
        }
    }
}

bool TaskManager::isTaskRunning(TaskWrapper* task) const {
    for (const auto& managedTask : tasks) {
        if (managedTask.task == task) {
            return managedTask.task->isRunning();
        }
    }
    return false;
}
