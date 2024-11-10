#include "TestHelpUtils.h"
#include "DataBaseQuery.h"
#include "TaskHelpUtils.h"

void TestHelpUtils::displayAllInDataBase() {
#ifdef SET_ON_DEBUG
    auto all = DataBaseQuery::all();
    qDebug() << "---------------------------------------------------------";
    qDebug() << "At Date:> " << QDateTime::currentDateTime().toString();
    qDebug() << "with here we gain" << all.size();
    for (auto& each : all) {
        TaskHelpUtils::display_as_format(*each);
        delete each;
    }
    qDebug() << "---------------------------------------------------------";
#endif
}
