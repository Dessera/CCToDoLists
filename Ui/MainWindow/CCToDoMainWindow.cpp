#include "CCToDoMainWindow.h"
#include <QKeyEvent>
#include <QMessageBox>
#include "Core/MarkdownUtils/MarkDownUtils.h"
#include "MainWindowExternWidgetIniter.h"
#include "MarkDownImportWindow/MarkDownImportWindow.h"
#include "MarkdownExportWindow/MarkdownExportWindow.h"
#include "TaskCreateManager.h"
#include "TaskCreateWindow/TaskCreateMainWindow.h"
#include "TaskDisplayWindow/TaskDisplayDialog.h"
#include "ToDoTreeWidgetHandler/ToDoTreeWidgetHandler.h"
#include "ui_CCToDoMainWindow.h"

#ifdef REQ_TEST

// if you require test, and check the target task is in the list
// uncomment the following line
// #include "TestHelpUtils.h"
#include "TestSources.h"  // this provides the sources insertive to database
#endif

#if defined(_MSC_VER) && defined(ON_DEBUG)
// In MSVC, you can use the following code to enable the memory leak check
// welp, you have to find solutions if u are using mingw-g++
// in linux, i suggests the valgrind :)
#include <vld.h>
#endif

CCToDoMainWindow::CCToDoMainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::CCToDoMainWindow) {
    ui->setupUi(this);
    MainWindowExternWidgetIniter::initializeThis(this);
    initConnections();
    initDatas();
    MainWindowExternWidgetIniter::initializeAfterOpenDataBase(this);
    MainWindowExternWidgetIniter::final_initializing_ui_adjust(this);
}

void CCToDoMainWindow::focusOnDate(const QDate& date) {
    ui->label->setText(date.toString("yyyy-MM-dd"));
    dateTreeHandler->clearAll();
    auto result = TaskCreateManager::gainDateTask(date);
    dateTreeHandler->setTasks(result);
    dateTreeHandler->setEditBaseTime({date, QTime(0, 0, 0)});
}

void CCToDoMainWindow::initConnections() {
    // connect the actions
    // add from window
    connect(ui->action_addFromWindow, &QAction::triggered, this,
            &CCToDoMainWindow::open_TaskCreatorWindow);
    connect(ui->action_newTask, &QAction::triggered, this,
            &CCToDoMainWindow::open_TaskCreatorWindow);
    connect(ui->action_locate_today, &QAction::triggered, this,
            &CCToDoMainWindow::focusOnToday);
    connect(ui->action_look_previous, &QAction::triggered, this,
            &CCToDoMainWindow::on_btn_to_previousDay_clicked);
    connect(ui->action_look_next, &QAction::triggered, this,
            &CCToDoMainWindow::on_btn_to_nextDay_clicked);
    connect(dateTreeHandler.get(), &ToDoTreeWidgetHandler::tellDisplayTask,
            this, &CCToDoMainWindow::handle_tell_display);
    connect(dateTreeHandler.get(), &ToDoTreeWidgetHandler::tell_refresh_group,
            this, &CCToDoMainWindow::handle_refresh_group);
    connect(
        dateTreeHandler.get(),
        &ToDoTreeWidgetHandler::tell_no_source_copy_error, this, [=]() {
            statusBar()->showMessage("没有地址源！请选择一个项目进行复制！");
        });

    connect(ui->action_importMarkDown, &QAction::triggered, this,
            &CCToDoMainWindow::handle_start_markdown_import);
    connect(&importer, &MarkdownImporter::parseFinish, this,
            &CCToDoMainWindow::handle_open_markdown_window);

    // exports
    connect(ui->action_save_on_date_display, &QAction::triggered, this,
            &CCToDoMainWindow::handle_open_export_window_by_action);
    connect(ui->action_save_ddl, &QAction::triggered, this,
            &CCToDoMainWindow::handle_open_export_window_by_action);
    connect(ui->action_save_high_priority, &QAction::triggered, this,
            &CCToDoMainWindow::handle_open_export_window_by_action);
    connect(ui->action_save_recent, &QAction::triggered, this,
            &CCToDoMainWindow::handle_open_export_window_by_action);

    connect(ui->action_on_insert_at_current_date, &QAction::triggered,
            dateTreeHandler.get(),
            &ToDoTreeWidgetHandler::handle_add_root_action);

    // resize this, to see a big picture
    connect(ui->dock_view_todo, &QDockWidget::topLevelChanged, this,
            [=]() { ui->dock_view_todo->resize(this->size()); });
}

void CCToDoMainWindow::initDatas() {
    if (!open_dataBase()) {
        handle_error_in_open_database();
    }
}

void CCToDoMainWindow::open_TaskCreatorWindow() {
    dateTreeHandler->handle_add_root_action();
}

void CCToDoMainWindow::handle_refresh_group() {
    // refresh groups if there is any modification
    refreshGroups();
}

void CCToDoMainWindow::refreshGroups() {
    /* set sources */
    todaySpecailHandler->clearAll();
    auto result = TaskCreateManager::gainTodaysTask();
    todaySpecailHandler->setTasks(result);
    result.clear();
    result = TaskCreateManager::gainInWeekTask();
    weekSpecailHandler->clearAll();
    weekSpecailHandler->setTasks(result);
    weekSpecailHandler->setSortable(true);
    weekSpecailHandler->sortByDDLDate();
    result.clear();
    result = TaskCreateManager::gainHighPriorityTask();
    highPriorityHandler->clearAll();
    highPriorityHandler->setTasks(result);
    qDebug() << "Refresh status widget";
    refreshStatusWidget();
    MainWindowExternWidgetIniter::makeResizeAsContext(
        ui->treeWidget_group_recentWeek);
    MainWindowExternWidgetIniter::makeResizeAsContext(
        ui->treeWidget_group_today);
    MainWindowExternWidgetIniter::makeResizeAsContext(
        ui->treeWidget_highPriority);
}

void CCToDoMainWindow::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Delete) {
        handle_key_deletions();
    } else if (event->key() == Qt::Key_C && event->modifiers() == Qt::CTRL) {
        handle_key_copy();
    } else if (event->key() == Qt::Key_V && event->modifiers() == Qt::CTRL) {
        handle_key_paste();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void CCToDoMainWindow::handle_key_deletions() {
    bool res = dateTreeHandler->handle_delete_action();
    if (!res) {
        statusBar()->showMessage("没有选中的目标对象！请选择一个再删除！");
    } else {
        statusBar()->showMessage("删除成功！");
    }
    return;
}

void CCToDoMainWindow::handle_key_copy() {
    dateTreeHandler->handle_copy_action();
}

void CCToDoMainWindow::handle_key_paste() {
    dateTreeHandler->handle_paste_action();
}

void CCToDoMainWindow::refreshStatusWidget() {
    ui->status_widget->setDateShow(QDate::currentDate());
    ui->status_widget->setTaskLists(TaskCreateManager::gainTodaysTask());
}

void CCToDoMainWindow::handle_tell_display(Task* task, QTreeWidgetItem* item) {
    TaskDisplayDialog dialog;
    dialog.setTasksForDisplay(task, item);
    dialog.exec();
}

bool CCToDoMainWindow::open_dataBase() {
    return dataBase.getInstance()->open_database(
        "data/dataBase/TodoDataBase.db");
}

void CCToDoMainWindow::handle_error_in_open_database() {
    qDebug() << "Error occurs when open the database";
}

CCToDoMainWindow::~CCToDoMainWindow() {
    delete ui;
}

void CCToDoMainWindow::on_btn_to_nextDay_clicked() {
    QDate date = QDate::fromString(ui->label->text(), "yyyy-MM-dd");
    date       = date.addDays(1);
    focusOnDate(date);
}

void CCToDoMainWindow::on_btn_to_previousDay_clicked() {
    QDate date = QDate::fromString(ui->label->text(), "yyyy-MM-dd");
    date       = date.addDays(-1);
    focusOnDate(date);
}

void CCToDoMainWindow::handle_start_markdown_import() {
    QString filePath = MarkDownUtils::fetchTargetMarkdownPath(this);
    if (filePath.isEmpty()) {
        return;
    }

    importer.setParseSource(filePath);
    auto ids = importer.parse();
    if (!ids.has_value()) {
        QMessageBox::critical(this, "解析错误！",
                              importer.displayErrorStatus());
        return;
    }
    // call in async way, to the handle_open_markdown_window
    // to see the next step
}

void CCToDoMainWindow::handle_open_markdown_window(QList<int> ids) {
    if (!markdownImportWindow) {
        markdownImportWindow = std::make_unique<MarkDownImportWindow>(this);
        connect(markdownImportWindow.get(),
                &MarkDownImportWindow::tell_shell_refresh_all, this, [=]() {
                    refreshGroups();
                    focusOnToday();
                });
    }

    markdownImportWindow->setTargets(ids);
    markdownImportWindow->show();
}

void CCToDoMainWindow::handle_open_export_window_by_action() {
    QAction* act = qobject_cast<QAction*>(sender());
    if (act == ui->action_save_on_date_display) {
        handle_open_markdown_export_window(dateTreeHandler.get());
    } else if (act == ui->action_save_high_priority) {
        handle_open_markdown_export_window(highPriorityHandler.get());
    } else if (act == ui->action_save_recent) {
        handle_open_markdown_export_window(weekSpecailHandler.get());
    } else if (act == ui->action_save_ddl) {
        handle_open_markdown_export_window(todaySpecailHandler.get());
    }
}

void CCToDoMainWindow::handle_open_markdown_export_window(
    ToDoTreeWidgetHandler* handler) {
    if (!markdownExportWindow) {
        markdownExportWindow = std::make_unique<MarkdownExportWindow>(this);
        markdownExportWindow->setTreeHandler(handler);
    }
    markdownExportWindow->setTreeHandler(handler);
    markdownExportWindow->show();
}

void CCToDoMainWindow::on_calendarWidget_activated(const QDate& date) {
    focusOnDate(date);
}
