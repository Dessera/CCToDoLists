#include "CCToDoDataBaseImpl.h"
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

static CCToDoDataBaseImpl::ErrorCode fromSql(const QSqlError error) {
    switch (error.type()) {
        case QSqlError::ConnectionError:
            return CCToDoDataBaseImpl::ErrorCode::ConnectionError;
        case QSqlError::StatementError:
            return CCToDoDataBaseImpl::ErrorCode::StatementError;
        case QSqlError::TransactionError:
            return CCToDoDataBaseImpl::ErrorCode::TransactionError;
        default:
            return CCToDoDataBaseImpl::ErrorCode::UnknownErro;
    }
}

CCToDoDataBaseImpl::CCToDoDataBaseImpl(QObject* parent) : QObject(parent) {
    _do_init_dataBase();
}

void CCToDoDataBaseImpl::_do_init_dataBase() {
    // Initialize the database.
    database = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
}

void CCToDoDataBaseImpl::setIDIncrementReset() {
    QSqlQuery query;
    bool      res = query.exec(
        "UPDATE sqlite_sequence SET seq = 1 WHERE name = 'TodoTable'");
    if (!res) {
        qWarning() << "Failed to reset ID increment"
                   << query.lastError().text();
    }
}

void CCToDoDataBaseImpl::tell_error() {
    emit errorOccur(fromSql(database->lastError()),
                    database->lastError().text());
}

bool CCToDoDataBaseImpl::open_database(const QString& databaseName) {
    // Open the database.
    database->setDatabaseName(databaseName);
    if (!database->open()) {
        tell_error();
        return false;
    }
    setIDIncrementReset();
    emit connect_success();
    return true;
}

CCToDoDataBaseImpl::~CCToDoDataBaseImpl() {
    qDebug() << "Release Database";
    QString name = database->connectionName();
    database->close();
    delete database;
    QSqlDatabase::removeDatabase(name);
}
