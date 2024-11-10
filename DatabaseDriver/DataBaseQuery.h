#ifndef DATABASEQUERY_H
#define DATABASEQUERY_H
#include "Task.h"

class DataBaseQuery {
public:
    using Priority = Task::TaskData::Priority;
    DataBaseQuery();
    DataBaseQuery(const DataBaseQuery&)            = delete;
    DataBaseQuery& operator=(const DataBaseQuery&) = delete;

    /* Searching the main */
    static QList<Task*> queryTask(const QString& includingSearch);

    /* those who are in time */
    static QList<Task*> queryTask(const QDateTime& inTime);
    /* query in a wide range, any tasks that is accessible shell be at here */
    static QList<Task*> queryTask(const QDateTime& startTime,
                                  const QDateTime& endTime);

    /* query in a lot strict way, for those who start after the start time
     * and the end time
     */
    static QList<Task*> queryStrictRangeDateTask(const QDateTime& startTime,
                                                 const QDateTime& endTime);

    /* Query a tasks child */
    static QList<Task*> queryChild(const Task& parent);

    static QList<Task*> queryAllBeforeDateTime(const QDateTime& date);

    static Task* queryParent(const Task& child);

    static QList<Task*> queryGroup(const QString& groupName);

    static QList<Task*> queryPriority(Priority priority);

    static QList<Task*> queryOnDateDDL(const QDate& date);

    static QList<Task*> queryWeekSessions();

    static QList<Task*> queryByIDs(const QList<int>& ids);

    static QList<Task*> all();

private:
    static QList<Task*> _do_query(const QString& queryString);
};

#endif  // DATABASEQUERY_H
