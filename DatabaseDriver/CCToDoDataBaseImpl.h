#ifndef CCTODODATABASEIMPL_H
#define CCTODODATABASEIMPL_H

#include <QObject>
class QSqlDatabase;
class CCToDoDataBaseImpl : public QObject {
    Q_OBJECT
public:
    CCToDoDataBaseImpl(const CCToDoDataBaseImpl&)            = delete;
    CCToDoDataBaseImpl& operator=(const CCToDoDataBaseImpl&) = delete;
    ~CCToDoDataBaseImpl();
    bool open_database(const QString& databaseName);

    enum class ErrorCode {
        NoError,
        ConnectionError,
        StatementError,
        TransactionError,
        UnknownErro,
    };

signals:
    void errorOccur(ErrorCode code, QString error);
    void connect_success();

private:
    friend class CCToDoDataBase;
    CCToDoDataBaseImpl(QObject* parent = nullptr);
    void          _do_init_dataBase();
    void          tell_error();
    void          setIDIncrementReset();
    QSqlDatabase* database{nullptr};
};

#endif  // CCTODODATABASEIMPL_H
