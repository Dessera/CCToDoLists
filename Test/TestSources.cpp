#include "TestSources.h"
#include "DataBaseAdder.h"
#include "Task.h"
QList<Task*> TestSources::createTestTasks() {
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

    Task demoTask2 = TaskFactory::createTask()
                         .setMainTask()
                         .setThisMainTask("Test Task")
                         .setDescription()
                         .setThisDescription("This is a test task")
                         .setTime()
                         .setStartTime(QDateTime::currentDateTime().addDays(-4))
                         .setEndTime(QDateTime::currentDateTime().addDays(4))
                         .setPriority()
                         .setThisPriority(Task::TaskData::Priority::High);

    Task* newTask;

    newTask = TaskFactory::toHeap(demoTask1);
    QList<Task*> result;
    result.push_back(newTask);
    newTask = TaskFactory::toHeap(demoTask2);
    result.push_back(newTask);
    return result;
}

bool TestSources::addTestTaskToDataBase() {
    auto result = createTestTasks();
    bool flag   = true;
    for (auto& task : result) {
        if (!DataBaseAdder::addTaskBack(*task)) {
            flag = false;
        }
        delete task;
    }
    return flag;
}

QList<Task*> TestSources::createTreeHierarchyTasks() {
    Task father = TaskFactory::createTask()
                      .setMainTask()
                      .setThisMainTask("Father Task")
                      .setDescription()
                      .setThisDescription("This is a father task")
                      .setTime()
                      .setStartTime(QDateTime::currentDateTime().addDays(-1))
                      .setEndTime(QDateTime::currentDateTime().addDays(1))
                      .setPriority()
                      .setThisPriority(Task::TaskData::Priority::High);

    DataBaseAdder::addTaskBack(father);

    Task child1 = TaskFactory::createTask()
                      .setMainTask()
                      .setThisMainTask("Child Task 1")
                      .setDescription()
                      .setThisDescription("This is a child task 1")
                      .setTime()
                      .setStartTime(QDateTime::currentDateTime().addDays(-1))
                      .setEndTime(QDateTime::currentDateTime().addDays(1))
                      .setPriority()
                      .setThisPriority(Task::TaskData::Priority::High);

    Task child2 = TaskFactory::createTask()
                      .setMainTask()
                      .setThisMainTask("Child Task 2")
                      .setDescription()
                      .setThisDescription("This is a child task 2")
                      .setTime()
                      .setStartTime(QDateTime::currentDateTime().addDays(-1))
                      .setEndTime(QDateTime::currentDateTime().addDays(1))
                      .setPriority()
                      .setThisPriority(Task::TaskData::Priority::High);

    child1.setparent_id(father);
    child2.setparent_id(father);

    QList<Task*> result;
    result.push_back(TaskFactory::toHeap(std::move(child1)));
    result.push_back(TaskFactory::toHeap(std::move(child2)));
    return result;
}

bool TestSources::addTreeHierarchyTasksToDataBase() {
    auto result = createTreeHierarchyTasks();
    bool flag   = true;
    for (auto& task : result) {
        if (!DataBaseAdder::addTaskBack(*task)) {
            flag = false;
        }
        qDebug() << task->gain_id();
        delete task;
    }
    return flag;
}
