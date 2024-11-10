#include "TestTask.h"
#include "Task.h"
#include "TaskHelpUtils.h"
void TestTask::doTest() {
    Task myTestTask =
        TaskFactory::createTask()
            .setMainTask()
            .setThisMainTask("Write a test code")
            .setDescription()
            .setThisDescription("Write a code to test task creating")
            .setTime()
            .setStartTime(TaskHelpUtils::fromDateTime("2021-01-01 00:00:00"))
            .setEndTime(TaskHelpUtils::fromDateTime("2021-01-01 01:00:00"))
            .setPriority()
            .setThisPriority(Task::TaskData::Priority::High);
    TaskHelpUtils::display_as_format(myTestTask);
}
