#ifndef TASKDISPLAYDIALOG_H
#define TASKDISPLAYDIALOG_H
#include <QDialog>
#include <QTimer>
class Task;
namespace Ui {
class TaskDisplayDialog;
}

class QTreeWidgetItem;
class QChart;
class QPieSeries;
class TaskDisplayDialog : public QDialog {
    Q_OBJECT

public:
    using FinishedIndex   = int;
    using UnfinishedIndex = int;
    explicit TaskDisplayDialog(QWidget *parent = nullptr);
    /* item is to indicate the percentage we finish */
    void setTasksForDisplay(Task *task, QTreeWidgetItem *item);
    ~TaskDisplayDialog();
    virtual int exec() override;
public slots:
    void updateTimeDDLLabel();
    void closeEvent(QCloseEvent *event) override;

private:
    struct PieSliceStyleFactory {
        static QPieSeries *createPieSeries(
            const QPair<FinishedIndex, UnfinishedIndex> &result);
    };

    Ui::TaskDisplayDialog                *ui;
    void                                  initPieView();
    void                                  initConnections();
    void                                  initProgressBar();
    void                                  handle_newSet();
    QPair<FinishedIndex, UnfinishedIndex> analysisTreeWidget();
    void drawPie(const QPair<FinishedIndex, UnfinishedIndex> &result);

    std::shared_ptr<QChart> chart_handle;
    QPieSeries             *pieSeries;
    Task                   *borrowed_task{nullptr};
    QTreeWidgetItem        *borrowed_item{nullptr};
    QTimer                  secondsTimer;
};

#endif  // TASKDISPLAYDIALOG_H
