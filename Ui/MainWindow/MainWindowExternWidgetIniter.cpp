#include "MainWindowExternWidgetIniter.h"
#include <QGraphicsOpacityEffect>
#include "CCToDoMainWindow.h"
#include "CCToDoTreeDelegate/CCToDoTreeWidgetDelegate.h"
#include "TaskCreateManager.h"
#include "ToDoTreeWidgetHandler/ToDoTreeWidgetHandler.h"
#include "UiSources/UiSources.h"
#include "ui_CCToDoMainWindow.h"

void MainWindowExternWidgetIniter::makeResizeAsContext(QTreeWidget* widget) {
    for (int i = 0; i < widget->columnCount(); i++) {
        widget->resizeColumnToContents(i);
    }
}

void MainWindowExternWidgetIniter::initializeThis(CCToDoMainWindow* window) {
    initialize_tree_viewdock(window);
}

void MainWindowExternWidgetIniter::initializeAfterOpenDataBase(
    CCToDoMainWindow* window) {
    initDateWidgets(window);
    initGroupTabs(window);
}

void MainWindowExternWidgetIniter::initialize_tree_viewdock(
    CCToDoMainWindow* window) {
    QStringList headers = UiSources::HeaderViewProviders::proviceCommonHeader();
    const int   cnt     = headers.count();
    window->ui->datetreeWidget_tasks->setColumnCount(cnt);
    window->ui->datetreeWidget_tasks->setHeaderLabels(headers);

    window->ui->treeWidget_group_today->setColumnCount(cnt);
    window->ui->treeWidget_group_today->setHeaderLabels(headers);

    window->ui->treeWidget_group_recentWeek->setColumnCount(cnt);
    window->ui->treeWidget_group_recentWeek->setHeaderLabels(headers);

    window->ui->treeWidget_highPriority->setColumnCount(cnt);
    window->ui->treeWidget_highPriority->setHeaderLabels(headers);

    window->dateTreeHandler = std::make_unique<ToDoTreeWidgetHandler>(
        window->ui->datetreeWidget_tasks);
    window->todaySpecailHandler = std::make_unique<ToDoTreeWidgetHandler>(
        window->ui->treeWidget_group_today);
    window->weekSpecailHandler = std::make_unique<ToDoTreeWidgetHandler>(
        window->ui->treeWidget_group_recentWeek);
    window->highPriorityHandler = std::make_unique<ToDoTreeWidgetHandler>(
        window->ui->treeWidget_highPriority);
}

void MainWindowExternWidgetIniter::initDateWidgets(CCToDoMainWindow* window) {
    /* set the label with todays data */
    window->ui->label->setText(QDate::currentDate().toString("yyyy-MM-dd"));
    /* Sepecial Settings on dateTreeWidget */

    window->dateTreeHandler->setSortable(true);
    window->dateTreeHandler->setAsDragable(true);

    window->focusOnToday();
    makeResizeAsContext(window->ui->datetreeWidget_tasks);
}

void MainWindowExternWidgetIniter::initGroupTabs(CCToDoMainWindow* window) {
    /* set enbale sources */
    window->refreshGroups();
}

void MainWindowExternWidgetIniter::final_initializing_ui_adjust(
    CCToDoMainWindow* window) {
    window->ui->datetreeWidget_tasks->resizeColumnToContents(0);
    initStatusWidget(window);
}

void MainWindowExternWidgetIniter::initStatusWidget(CCToDoMainWindow* window) {
    window->ui->status_widget->setDateShow(QDate::currentDate());
    window->ui->status_widget->setTaskLists(
        TaskCreateManager::gainTodaysTask());
}
