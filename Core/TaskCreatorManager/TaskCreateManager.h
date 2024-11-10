#ifndef TASKCREATEMANAGER_H
#define TASKCREATEMANAGER_H
#include <QString>
class QDate;
class Task;
/*
    This Class is using in ui communication to create a task for convenience
*/

struct TaskCreateManager {
    static QList<Task*> gainTodaysTask();
    static QList<Task*> gainDateTask(const QDate& date);
    static QList<Task*> gainInWeekTask();
    static QList<Task*> gainHighPriorityTask();
};

#endif  // TASKCREATEMANAGER_H
