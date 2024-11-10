#include "TestDeleter.h"
#include "DataBaseQuery.h"
#include "DatabaseDeleter.h"
#include "Task.h"
#include "TaskHelpUtils.h"
void TestDeleter::doTest() {
    auto all = DataBaseQuery::all();

    for (auto& each : all) {
        if (each->gain_id() == 2) {
            if (!DatabaseDeleter::deleteTaskInDataBase(*each)) {
                qDebug() << "Remove failed!";
            }
        }
    }

    for (auto& each : all) {
        delete each;
    }

    qDebug() << "After delete";

    all = DataBaseQuery::all();
    qDebug() << all.size();
    for (auto& each : all) {
        TaskHelpUtils::display_as_format(*each);
        delete each;
    }

    qDebug() << "Shell DeleteALL";

    all = DataBaseQuery::all();
    if (!DatabaseDeleter::deleteTaskInDataBase(all)) {
        qDebug() << "Failed to delete all";
    }

    all = DataBaseQuery::all();
    for (auto& each : all) {
        TaskHelpUtils::display_as_format(*each);
        delete each;
    }
}
