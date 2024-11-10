#include "DataBaseAdder.h"
#include <QMutexLocker>
#include <QSqlQuery>
#include "Task.h"
#include "TaskQueryAdapter.h"

/*
    Factory! Factory! Factory!
*/

struct AdderSqlFactory {
    static constexpr const char* INSERT_TARGET = "INSERT INTO TodoTable ";
    static QString               createAddSql(const Task& add) {
        return QString(INSERT_TARGET) + TaskQueryAdapter::toInsertiveQuery(add);
    }
    static int fetchInstantGainID() {
        QSqlQuery query;
        query.prepare("SELECT last_insert_rowid()");
        query.exec();
        query.next();
        return query.value(0).toInt();
    }
};

/*
    The adder of the database
*/
bool DataBaseAdder::addTaskBack(Task& add) {
    QSqlQuery            query;
    static QMutex        mutex;
    QMutexLocker<QMutex> locker(&mutex);
    query.prepare(AdderSqlFactory::createAddSql(add));
    bool result = query.exec();
    if (!result) return false;
    add.setid_from_db(AdderSqlFactory::fetchInstantGainID());
    return true;
}
