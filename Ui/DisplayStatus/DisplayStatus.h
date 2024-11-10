#ifndef DISPLAYSTATUS_H
#define DISPLAYSTATUS_H

#include <QChart>
#include <QWidget>
#include "TaskListsHandle/TaskListsHandle.h"
namespace Ui {
class DisplayStatus;
}

class QPieSeries;
class QStackedBarSeries;
class DisplayStatus : public QWidget {
    Q_OBJECT

public:
    explicit DisplayStatus(QWidget *parent = nullptr);
    void setTaskLists(QList<Task *> tasks);
    void setDateShow(const QDate &date);
    void freshCharts();
    ~DisplayStatus();

private:
    void init_pieCharts();
    void init_columnCharts();
    /* handle sources */
    TaskListsHandle    handles;
    Ui::DisplayStatus *ui;
    /* displaying chart */
    std::unique_ptr<QChart> pie_Chart;
    std::unique_ptr<QChart> column_Chart;

    using FinishedIndex   = int;
    using UnfinishedIndex = int;
    struct SeriesFactory {
        QPieSeries        *createPieSeries(FinishedIndex   finished,
                                           UnfinishedIndex unfinished);
        QStackedBarSeries *createBarSet(FinishedIndex   finished,
                                        UnfinishedIndex unfinished);
    } factory;
};

#endif  // DISPLAYSTATUS_H
