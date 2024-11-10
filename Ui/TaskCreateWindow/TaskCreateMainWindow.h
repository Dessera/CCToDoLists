#ifndef TASKCREATEMAINWINDOW_H
#define TASKCREATEMAINWINDOW_H
#include <QMainWindow>
#include "Task.h"
namespace Ui {
class TaskCreateMainWindow;
}

class QTreeWidgetItem;

class TaskCreateMainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit TaskCreateMainWindow(QWidget *parent = nullptr);
    ~TaskCreateMainWindow();
    static constexpr const int       ALLOWED_MIN_INTERVAL_SEC = 60 * 60;
    QPair<Task *, QTreeWidgetItem *> getTask() {
        collectsAll();
        return {TaskFactory::toHeap(modify_template), item};
    }
    /* It's wired that the show is not the virtual function, so I Have to
     * pretend that it is virtual, Welp, It only display critical box, if
     * users do not assigned to tell which tree item he wanna to add and create!
     */
    void show();
    void setCreatingParent(QTreeWidgetItem *parent) {
        item = parent;
    }
    void setDefaultDateTime(const QDateTime &start);
signals:
    void tellFetchTask();
public slots:
    void closeEvent(QCloseEvent *event);
private slots:
    void on_dateTimeEdit_startTime_dateTimeChanged(const QDateTime &dateTime);

    void on_dateTimeEdit_endTime_dateTimeChanged(const QDateTime &dateTime);

    void on_mainTaskEdit_editingFinished();

    void on_btn_cancel_clicked();

    void on_btn_create_clicked();

private:
    void collectsAll();
    void initComboBox();
    void initDateTimeEdits();

    /* This is the modifying template */
    Task modify_template = TaskFactory::createTask();
    /* is canceled sessions */
    bool isCancelSessions{false};
    /*
     * borrowing the parent treeWidgetItem, at the close will reset to nullptr
     */
    QTreeWidgetItem          *item{nullptr};
    Ui::TaskCreateMainWindow *ui;
};

#endif  // TASKCREATEMAINWINDOW_H
