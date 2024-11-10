#ifndef TASKTREEWIDEGTITEMFACTORY_H
#define TASKTREEWIDEGTITEMFACTORY_H
/*
    An adapter factory, aiming in creating an adapter
    from treeWidget Items to Task, and make a map memo
    between twos.
*/
#include <QMap>
class QTreeWidgetItem;
class QTreeWidget;
class Task;

struct TaskTreeWidegtItemFactory {
    enum ColumnIndex {
        MainTaskDescriptions = 0,
        Priority             = 1,
        StartTime            = 2,
        DeadLine             = 3
    };

    QTreeWidgetItem* itemFromTask(Task* task, QTreeWidget* tree,
                                  Task* parentTask = nullptr);

    Task*            fromItemOne(QTreeWidgetItem* item) const;
    bool             modifiedAccordingItems(Task& task, QTreeWidgetItem* item);
    void             setItemFlagsForCCToDoTree(QTreeWidgetItem* item);
    void             setItemFlagsForCommonTree(QTreeWidgetItem* item);
    QTreeWidgetItem* fromTask(Task* task) const;
    bool             makeUnmap(const QList<QTreeWidgetItem*>& targetItem);
    void             clearHolds();

protected:
    /*
        Watch out! we only shared the raw pointer of the task
        And in Qt, My design pattern is:
        -   If Any object in qt can be managed by qt
            I will do so :)
    */
    QMap<Task*, QTreeWidgetItem*> map;

    /*
        This is important for the outlook of the treeWidget
    */
    void setItemStyles(const Task* task, QTreeWidgetItem* item);
};

#endif  // TASKTREEWIDEGTITEMFACTORY_H
