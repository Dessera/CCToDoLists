#include "TestDataBase.h"
#include <QDebug>
#include "CCToDoDataBase.h"

void TestDataBase::doTest() {
    CCToDoDataBase dataBase;
    QObject::connect(dataBase.getInstance(), &CCToDoDataBaseImpl::errorOccur,
                     [=](CCToDoDataBaseImpl::ErrorCode code, QString str) {
                         qDebug() << "Error occur";
                         qDebug() << "Error code:" << static_cast<int>(code);
                         qDebug() << "Error message:" << str;
                     });
    bool res =
        dataBase.getInstance()->open_database("data/dataBase/TodoDataBase.db");

    if (!res) qDebug() << "Failed to open the dataBase";
}
