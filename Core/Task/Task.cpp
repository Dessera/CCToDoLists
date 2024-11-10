#include "Task.h"
/*
    For readers:
    Try to simplify the task creation process?
    I tried at one time(2024.11.9 1:00 am), but i failed, so i just
    put it at here
*/
Task::Task(const Task& task) {
    taskData.description = task.taskData.description;
    taskData.mainTask    = task.taskData.mainTask;
    taskData.parent_id   = task.taskData.parent_id;
    taskData.startFrom   = task.taskData.startFrom;
    taskData.endAt       = task.taskData.endAt;
    taskData.priority    = task.taskData.priority;
    taskData.groupName   = task.taskData.groupName;
    taskData.id_from_db  = task.taskData.id_from_db;
    taskData.isFinished  = task.taskData.isFinished;
}

Task::Task(Task&& task) noexcept {
    taskData.description = std::move(task.taskData.description);
    taskData.mainTask    = std::move(task.taskData.mainTask);
    taskData.parent_id   = task.taskData.parent_id;
    taskData.startFrom   = task.taskData.startFrom;
    taskData.endAt       = task.taskData.endAt;
    taskData.priority    = task.taskData.priority;
    taskData.groupName   = task.taskData.groupName;
    taskData.id_from_db  = task.taskData.id_from_db;
    taskData.isFinished  = task.taskData.isFinished;
}

const Task& Task::operator=(const Task& task) {
    if (&task == this) return *this;
    taskData.description = task.taskData.description;
    taskData.mainTask    = task.taskData.mainTask;
    taskData.parent_id   = task.taskData.parent_id;
    taskData.startFrom   = task.taskData.startFrom;
    taskData.endAt       = task.taskData.endAt;
    taskData.priority    = task.taskData.priority;
    taskData.groupName   = task.taskData.groupName;
    taskData.id_from_db  = task.taskData.id_from_db;
    taskData.isFinished  = task.taskData.isFinished;
    return *this;
}

struct TaskTimeCreator TaskCreatorBase::setTime() {
    return TaskTimeCreator(holdingTask);
}

struct TaskMainDescriptorCreator TaskCreatorBase::setMainTask() {
    return TaskMainDescriptorCreator(holdingTask);
}

struct TaskExtraDescriptorCreator TaskCreatorBase::setDescription() {
    return TaskExtraDescriptorCreator(holdingTask);
}

struct TaskPriorityCreator TaskCreatorBase::setPriority() {
    return TaskPriorityCreator(holdingTask);
}

struct TaskSetGroupCreator TaskCreatorBase::setGroup() {
    return TaskSetGroupCreator(holdingTask);
}

struct TaskTimeCreator& TaskTimeCreator::setStartTime(const QDateTime& start) {
    holdingTask.taskData.startFrom = start;
    return *this;
}

struct TaskTimeCreator& TaskTimeCreator::setEndTime(const QDateTime& end) {
    holdingTask.taskData.endAt = end;
    return *this;
}

struct TaskMainDescriptorCreator& TaskMainDescriptorCreator::setThisMainTask(
    const QString& mainTask) {
    holdingTask.taskData.mainTask = mainTask;
    return *this;
}

struct TaskExtraDescriptorCreator&
TaskExtraDescriptorCreator::setThisDescription(const QString& description) {
    holdingTask.taskData.description = description;
    return *this;
}

struct TaskPriorityCreator& TaskPriorityCreator::setThisPriority(
    Task::TaskData::Priority priority) {
    holdingTask.taskData.priority = priority;
    return *this;
}

struct TaskSetGroupCreator& TaskSetGroupCreator::setThisGroup(
    const QString& groupName) {
    holdingTask.taskData.groupName = groupName;
    return *this;
}
