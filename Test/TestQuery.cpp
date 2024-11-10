#include "TestQuery.h"
#include "DataBaseAdder.h"
#include "DataBaseQuery.h"
#include "DataBaseUpdater.h"
#include "TaskHelpUtils.h"
void TestQuery::doTest() {
    /* Must ensure call after open the database */

    /* Check if can gain all */
    qDebug() << "------- Gain All ------- ";
    auto res = DataBaseQuery::all();
    for (auto& task : res) {
        TaskHelpUtils::display_as_format(*task);
    }

    for (auto& task : res) {
        delete task;
    }
    qDebug() << "------- Gain All End ------- ";

    // Add Test
    // test in days
    Task demoTask1 = TaskFactory::createTask()
                         .setMainTask()
                         .setThisMainTask("Test Task")
                         .setDescription()
                         .setThisDescription("This is a test task")
                         .setTime()
                         .setStartTime(QDateTime::currentDateTime().addDays(-1))
                         .setEndTime(QDateTime::currentDateTime().addDays(1))
                         .setPriority()
                         .setThisPriority(Task::TaskData::Priority::High);

    Task demoTask11 =
        TaskFactory::createTask()
            .setMainTask()
            .setThisMainTask("Test Task")
            .setDescription()
            .setThisDescription("This is another test task")
            .setTime()
            .setStartTime(QDateTime::currentDateTime().addDays(-1))
            .setEndTime(QDateTime::currentDateTime().addDays(1))
            .setPriority()
            .setThisPriority(Task::TaskData::Priority::High);

    Task demoTask2 = TaskFactory::createTask()
                         .setMainTask()
                         .setThisMainTask("Test Task")
                         .setDescription()
                         .setThisDescription("This is a test task")
                         .setTime()
                         .setStartTime(QDateTime::currentDateTime().addDays(-2))
                         .setEndTime(QDateTime::currentDateTime().addDays(2))
                         .setPriority()
                         .setThisPriority(Task::TaskData::Priority::High);

    Task demoTask3 = TaskFactory::createTask()
                         .setMainTask()
                         .setThisMainTask("Test Task")
                         .setDescription()
                         .setThisDescription("This is a test task")
                         .setTime()
                         .setStartTime(QDateTime::currentDateTime().addDays(-4))
                         .setEndTime(QDateTime::currentDateTime().addDays(4))
                         .setPriority()
                         .setThisPriority(Task::TaskData::Priority::High);

    DataBaseAdder::addTaskBack(demoTask1);
    DataBaseAdder::addTaskBack(demoTask11);
    DataBaseAdder::addTaskBack(demoTask2);
    DataBaseAdder::addTaskBack(demoTask3);

    // query inTime

    auto result = DataBaseQuery::queryTask(QDateTime::currentDateTime());
    qDebug() << "Checked " << result.size() << " Expected " << 4;
    for (auto& task : result) {
        delete task;
    }

    auto result2 =
        DataBaseQuery::queryTask(QDateTime::currentDateTime().addDays(3));
    qDebug() << "Checked " << result2.size() << " Expected " << 1;
    for (auto& task : result2) {
        delete task;
    }

    auto res3 = DataBaseQuery::queryTask(
        QDateTime(QDate::currentDate(), QTime(0, 0, 0)).addDays(2),
        QDateTime(QDate::currentDate(), QTime(0, 0, 0)).addDays(5));
    qDebug() << "Checked " << res3.size() << " Expected " << 4;
    for (auto& task : res3) {
        delete task;
    }

    // set 2 as parent

    Task child1 = TaskFactory::createTask()
                      .setMainTask()
                      .setThisMainTask("Test Task")
                      .setDescription()
                      .setThisDescription("This is a test task")
                      .setTime()
                      .setStartTime(QDateTime::currentDateTime().addDays(-1))
                      .setEndTime(QDateTime::currentDateTime().addDays(1))
                      .setPriority()
                      .setThisPriority(Task::TaskData::Priority::High);

    Task child2 = TaskFactory::createTask()
                      .setMainTask()
                      .setThisMainTask("Test Task")
                      .setDescription()
                      .setThisDescription("This is a test task")
                      .setTime()
                      .setStartTime(QDateTime::currentDateTime().addDays(-1))
                      .setEndTime(QDateTime::currentDateTime().addDays(1))
                      .setPriority()
                      .setThisPriority(Task::TaskData::Priority::High);

    auto        new_all = DataBaseQuery::all();
    const Task* parent  = nullptr;
    for (auto& each : new_all) {
        if (each->gain_id() == 2) {
            child1.setparent_id(*each);
            child2.setparent_id(*each);
            DataBaseAdder::addTaskBack(child1);
            DataBaseAdder::addTaskBack(child2);
            parent = each;
        }
    }
    if (parent) {
        auto res_child = DataBaseQuery::queryChild(*parent);
        qDebug() << "Expected 2, Checked " << res_child.size();
        for (const auto& each : res_child) {
            delete each;
        }
    }

    for (auto& each : new_all) {
        delete each;
    }
}
