#include "ToDoTreeWidgetHandler.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "CCToDoTaskTreeMenuFactory/CCToDoTreeCustomMenuFactory.h"
#include "CCToDoTreeWidget.h"
#include "CCToDoTreeWidgetItem/CCToDoTreeWidgetItem.h"
#include "DataBaseAdder.h"
#include "DataBaseUpdater.h"
#include "DatabaseDeleter.h"
#include "TaskCreateWindow/TaskCreateMainWindow.h"
#include "TaskHelpUtils.h"
#include "TaskTreeWidgetItemFactory/TaskTreeWidegtItemFactory.h"
#ifdef REQ_TEST
#include "utils/TestHelpUtils.h"
#endif

ToDoTreeWidgetHandler::ToDoTreeWidgetHandler(QTreeWidget* widget,
                                             QObject*     parent)
    : QObject(parent) {
    handling_tree     = widget;
    auto subtype_tree = dynamic_cast<CCToDoTreeWidget*>(handling_tree);
    if (subtype_tree) {
        handle_CCToDoTreeSpecial(subtype_tree);
        do_initMenuFactory();
        do_initCreateWindow();
    }
}

void ToDoTreeWidgetHandler::do_initMenuFactory() {
    menuFactory = std::make_shared<CCToDoTreeCustomMenuFactory>(this);
    connect(menuFactory.get(),
            &CCToDoTreeCustomMenuFactory::tellAddNewTaskAtHere, this,
            &ToDoTreeWidgetHandler::handle_add_action);
    connect(menuFactory.get(),
            &CCToDoTreeCustomMenuFactory::tellDeleteThisTaskAtHere, this,
            &ToDoTreeWidgetHandler::handle_delete_action);
    connect(menuFactory.get(),
            &CCToDoTreeCustomMenuFactory::tellDisplayDetailOfThisTask, this,
            &ToDoTreeWidgetHandler::handle_display_action);

    connect(menuFactory.get(),
            &CCToDoTreeCustomMenuFactory::tellCopyThisTaskAtHere, this,
            &ToDoTreeWidgetHandler::handle_copy_action);

    connect(menuFactory.get(),
            &CCToDoTreeCustomMenuFactory::tellPasteTaskAtHere, this,
            &ToDoTreeWidgetHandler::handle_paste_action);

    connect(menuFactory.get(), &CCToDoTreeCustomMenuFactory::tellAddToRoot,
            this, &ToDoTreeWidgetHandler::handle_add_root_action);
}

void ToDoTreeWidgetHandler::do_initCreateWindow() {
    createWindow = std::make_shared<TaskCreateMainWindow>();

    connect(createWindow.get(), &TaskCreateMainWindow::tellFetchTask, this,
            &ToDoTreeWidgetHandler::handle_the_incoming_new_task_from_window);
}

void ToDoTreeWidgetHandler::handle_CCToDoTreeSpecial(CCToDoTreeWidget* tree) {
    connect(tree, &CCToDoTreeWidget::tellDragDropParentRelation, this,
            &ToDoTreeWidgetHandler::receiveHandleOfDrags);
    connect(tree->itemDelegate(), &QAbstractItemDelegate::closeEditor, this,
            &ToDoTreeWidgetHandler::handle_value_change);
    connect(tree, &CCToDoTreeWidget::itemCheckboxStatusChanged, this,
            &ToDoTreeWidgetHandler::handle_value_change);
    connect(tree, &CCToDoTreeWidget::customContextMenuRequested, this,
            &ToDoTreeWidgetHandler::handle_customMenuEvent);
}

void ToDoTreeWidgetHandler::handle_the_incoming_new_task_from_window() {
    auto result = createWindow->getTask();
    handle_new_add_task(result.first, result.second);
}

void ToDoTreeWidgetHandler::handle_new_add_task(Task*            inHeap,
                                                QTreeWidgetItem* parent) {
    // sync to the task handler
    tasksHandler.addTaskIntoManage(inHeap);
    Task* parent_task = nullptr;
    if (parent == handling_tree->invisibleRootItem()) {
        inHeap->set_no_parent();
    } else {
        parent_task = factory.fromItemOne(parent);
        // display for once
        inHeap->setparent_id(*parent_task);
        inHeap->setendAt(parent_task->getendAt());
        inHeap->setstartFrom(parent_task->getstartFrom());
    }

    // sync to the database
    DataBaseAdder::addTaskBack(*inHeap);

    // we gain the task number as direct
    factory.itemFromTask(inHeap, handling_tree, parent_task);
    emit tell_refresh_group();
}

void ToDoTreeWidgetHandler::setAsDragable(bool isDragable) {
    // 设置可以拖拽
    if (isDragable) {
        handling_tree->setDragEnabled(isDragable);
        handling_tree->setDragDropMode(QTreeView::InternalMove);
        handling_tree->setDefaultDropAction(Qt::MoveAction);
    } else {
        handling_tree->setDragEnabled(isDragable);
        handling_tree->setDragDropMode(QTreeView::NoDragDrop);
        handling_tree->setDefaultDropAction(Qt::IgnoreAction);
    }
}

void ToDoTreeWidgetHandler::setSortable(bool isSortable) {
    // 设置节点是可以排序的，当然，这个排序是根据QTreeWidgetItem的DDL排序（目前支持）!
    handling_tree->setSortingEnabled(isSortable);
}

void ToDoTreeWidgetHandler::sortByDDLDate(Qt::SortOrder order) {
    handling_tree->sortItems(TaskTreeWidegtItemFactory::ColumnIndex::DeadLine,
                             order);
}

/*
 *   Followings are the things that handle the slots of menu reactions
 */

void ToDoTreeWidgetHandler::handle_add_action() {
    qDebug() << "Action of add triggers";

    qDebug() << "current item" << handling_tree->currentItem();
    createWindow->setCreatingParent(handling_tree->currentItem());
    createWindow->setDefaultDateTime(editBaseTime);
    createWindow->show();
    // our task will async return, see handle_the_incoming_new_task
}

void ToDoTreeWidgetHandler::handle_add_root_action() {
    qDebug() << "Add to top level!";
    createWindow->setCreatingParent(handling_tree->invisibleRootItem());
    createWindow->setDefaultDateTime(editBaseTime);
    createWindow->show();
    // our task will async return, see handle_the_incoming_new_task
}

void ToDoTreeWidgetHandler::handle_display_action() {
    qDebug() << "Display!";

    // get the task
    auto  item = handling_tree->currentItem();
    Task* task = factory.fromItemOne(item);
    if (!task) {
        qFatal() << "Things shouldn't be like this!";
        return;
    }

    emit tellDisplayTask(task, item);
}

void ToDoTreeWidgetHandler::handle_copy_action() {
    // register the copy sign
    Task* clone_one = nullptr;
    if (handling_tree->currentItem()) {
        Task* sourceTask = factory.fromItemOne(handling_tree->currentItem());
        clone_one        = TaskFactory::toHeap(*sourceTask);
    }
    copy_paste_memo = {handling_tree->currentItem(), nullptr, clone_one};
}

void ToDoTreeWidgetHandler::handle_paste_action() {
    if (!copy_paste_memo.copyItem) {
        emit tell_no_source_copy_error();
        return;
    }

    auto possible_dest = handling_tree->currentItem();
    if (!possible_dest) {
        qDebug() << "no dest, set as the root as the default!";
        possible_dest = handling_tree->invisibleRootItem();
    }

    copy_paste_memo.pasteItem = possible_dest;
    Task* clone_one           = copy_paste_memo.holding_copy;
    handle_new_add_task(clone_one, copy_paste_memo.pasteItem);
}

static void findAllSub(QTreeWidgetItem* item, QList<QTreeWidgetItem*>& removes,
                       QTreeWidget* widget) {
    if (!item) return;
    const int CHILD_CNT = item->childCount();
    for (int i = 0; i < CHILD_CNT; i++) {
        auto child = item->child(i);
        findAllSub(child, removes, widget);
        removes << child;
    }
    removes << item;
}

static void delete_this(QTreeWidgetItem* item) {
    if (!item) return;
    const int CHILD_CNT = item->childCount();
    for (int i = 0; i < CHILD_CNT; i++) {
        auto child = item->child(i);
        delete_this(child);
    }
    delete item;
}

bool ToDoTreeWidgetHandler::handle_delete_action() {
    qDebug() << "Action of delete triggers";

    CCToDoTreeWidgetItem* item =
        dynamic_cast<CCToDoTreeWidgetItem*>(handling_tree->currentItem());

    if (!item) return false;  //

    QList<QTreeWidgetItem*> removeItems;

    // find all the sub items
    findAllSub(item, removeItems, handling_tree);

    // find the task holdings
    QList<Task*> removeTasks;
    for (const auto& item : removeItems) {
        auto task = factory.fromItemOne(item);
        if (task) removeTasks << task;
    }

    if (removeTasks.size() != removeItems.size())
        qFatal() << "Tasks and items are not in the same size!";
    // unmap the task and items
    factory.makeUnmap(removeItems);

    // sync to database
    DatabaseDeleter::deleteTaskInDataBase(removeTasks);

    // release handlings
    tasksHandler.releaseTargetSources(removeTasks);

    delete_this(item);

    qDebug() << "finished!";
    emit tell_refresh_group();
    return true;
}

/*
    This function suffers me at 2024.11.8, I fixed the simplified the
    logic to this function, and it works well, at least right... for now
    Written on 2024.11.9 :)

    Function shell add a patch of tasks to the treeWidget, the tasks can be
    multilevels, so i write a recursive function to handle the task tree
    by loop, i am afraid of using recursive function, as it may cause stack
    crash :)
*/

void ToDoTreeWidgetHandler::setTasks(QList<Task*> org_handlingTask) {
    QList<Task*> childishTask;

    tasksHandler.setManage(org_handlingTask);

    QList<Task*> handlingTask = tasksHandler.borrowsFrom();

    for (const auto& task : handlingTask) {
        // if is parent
        if (task->getparent_id() != Task::INVALID_DB_ID) {
            childishTask << task;
        } else {
            auto item = factory.itemFromTask(task, handling_tree);
            handling_tree->addTopLevelItem(item);
        }
    }

    int hit_count = 0;

    while (!childishTask.empty()) {
        QList<Task*> this_time_children = childishTask;
        for (const auto& child : this_time_children) {
            auto parent_task =
                TaskHelpUtils::queryTempTaskInList(*child, handlingTask);
            QTreeWidgetItem* parent_item = factory.fromTask(parent_task);
            // check if the hit count satisfied the check
            // if not, we convience the child should be root
            // it is possible that the parent isn't on the list
            // so we handle it as the root
            // God knows the fucking logic sucks me up!
            if (hit_count > 2) {
                qDebug() << "find orphand node, set as root ";
                auto item = factory.itemFromTask(child, handling_tree);
                handling_tree->addTopLevelItem(item);
                childishTask.removeOne(child);
                hit_count = 0;
                continue;
            }

            if (!parent_task || !parent_item) {
                hit_count++;
                continue;  // actually if some task is other
                           // child-levels, we continue, as
                           // the child has no widgetItem to
                           // be parents!
            }

            // add to treeItem as child
            if (parent_item) {
                auto child_item =
                    factory.itemFromTask(child, handling_tree, parent_task);
                parent_item->addChild(child_item);
                // remove
                childishTask.removeOne(child);
            }
        }
    }
}

void ToDoTreeWidgetHandler::clearAll() {
    handling_tree->clear();
    factory.clearHolds();
}

QList<Task*> ToDoTreeWidgetHandler::borrowFrom() const {
    return tasksHandler.borrowsFrom();
}

void ToDoTreeWidgetHandler::receiveHandleOfDrags(QTreeWidgetItem* new_parent,
                                                 QTreeWidgetItem* beDragged) {
    qDebug() << "Received! start process update!";
    // check its new parent!

    Task* parent_task = factory.fromItemOne(new_parent);
    Task* child_task  = factory.fromItemOne(beDragged);

    if (!child_task) {
        // things won't happen, make cricital
        qFatal() << "Opps! child itself is empty! crash shell be!";
        return;
    }

    if (!parent_task) {
        qDebug() << "This is root one!";
        // set as the root task, disable the parent_id
        child_task->set_no_parent();
    } else {
        qDebug() << "This is the parent one";
        child_task->setparent_id(*parent_task);
        child_task->setendAt(parent_task->getendAt());
        child_task->setstartFrom(parent_task->getstartFrom());
    }

    // sync to database
    DataBaseUpdater::updateTargetTask(*child_task);
    // inform the refresh message to the mainWindow
    emit tell_refresh_group();
}

void ToDoTreeWidgetHandler::handle_value_change() {
    qDebug() << "Received! start process update! ";
    qDebug() << "Start check the signals change";
    auto  item = handling_tree->currentItem();
    Task* task = factory.fromItemOne(item);
    if (!task) {
        qFatal() << "Opps! task itself is empty! crash shell be!";
        return;
    }

    factory.modifiedAccordingItems(*task, item);

    // sync to database
    DataBaseUpdater::updateTargetTask(*task);
    // inform the refresh message to the mainWindow
    emit tell_refresh_group();
}

QMenu* ToDoTreeWidgetHandler::handle_plain_menu(
    CCToDoTreeWidget* special_tree) {
    QMenu* res = menuFactory->fetchMenuOnNoItem(special_tree);
    if (!copy_paste_memo.isPastable()) {
        // disable the paste action
        // first we need to find him
        auto actionLists = res->findChildren<QAction*>();
        for (const auto& each : actionLists) {
            if (each->text() == CCToDoTreeCustomMenuFactory::MenuName::PASTE) {
                each->setEnabled(false);
            }
        }
    }
    return res;
}

QMenu* ToDoTreeWidgetHandler::handle_special_menu(
    CCToDoTreeWidget* special_tree) {
    QMenu* res = menuFactory->fetchMenu(special_tree);
    if (!copy_paste_memo.isPastable()) {
        // disable the paste action
        // first we need to find him
        auto actionLists = res->findChildren<QAction*>();
        for (const auto& each : actionLists) {
            if (each->text() == CCToDoTreeCustomMenuFactory::MenuName::PASTE) {
                each->setEnabled(false);
            }
        }
    }
    return res;
}

void ToDoTreeWidgetHandler::handle_customMenuEvent(const QPoint& point) {
    qDebug() << "Custom Menu shell works!";

    // handle the special tree
    auto special_tree = dynamic_cast<CCToDoTreeWidget*>(handling_tree);
    if (special_tree) {
        // now that we suppose to handle the special tree event

        CCToDoTreeWidgetItem* item =
            dynamic_cast<CCToDoTreeWidgetItem*>(special_tree->itemAt(point));

        if (!item) {
            // this means that we are pointing at root
            QMenu* plain_menu = handle_plain_menu(special_tree);
            plain_menu->exec(QCursor::pos());
        } else {
            QMenu* special_menu = handle_special_menu(special_tree);
            special_menu->exec(QCursor::pos());
        }
    }
}
