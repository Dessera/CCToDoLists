#include "TaskListsHandle.h"

void TaskListsHandle::setManage(QList<Task*>& handling) {
    if (!this->handling.empty()) releaseSourceIn();

    for (auto task : handling) {
        this->handling.push_back(TaskFactory::toHeap(*task));
    }
    // release the original sources and set clear
    for (auto task : handling) {
        delete task;
    }
    handling.clear();
}

void TaskListsHandle::releaseSourceIn() {
    for (auto task : handling) {
        delete task;
    }
    handling.clear();
}

QList<Task*> TaskListsHandle::borrowsFrom() const {
    QList<Task*> result;
    for (const auto& each : handling) {
        result << each;
    }
    return result;
}

void TaskListsHandle::releaseTargetSources(const QList<Task*>& releases) {
    for (const auto& each_shell_del : releases) {
        int index = handling.indexOf(each_shell_del);
        if (index < 0) {
            qWarning() << "Deleting a not existing task!";
            continue;
        }
        auto delete_task = handling.takeAt(index);
        delete delete_task;
    }
}

TaskListsHandle::~TaskListsHandle() {
    releaseSourceIn();
}
