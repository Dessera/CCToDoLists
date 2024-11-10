#include "TaskCreateManager.h"
#include "DataBaseQuery.h"
#include "Task.h"
QList<Task*> TaskCreateManager::gainTodaysTask() {
    return DataBaseQuery::queryOnDateDDL(QDate::currentDate());
}

QList<Task*> TaskCreateManager::gainDateTask(const QDate& date) {
    return DataBaseQuery::queryTask(QDateTime(date, QTime(0, 0, 0)),
                                    QDateTime(date, QTime(23, 59, 59)));
}

QList<Task*> TaskCreateManager::gainInWeekTask() {
    return DataBaseQuery::queryWeekSessions();
}

QList<Task*> TaskCreateManager::gainHighPriorityTask() {
    return DataBaseQuery::queryPriority(Task::TaskData::Priority::High);
}
