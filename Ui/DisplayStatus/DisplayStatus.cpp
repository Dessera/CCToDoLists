#include "DisplayStatus.h"
#include <QBarSet>
#include <QChart>
#include <QPieSeries>
#include <QPieSlice>
#include <QStackedBarSeries>
#include "ui_DisplayStatus.h"

DisplayStatus::DisplayStatus(QWidget *parent)
    : QWidget(parent), ui(new Ui::DisplayStatus) {
    ui->setupUi(this);
    init_pieCharts();
    init_columnCharts();
}

void DisplayStatus::init_pieCharts() {
    pie_Chart = std::make_unique<QChart>();
    ui->pieChartView->setChart(pie_Chart.get());
    pie_Chart->setTitle("任务进度");
    pie_Chart->legend()->setVisible(true);
    pie_Chart->legend()->setAlignment(Qt::AlignBottom);
}

void DisplayStatus::init_columnCharts() {
    column_Chart = std::make_unique<QChart>();
    ui->column_chartView->setChart(column_Chart.get());
    column_Chart->setTitle("任务进度");
    column_Chart->legend()->setVisible(true);
    column_Chart->legend()->setAlignment(Qt::AlignBottom);
}

void DisplayStatus::setTaskLists(QList<Task *> tasks) {
    ui->label_index->setText(
        QString("现在统计的总任务数: %1").arg(tasks.size()));
    handles.setManage(tasks);
    freshCharts();
}

void DisplayStatus::setDateShow(const QDate &date) {
    ui->label_date->setText(date.toString("yyyy-MM-dd"));
}

static QPair<int, int> anlysisTask(const QList<Task *> &be_checked) {
    // find the checked tasks with whom are children

    int finished   = 0;
    int unfinished = 0;

    // then checked the children checked
    for (const auto &child : be_checked) {
        if (child->getisFinished()) {
            finished++;
        } else {
            unfinished++;
        }
    }
    return {finished, unfinished};
}

QPieSeries *DisplayStatus::SeriesFactory::createPieSeries(
    FinishedIndex finished, UnfinishedIndex unfinished) {
    int total = finished + unfinished;
    if (total == 0) {
        qFatal() << "Oh how could this be????";
        return nullptr;
    }
    QPieSeries *pieSeries = new QPieSeries();

    pieSeries->append("已完成", finished);

    QPieSlice *slice1 = pieSeries->slices().at(0);
    slice1->setLabel(QString("已完成 %1%")
                         .arg(QString::number((float)finished * 100 / total)));

    pieSeries->append("未完成", unfinished);
    QPieSlice *slice2 = pieSeries->slices().at(1);
    slice2->setLabel(
        QString("未完成 %1%")
            .arg(QString::number((float)unfinished * 100 / total)));
    return pieSeries;
}

QStackedBarSeries *DisplayStatus::SeriesFactory::createBarSet(
    FinishedIndex finished, UnfinishedIndex unfinished) {
    QStackedBarSeries *barSet = new QStackedBarSeries();
    QBarSet           *set =
        new QBarSet(QString("已完成个数: %1").arg(QString::number(finished)));
    *set << finished;
    QBarSet *set2 =
        new QBarSet(QString("未完成个数: %1").arg(QString::number(unfinished)));
    *set2 << unfinished;
    barSet->append(set);
    barSet->append(set2);
    return barSet;
}

void DisplayStatus::freshCharts() {
    pie_Chart->removeAllSeries();
    column_Chart->removeAllSeries();
    auto result = ::anlysisTask(handles.borrowsFrom());
    int  total  = result.first + result.second;
    if (total == 0) {
        return;
    }
    QPieSeries *pieSeries =
        factory.createPieSeries(result.first, result.second);

    QStackedBarSeries *barSet =
        factory.createBarSet(result.first, result.second);

    pie_Chart->addSeries(pieSeries);
    column_Chart->addSeries(barSet);
}

DisplayStatus::~DisplayStatus() {
    delete ui;
}
