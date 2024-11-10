#include "DatabaseDeleter.h"
#include <QSqlQuery>
#include "DataBaseCommons.h"
struct DeleteSqlFactory {
    static constexpr const char* DELETE = "DELETE FROM TodoTable";
    static QString               createSqlDeleterByID(const int& id) {
        return QString("%1 WHERE ID = %2").arg(DELETE, QString::number(id));
    }

    static QString createSqlDeleteMultiIDs(const QList<int>& ids) {
        return QString("%1 WHERE ID IN %2")
            .arg(DELETE, DataBaseCommons::fromIDGroup(ids));
    }
};

/*
    From now we support only delete actually the id
*/

static bool _delete_by_id(const int& id) {
    QSqlQuery query;
    query.prepare(DeleteSqlFactory::createSqlDeleterByID(id));
    return query.exec();
}

static bool _delete_by_ids(const QList<int>& ids) {
    QSqlQuery query;

    query.prepare(DeleteSqlFactory::createSqlDeleteMultiIDs(ids));

    return query.exec();
}

bool DatabaseDeleter::deleteTaskInDataBase(const Task& atTask) {
    return _delete_by_id(atTask.gain_id());
}

bool DatabaseDeleter::deleteTaskInDataBase(const QList<Task*> tasks) {
    QList<int> ids;
    for (const auto& each : tasks) {
        ids << each->gain_id();
    }
    return _delete_by_ids(ids);
}
