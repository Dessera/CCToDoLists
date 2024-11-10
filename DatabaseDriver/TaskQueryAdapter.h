#ifndef TASKQUERYADAPTER_H
#define TASKQUERYADAPTER_H
#include <QString>
class QSqlQuery;
class Task;

struct TaskQueryAdapter {
    static Task*   fromQuery(QSqlQuery& query);
    static QString toInsertiveQuery(const Task& task);
};

#endif  // TASKQUERYADAPTER_H
