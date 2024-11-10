#ifndef CCTODOMAINWINDOW_H
#define CCTODOMAINWINDOW_H

#include <QDate>
#include <QMainWindow>
#include "CCToDoDataBase.h"
#include "MarkDownParser/Importer/MarkdownImporter.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class CCToDoMainWindow;
}
QT_END_NAMESPACE

class TaskCreateMainWindow;
class ToDoTreeWidgetHandler;
class MarkDownImportWindow;
class MarkdownExportWindow;

class Task;
class QTreeWidgetItem;

class CCToDoMainWindow : public QMainWindow {
    Q_OBJECT

public:
    CCToDoMainWindow(QWidget *parent = nullptr);
    void inline focusOnToday() {
        focusOnDate(QDate::currentDate());
    }
    // func name tells everything, gosh
    void refreshGroups();
    void refreshStatusWidget();
    ~CCToDoMainWindow();
public slots:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void open_TaskCreatorWindow();
    void handle_error_in_open_database();
    void handle_refresh_group();
    void handle_tell_display(Task *task, QTreeWidgetItem *item);
    void handle_start_markdown_import();
    void on_btn_to_nextDay_clicked();
    void on_btn_to_previousDay_clicked();
    void on_calendarWidget_activated(const QDate &date);
    void handle_open_markdown_window(QList<int> result);
    void handle_open_export_window_by_action();

    void handle_key_deletions();
    void handle_key_copy();
    void handle_key_paste();

private:
    bool open_dataBase();
    void initConnections();
    void initDatas();
    void focusOnDate(const QDate &date);
    void handle_open_markdown_export_window(ToDoTreeWidgetHandler *handler);
    friend struct MainWindowExternWidgetIniter;
    CCToDoDataBase                         dataBase;
    MarkdownImporter                       importer;
    std::unique_ptr<MarkDownImportWindow>  markdownImportWindow{nullptr};
    std::unique_ptr<MarkdownExportWindow>  markdownExportWindow{nullptr};
    std::unique_ptr<ToDoTreeWidgetHandler> dateTreeHandler{nullptr};
    std::unique_ptr<ToDoTreeWidgetHandler> todaySpecailHandler{nullptr};
    std::unique_ptr<ToDoTreeWidgetHandler> weekSpecailHandler{nullptr};
    std::unique_ptr<ToDoTreeWidgetHandler> highPriorityHandler{nullptr};
    std::unique_ptr<ToDoTreeWidgetHandler> importerTreeHandler{nullptr};
    Ui::CCToDoMainWindow                  *ui;
};
#endif  // CCTODOMAINWINDOW_H
