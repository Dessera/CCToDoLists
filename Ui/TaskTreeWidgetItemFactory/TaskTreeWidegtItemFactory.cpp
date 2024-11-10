#include "TaskTreeWidegtItemFactory.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "CCToDoTreeWidget/CCToDoTreeWidget.h"
#include "CCToDoTreeWidgetItem/CCToDoTreeWidgetItem.h"
#include "Task.h"
#include "TaskHelpUtils.h"
#include "UiSources/UiSources.h"

/*
    itemFromTask means to map task to item
    And it's **my design fault to make such a misleading name :( **
*/
QTreeWidgetItem* TaskTreeWidegtItemFactory::itemFromTask(Task*        task,
                                                         QTreeWidget* tree,
                                                         Task* parentTask) {
    auto             parentWidgetItem = map.value(parentTask, nullptr);
    QTreeWidgetItem* thisItem         = nullptr;
    if (!tree) {
        /* At any how, GUI Application can't let it happen */
        qFatal() << "TreeWidget is empty, crash shell be!";
        return nullptr;
    }

    auto special_tree = dynamic_cast<CCToDoTreeWidget*>(tree);
    /* what are we binding at? */
    if (special_tree) {
        thisItem = new CCToDoTreeWidgetItem(
            parentWidgetItem ? parentWidgetItem : tree->invisibleRootItem());
        setItemStyles(task, thisItem);
        setItemFlagsForCCToDoTree(thisItem);
    } else {
        thisItem = new QTreeWidgetItem(
            parentWidgetItem ? parentWidgetItem : tree->invisibleRootItem());
        setItemStyles(task, thisItem);
        setItemFlagsForCommonTree(thisItem);
    }
    map.insert(task, thisItem);
    return thisItem;
}

void TaskTreeWidegtItemFactory::setItemStyles(const Task*      task,
                                              QTreeWidgetItem* thisItem) {
    thisItem->setText(ColumnIndex::MainTaskDescriptions, task->getmainTask());
    thisItem->setIcon(ColumnIndex::MainTaskDescriptions,
                      UiSources::IconsStorage::MainTaskIcon());

    thisItem->setText(ColumnIndex::Priority,
                      TaskHelpUtils::gainPriorityString(*task));
    thisItem->setIcon(ColumnIndex::Priority,
                      UiSources::IconsStorage::fromTaskPriority(*task));

    thisItem->setText(ColumnIndex::StartTime,
                      TaskHelpUtils::toDateTime(task->getstartFrom()));
    thisItem->setIcon(ColumnIndex::StartTime,
                      UiSources::IconsStorage::StartLineIcon());

    thisItem->setText(ColumnIndex::DeadLine,
                      TaskHelpUtils::toDateTime(task->getendAt()));

    thisItem->setIcon(ColumnIndex::DeadLine,
                      UiSources::IconsStorage::DeadLineIcon());
    thisItem->setCheckState(
        0, task->getisFinished() ? Qt::Checked : Qt::Unchecked);

    // setToolTips for each column
    thisItem->setToolTip(ColumnIndex::MainTaskDescriptions,
                         task->getdescription());
    thisItem->setToolTip(ColumnIndex::Priority,
                         TaskHelpUtils::gainPriorityString(*task));
    thisItem->setToolTip(ColumnIndex::DeadLine,
                         TaskHelpUtils::toDateTime(task->getendAt()));

    // setTextProperty for further sortings
    thisItem->setData(ColumnIndex::DeadLine, Qt::UserRole + 1,
                      task->getendAt().toMSecsSinceEpoch());
}

void TaskTreeWidegtItemFactory::setItemFlagsForCCToDoTree(
    QTreeWidgetItem* item) {
    item->setFlags(item->flags() | Qt::ItemIsEditable | Qt::ItemIsAutoTristate);
}

void TaskTreeWidegtItemFactory::setItemFlagsForCommonTree(
    QTreeWidgetItem* item) {
    // setItem Uncheckable :)
    item->setFlags(item->flags() & ~Qt::ItemIsUserCheckable);
}

/*
    For readers: if u gonna change the item update policy,
    do it at here :)
*/
bool TaskTreeWidegtItemFactory::modifiedAccordingItems(Task&            task,
                                                       QTreeWidgetItem* item) {
    if (!item) return false;
    task.setmainTask(item->text(ColumnIndex::MainTaskDescriptions));

    task.setpriority(TaskHelpUtils::fromInt(
        TaskHelpUtils::fromPriorityString(item->text(ColumnIndex::Priority))));

    /*
        Check the time relationship, if the start time is later than the end
       time then we have to revert the time relationship
    */
    QDateTime start =
        TaskHelpUtils::fromDateTime(item->text(ColumnIndex::StartTime));
    QDateTime end =
        TaskHelpUtils::fromDateTime(item->text(ColumnIndex::DeadLine));
    if (start >= end) {
        // can't revert time relationship
        end = QDateTime(start.date(), QTime(23, 59, 59));
    }

    task.setstartFrom(start);
    task.setendAt(end);

    task.setisFinished(item->checkState(0) == Qt::Checked);

    // also update the items
    setItemStyles(&task, item);

    return true;
}

/*
    Simply unmap the relationship between task and item
*/
bool TaskTreeWidegtItemFactory::makeUnmap(
    const QList<QTreeWidgetItem*>& targetItem) {
    for (const auto& each : targetItem) {
        auto task = fromItemOne(each);
        if (task) {
            map.remove(task);
        }
    }
    return true;
}

Task* TaskTreeWidegtItemFactory::fromItemOne(QTreeWidgetItem* item) const {
    return map.key(item, nullptr);
}

QTreeWidgetItem* TaskTreeWidegtItemFactory::fromTask(Task* task) const {
    return map.value(task, nullptr);
}

void TaskTreeWidegtItemFactory::clearHolds() {
    map.clear();
}
