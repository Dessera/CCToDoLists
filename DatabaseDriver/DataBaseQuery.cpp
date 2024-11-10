#include "DataBaseQuery.h"
#include <QSqlQuery>
#include "CCToDoDataBase.h"
#include "Task.h"
#include "TaskHelpUtils.h"
#include "TaskQueryAdapter.h"
struct QuerySqlFactory {
    static constexpr const char* SELECT_TARGET = "SELECT * from TodoTable ";

    static QString createIncludings(const QString& includingSearch,
                                    const QString  target) {
        return QString(SELECT_TARGET) +
               QString("WHERE %1 LIKE '%" + includingSearch + "%'").arg(target);
    }

    static QString createInTime(const QDateTime t) {
        return QString(SELECT_TARGET) +
               QString("WHERE %1 <= '%3' AND %2 >= '%3' ")
                   .arg(CCToDoDataBase::KEY_BEGIN_DATE,
                        CCToDoDataBase::KEY_END_DATE,
                        TaskHelpUtils::toDateTime(t));
    }

    static QString createRangeMatch(const QDateTime& begin,
                                    const QDateTime& end) {
        return QString(SELECT_TARGET) +
               QString("WHERE %1 <= '%4' AND %2 >= '%3' ")
                   .arg(CCToDoDataBase::KEY_BEGIN_DATE,
                        CCToDoDataBase::KEY_END_DATE,
                        begin.toString("yyyy-MM-dd HH:mm:ss"),
                        end.toString("yyyy-MM-dd HH:mm:ss"));
    };

    static QString createStrictRangeSearch(const QDateTime& begin,
                                           const QDateTime& end) {
        qDebug() << QString("WHERE %1 >= '%3' AND %2 <= '%4' ")
                        .arg(CCToDoDataBase::KEY_BEGIN_DATE,
                             CCToDoDataBase::KEY_END_DATE,
                             begin.toString("yyyy-MM-dd HH:mm:ss"),
                             end.toString("yyyy-MM-dd HH:mm:ss"));
        return QString(SELECT_TARGET) +
               QString("WHERE %1 >= '%3' AND %2 <= '%4' ")
                   .arg(CCToDoDataBase::KEY_BEGIN_DATE,
                        CCToDoDataBase::KEY_END_DATE,
                        begin.toString("yyyy-MM-dd HH:mm:ss"),
                        end.toString("yyyy-MM-dd HH:mm:ss"));
    }

    static QString createCheckChild(const Task& parent) {
        return QString(SELECT_TARGET) +
               QString("WHERE %1 = %2")
                   .arg(CCToDoDataBase::KEY_PARENTID,
                        QString::number(parent.gain_id()));
    }
    static QString createFetchAll() {
        return SELECT_TARGET;
    }

    static QString searchGroup(const QString& groupName) {
        return QString(SELECT_TARGET) +
               QString("WHERE %1 = %2")
                   .arg(CCToDoDataBase::KEY_BELONGING_GROUP, groupName);
    }

    static QString searchParent(const Task& child) {
        return QString(SELECT_TARGET) +
               QString("WHERE %1 = %2")
                   .arg(CCToDoDataBase::KEY_ID,
                        QString::number(child.getparent_id()));
    }

    static QString searchByPriority(Task::TaskData::Priority priority) {
        return QString(SELECT_TARGET) +
               QString("WHERE %1 = %2")
                   .arg(CCToDoDataBase::KEY_PRIORITY,
                        QString::number(static_cast<int>(priority)));
    }

    static QString searchTasksBeforeEndDate(const QDateTime& date) {
        return QString(SELECT_TARGET) +
               QString("WHERE %1 <= '%2'")
                   .arg(CCToDoDataBase::KEY_END_DATE,
                        TaskHelpUtils::toDateTime(date));
    }

    static QString searchDDLIsDate(const QDate& date) {
        return QString(SELECT_TARGET) +
               QString("WHERE %1 BETWEEN '%2' and '%3'")
                   .arg(CCToDoDataBase::KEY_END_DATE,
                        QDateTime(date, QTime(0, 0, 0))
                            .toString("yyyy-MM-dd HH:mm:ss"),
                        QDateTime(date, QTime(23, 59, 59))
                            .toString("yyyy-MM-dd HH:mm:ss"));
    }

    static QString searchWeekSessions() {
        return QString(SELECT_TARGET) +
               QString("WHERE %1 BETWEEN '%2' and '%3'")
                   .arg(CCToDoDataBase::KEY_END_DATE,
                        QDateTime(QDate::currentDate(), QTime(0, 0, 0))
                            .toString("yyyy-MM-dd HH:mm:ss"),
                        QDateTime(QDate::currentDate().addDays(7),
                                  QTime(23, 59, 59))
                            .toString("yyyy-MM-dd HH:mm:ss"));
    }

    static QString queryByIDs(const QList<int>& ids) {
        QString query = QString(SELECT_TARGET) + "WHERE ";
        for (int i = 0; i < ids.size(); ++i) {
            query += CCToDoDataBase::KEY_ID + QString(" = ") +
                     QString::number(ids[i]);
            if (i != ids.size() - 1) {
                query += " OR ";
            }
        }
        return query;
    }
};

/* Searching the main */
QList<Task*> DataBaseQuery::queryTask(const QString& includingSearch) {
    return _do_query(
        QuerySqlFactory::createIncludings(includingSearch, "MainTask"));
}

/* those who are in time */
QList<Task*> DataBaseQuery::queryTask(const QDateTime& inTime) {
    return _do_query(QuerySqlFactory::createInTime(inTime));
}
/* query in must range */
QList<Task*> DataBaseQuery::queryTask(const QDateTime& startTime,
                                      const QDateTime& endTime) {
    return _do_query(QuerySqlFactory::createRangeMatch(startTime, endTime));
}

QList<Task*> DataBaseQuery::queryStrictRangeDateTask(const QDateTime& startTime,
                                                     const QDateTime& endTime) {
    return _do_query(
        QuerySqlFactory::createStrictRangeSearch(startTime, endTime));
}

QList<Task*> DataBaseQuery::queryChild(const Task& parent) {
    return _do_query(QuerySqlFactory::createCheckChild(parent));
}

Task* DataBaseQuery::queryParent(const Task& child) {
    auto result = _do_query(QuerySqlFactory::searchParent(child));
    if (result.isEmpty()) {
        return nullptr;
    }
    /* For somewise, it shell be 1 parent :) */
    return result[0];
}

QList<Task*> DataBaseQuery::all() {
    return _do_query(QuerySqlFactory::createFetchAll());
}

QList<Task*> DataBaseQuery::queryGroup(const QString& groupName) {
    return _do_query(QuerySqlFactory::searchGroup(groupName));
}

QList<Task*> DataBaseQuery::queryPriority(Task::TaskData::Priority priority) {
    return _do_query(QuerySqlFactory::searchByPriority(priority));
}

QList<Task*> DataBaseQuery::queryAllBeforeDateTime(const QDateTime& date) {
    return _do_query(QuerySqlFactory::searchTasksBeforeEndDate(date));
}

QList<Task*> DataBaseQuery::queryOnDateDDL(const QDate& date) {
    return _do_query(QuerySqlFactory::searchDDLIsDate(date));
}

QList<Task*> DataBaseQuery::queryWeekSessions() {
    return _do_query(QuerySqlFactory::searchWeekSessions());
}

QList<Task*> DataBaseQuery::queryByIDs(const QList<int>& ids) {
    return _do_query(QuerySqlFactory::queryByIDs(ids));
}

QList<Task*> DataBaseQuery::_do_query(const QString& queryString) {
    QSqlQuery    query(queryString);
    QList<Task*> result;
    while (query.next()) {
        result << TaskQueryAdapter::fromQuery(query);
    }
    return result;
}
