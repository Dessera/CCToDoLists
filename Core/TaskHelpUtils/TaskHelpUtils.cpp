#include "TaskHelpUtils.h"
#include "CCToDoDataBase.h"

struct TaskValueMapCreator {
    static QString create(const QString& key, const QString value) {
        return QString("%1 = '%2'").arg(key, value);
    }
};

void TaskHelpUtils::display_as_format(const Task& task [[maybe_unused]]) {
#ifdef ON_DEBUG
    qDebug() << "-------------- Task Printer Start ------------";
    qDebug() << "Task ID: " << task.taskData.id_from_db;
    qDebug() << "Priority: " << static_cast<int>(task.taskData.priority);
    qDebug() << "Start From: " << toDateTime(task.taskData.startFrom);
    qDebug() << "End At: " << toDateTime(task.taskData.endAt);
    qDebug() << "Description: " << task.taskData.description;
    qDebug() << "Main Task: " << task.taskData.mainTask;
    qDebug() << "Parent ID: " << task.taskData.parent_id;
    qDebug() << "Group: " << task.taskData.groupName;
    qDebug() << "isFinished: " << task.taskData.isFinished;
    qDebug() << "-------------- Task Printer End --------------";
#endif
    return;
}

QString TaskHelpUtils::gainPriorityString(const Task& task) {
    return gainPriorityString(task.taskData.priority);
}

QString TaskHelpUtils::gainPriorityString(Task::TaskData::Priority priority) {
    switch (priority) {
        case Task::TaskData::Priority::Low:
            return PriorityString::Low;
        case Task::TaskData::Priority::Medium:
            return PriorityString::Medium;
        case Task::TaskData::Priority::High:
            return PriorityString::High;
    }
    return PriorityString::Medium;
}

/*
    Core Functions, mapping from task to sql value set strings!
*/

QString TaskHelpUtils::toValueMapString(const Task& task) {
    QString priority = TaskValueMapCreator::create(
        CCToDoDataBase::KEY_PRIORITY,
        QString::number(static_cast<int>(task.taskData.priority)));

    QString startFrom = TaskValueMapCreator::create(
        CCToDoDataBase::KEY_BEGIN_DATE, toDateTime(task.taskData.startFrom));

    QString endTo = TaskValueMapCreator::create(
        CCToDoDataBase::KEY_END_DATE, toDateTime(task.taskData.endAt));

    QString description = TaskValueMapCreator::create(
        CCToDoDataBase::KEY_DESCRIPTIONS, task.taskData.description);

    QString mainTask = TaskValueMapCreator::create(
        CCToDoDataBase::KEY_MAIN_TASK, task.taskData.mainTask);

    QString parentID = TaskValueMapCreator::create(
        CCToDoDataBase::KEY_PARENTID, QString::number(task.taskData.parent_id));

    QString group = TaskValueMapCreator::create(
        CCToDoDataBase::KEY_BELONGING_GROUP, task.taskData.groupName);

    QString isFinished =
        TaskValueMapCreator::create(CCToDoDataBase::KEY_IS_FINISHED,
                                    QString::number(task.taskData.isFinished));

    return QString("%1, %2, %3, %4, %5, %6, %7, %8")
        .arg(priority, startFrom, endTo, description, mainTask, parentID, group,
             isFinished);
}

int TaskHelpUtils::fromPriorityString(const QString& priority) {
    if (priority == PriorityString::Low)
        return static_cast<int>(Task::TaskData::Priority::Low);
    if (priority == PriorityString::Medium)
        return static_cast<int>(Task::TaskData::Priority::Medium);
    if (priority == PriorityString::High)
        return static_cast<int>(Task::TaskData::Priority::High);
    return static_cast<int>(Task::TaskData::Priority::Medium);
}

Task* TaskHelpUtils::queryTempTaskInList(const Task&        task,
                                         const QList<Task*> tasks) {
    for (const auto& each : tasks) {
        if (each->gain_id() == task.getparent_id()) {
            return each;
        }
    }
    return nullptr;
}
