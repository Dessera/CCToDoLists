#include "TaskQueryAdapter.h"
#include <QSqlQuery>
#include "CCToDoDataBase.h"
#include "Task.h"
#include "TaskHelpUtils.h"

/*
    Create Task from QSqlQuery
*/
Task* TaskQueryAdapter::fromQuery(QSqlQuery& query) {
    Task task =
        TaskFactory::createTask()
            .setMainTask()
            .setThisMainTask(
                query.value(CCToDoDataBase::KEY_MAIN_TASK).toString())
            .setDescription()
            .setThisDescription(
                query.value(CCToDoDataBase::KEY_DESCRIPTIONS).toString())
            .setTime()
            .setStartTime(TaskHelpUtils::fromDateTime(
                query.value(CCToDoDataBase::KEY_BEGIN_DATE).toString()))
            .setEndTime(TaskHelpUtils::fromDateTime(
                query.value(CCToDoDataBase::KEY_END_DATE).toString()))
            .setPriority()
            .setThisPriority(TaskHelpUtils::fromInt(
                query.value(CCToDoDataBase::KEY_PRIORITY).toInt()))
            .setGroup()
            .setThisGroup(
                query.value(CCToDoDataBase::KEY_BELONGING_GROUP).toString());
    task.taskData.id_from_db = query.value(CCToDoDataBase::KEY_ID).toInt();
    task.taskData.parent_id = query.value(CCToDoDataBase::KEY_PARENTID).toInt();
    task.taskData.isFinished =
        static_cast<bool>(query.value(CCToDoDataBase::KEY_IS_FINISHED).toInt());
    return TaskFactory::toHeap(task);
}

QString TaskQueryAdapter::toInsertiveQuery(const Task& task) {
    return QString(
               "(MainTask, Descriptions, Priority, "
               "BeginDate, EndDate, BelongingGroup, Parent, isFinished) VALUES "
               "('%1', "
               "'%2', %3, "
               "'%4', '%5', '%6', '%7', '%8')")
        /* Clang will told u to use multi-args, I convinced the idea
            is a bit of shit, see to match
        */
        .arg(task.taskData.mainTask) /* 1 */
        .arg(task.taskData.description)
        .arg(static_cast<int>(task.taskData.priority))
        .arg(TaskHelpUtils::toDateTime(task.taskData.startFrom))
        .arg(TaskHelpUtils::toDateTime(task.taskData.endAt)) /* 5 */
        .arg(task.taskData.groupName)
        .arg(task.taskData.parent_id)
        .arg(QString::number(
            static_cast<int>(task.taskData.isFinished))); /* 8 */
}
