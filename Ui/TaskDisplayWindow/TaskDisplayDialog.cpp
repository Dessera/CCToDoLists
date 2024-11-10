#include "TaskDisplayDialog.h"
#include <QPieSeries>
#include <QPieSlice>
#include <QTreeWidgetItem>
#include "Task.h"
#include "TaskHelpUtils.h"
#include "ui_TaskDisplayDialog.h"

QPieSeries* TaskDisplayDialog::PieSliceStyleFactory::createPieSeries(
    const QPair<FinishedIndex, UnfinishedIndex>& result) {
    int         total     = result.first + result.second;
    QPieSeries* pieSeries = new QPieSeries();
    pieSeries->append("已完成", result.first);

    /* Decorate the first slice */
    QPieSlice* slice1 = pieSeries->slices().at(0);
    slice1->setLabel(
        QString("已完成 %1%")
            .arg(QString::number((float)result.first * 100 / total)));
    pieSeries->append("未完成", result.second);

    /* Decorate the second slice */
    QPieSlice* slice2 = pieSeries->slices().at(1);
    slice2->setLabel(
        QString("未完成 %1%")
            .arg(QString::number((float)result.second * 100 / total)));

    /* Set hole size */
    pieSeries->setHoleSize(0.35);
    return pieSeries;
}

TaskDisplayDialog::TaskDisplayDialog(QWidget* parent)
    : QDialog(parent), ui(new Ui::TaskDisplayDialog) {
    ui->setupUi(this);
    setModal(true);
    initPieView();
    initProgressBar();
    initConnections();
}

void TaskDisplayDialog::initConnections() {
    connect(&secondsTimer, &QTimer::timeout, this,
            &TaskDisplayDialog::updateTimeDDLLabel);
}

void TaskDisplayDialog::initProgressBar() {
    ui->progressBar->setFormat("%p%的时间！");
}

void TaskDisplayDialog::initPieView() {
    chart_handle = std::make_shared<QChart>();
    ui->pieChartView->setChart(chart_handle.get());
    chart_handle->setTitle("任务进度");
    chart_handle->legend()->setVisible(true);
    chart_handle->legend()->setAlignment(Qt::AlignBottom);
}

int TaskDisplayDialog::exec() {
    secondsTimer.start(1000);
    // call the father show for the default behavior
    return QDialog::exec();
}

/*
    These are handles ready for display the tasks
*/
void TaskDisplayDialog::setTasksForDisplay(Task* task, QTreeWidgetItem* item) {
    borrowed_task = task;
    borrowed_item = item;
    handle_newSet();
}

void TaskDisplayDialog::handle_newSet() {
    ui->label_main_descriptions->setText("主要任务描述: \n" +
                                         borrowed_task->getmainTask());
    ui->label_endTime->setText(
        QString("DDL时间是 %1")
            .arg(TaskHelpUtils::toDateTime(borrowed_task->getendAt())));
    qint64 peroid =
        borrowed_task->getstartFrom().secsTo(borrowed_task->getendAt());
    ui->progressBar->setRange(0, peroid);
    auto result = analysisTreeWidget();
    drawPie(result);
    ui->description_edit->setPlainText(borrowed_task->getdescription());
    ui->label_priority->setText(
        QString("优先级: %1")
            .arg(TaskHelpUtils::gainPriorityString(*borrowed_task)));
}

static void collectInfo(QTreeWidgetItem*                    item,
                        TaskDisplayDialog::FinishedIndex&   finished,
                        TaskDisplayDialog::UnfinishedIndex& unfinished) {
    int children_size = item->childCount();

    if (children_size == 0) {
        if (item->checkState(0) == Qt::Checked) {
            finished++;
        } else {
            unfinished++;
        }
        return;
    }

    for (int i = 0; i < children_size; i++) {
        collectInfo(item->child(i), finished, unfinished);
    }
    return;
}

QPair<TaskDisplayDialog::FinishedIndex, TaskDisplayDialog::UnfinishedIndex>
TaskDisplayDialog::analysisTreeWidget() {
    FinishedIndex   finished   = 0;
    UnfinishedIndex unfinished = 0;
    collectInfo(borrowed_item, finished, unfinished);
    return {finished, unfinished};
}

void TaskDisplayDialog::drawPie(
    const QPair<TaskDisplayDialog::FinishedIndex,
                TaskDisplayDialog::UnfinishedIndex>& result) {
    chart_handle->removeAllSeries();

    // using in display
    // exception check

    pieSeries = PieSliceStyleFactory::createPieSeries(result);

    // add it to the chart
    chart_handle->addSeries(pieSeries);
}

void TaskDisplayDialog::updateTimeDDLLabel() {
    qDebug() << "Updating ddl lables...";

    if (borrowed_task->getendAt() < QDateTime::currentDateTime()) {
        ui->progressBar->setRange(0, 0);
        ui->progressBar->setFormat("已经超时！");
        ui->label_time_remain->setText("已经超时！");
        return;
    } else if (borrowed_task->getstartFrom() > QDateTime::currentDateTime()) {
        ui->progressBar->setRange(0, 0);
        ui->progressBar->setFormat("任务尚未开始！");
        ui->label_time_remain->setText("任务尚未开始！");
        return;
    }

    qint64 remain =
        QDateTime::currentDateTime().secsTo(borrowed_task->getendAt());
    ui->progressBar->setValue(remain);
    qDebug() << remain;
    qDebug() << borrowed_task->getendAt().secsTo(QDateTime::currentDateTime());

    ui->label_time_remain->setText(
        QString("预计的DDL剩余时间: %1")
            .arg(QTime::fromMSecsSinceStartOfDay(remain * 1000)
                     .toString("hh:mm:ss")));
}

void TaskDisplayDialog::closeEvent(QCloseEvent* event) {
    secondsTimer.stop();
    event->accept();
}

TaskDisplayDialog::~TaskDisplayDialog() {
    delete ui;
}
