#ifndef TESTSOURCES_H
#define TESTSOURCES_H
#include <QString>

class Task;
struct TestSources {
    static QList<Task*> createTestTasks();
    static bool         addTestTaskToDataBase();
    static QList<Task*> createTreeHierarchyTasks();
    static bool         addTreeHierarchyTasksToDataBase();
};

#endif  // TESTSOURCES_H
