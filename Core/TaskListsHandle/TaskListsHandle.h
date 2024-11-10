#ifndef TASKLISTSHANDLE_H
#define TASKLISTSHANDLE_H
#include <QList>
#include "Task.h"

/*
    To understand this, I adviced u to treat it as a
    std::shared_ptr<Task[]> :)
    - Auto Management
*/
class TaskListsHandle {
public:
    TaskListsHandle()                                  = default;
    TaskListsHandle(const TaskListsHandle&)            = delete;
    TaskListsHandle& operator=(const TaskListsHandle&) = delete;
    ~TaskListsHandle();
    // setManage WILL release the previous sources, so catch out!
    void setManage(QList<Task*>& handling);
    /* The task has already in heap, we just manage it :) */
    void addTaskIntoManage(Task* task) {
        handling << task;
    }
    void releaseSourceIn();

    QList<Task*> borrowsFrom() const;
    void         releaseTargetSources(const QList<Task*>& releases);

private:
    QList<Task*> handling;
};

#endif  // TASKLISTSHANDLE_H
