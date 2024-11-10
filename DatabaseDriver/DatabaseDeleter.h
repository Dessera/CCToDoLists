#ifndef DATABASEDELETER_H
#define DATABASEDELETER_H
#include "Task.h"

struct DatabaseDeleter {
    /* Delete by id required*/
    /* won't release the task, cause maybe later it can be refresh back */
    static bool deleteTaskInDataBase(const Task& atTask);

    /* For some continious records, support MultiDeletions*/
    static bool deleteTaskInDataBase(const QList<Task*> tasks);
};

#endif  // DATABASEDELETER_H
