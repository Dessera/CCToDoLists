#include "TestAdd.h"
#include "DataBaseAdder.h"
#include "Task.h"
void TestAdd::doTest() {
    Task demoTask = TaskFactory::createTask()
                        .setMainTask()
                        .setThisMainTask("Test Task")
                        .setDescription()
                        .setThisDescription("This is a test task")
                        .setTime()
                        .setStartTime(QDateTime::currentDateTime())
                        .setEndTime(QDateTime::currentDateTime().addDays(1))
                        .setPriority()
                        .setThisPriority(Task::TaskData::Priority::High);

    if (!DataBaseAdder::addTaskBack(demoTask)) {
        qDebug() << "Error occurs!";
    }
}
