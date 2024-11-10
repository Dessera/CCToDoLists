#include "DataBaseUpdater.h"
#include <QSqlQuery>
#include "TaskHelpUtils.h"
#include "qsqlerror.h"
struct DataBaseUpdateSQLFactory {
private:
    static constexpr const char* UPDATE = "UPDATE TodoTable SET";
    static constexpr const char* WHERE  = "WHERE id = ";
    static QString               getWhere(const Task& task) {
        return QString("%1 %2").arg(WHERE, QString::number(task.gain_id()));
    }

public:
    static QString getUpdateSql(const Task& task) {
        return QString("%1 %2 %3")
            .arg(UPDATE, TaskHelpUtils::toValueMapString(task), getWhere(task));
    }
};

bool DataBaseUpdater::updateTargetTask(Task& update) {
    QSqlQuery query;
    QString   res  = DataBaseUpdateSQLFactory::getUpdateSql(update);
    bool      res2 = query.exec(res);
    qDebug() << query.lastError().text();
    return res2;
}
