#include "TaskCreateMainWindow.h"
#include <QCloseEvent>
#include <QMessageBox>
#include "UiSources/UiSources.h"
#include "ui_TaskCreateMainWindow.h"
TaskCreateMainWindow::TaskCreateMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::TaskCreateMainWindow) {
    ui->setupUi(this);
    ui->mainTaskEdit->setLabel("请输入您的主干任务！");
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    initComboBox();
    initDateTimeEdits();
    setWindowTitle("创建一个任务");
}

void TaskCreateMainWindow::initDateTimeEdits() {
    ui->dateTimeEdit_startTime->setDateTime(
        QDateTime(QDate::currentDate().addDays(1), QTime(0, 0, 0)));
    ui->dateTimeEdit_endTime->setDateTime(
        QDateTime(QDate::currentDate().addDays(1), QTime(23, 59, 59)));
}

void TaskCreateMainWindow::initComboBox() {
    // Low Priority
    ui->comboBox_priority->addItem(UiSources::IconsStorage::lowPriorityIcon(),
                                   UiSources::PriorityMapForComboBox::Low);

    // Meidum
    ui->comboBox_priority->addItem(
        UiSources::IconsStorage::mediumPriorityIcon(),
        UiSources::PriorityMapForComboBox::Medium);

    // High
    ui->comboBox_priority->addItem(UiSources::IconsStorage::highPriorityIcon(),
                                   UiSources::PriorityMapForComboBox::High);
}

TaskCreateMainWindow::~TaskCreateMainWindow() {
    delete ui;
}

void TaskCreateMainWindow::setDefaultDateTime(const QDateTime &start) {
    ui->dateTimeEdit_startTime->setDateTime(start);
    ui->dateTimeEdit_endTime->setDateTime({start.date(), QTime(23, 59, 59)});
}

void TaskCreateMainWindow::show() {
    if (!item) {
        QMessageBox::critical(this, "发生错误", "请指定需要创建节点的父任务！");
        return;
    }
    QMainWindow::show();
}

void TaskCreateMainWindow::on_dateTimeEdit_startTime_dateTimeChanged(
    const QDateTime &dateTime) {
    if (dateTime >= ui->dateTimeEdit_endTime->dateTime()) {
        ui->dateTimeEdit_endTime->setDateTime(
            dateTime.addSecs(ALLOWED_MIN_INTERVAL_SEC));
    }
}

void TaskCreateMainWindow::on_dateTimeEdit_endTime_dateTimeChanged(
    const QDateTime &dateTime) {
    if (dateTime <= ui->dateTimeEdit_startTime->dateTime()) {
        ui->dateTimeEdit_startTime->setDateTime(
            dateTime.addSecs(-ALLOWED_MIN_INTERVAL_SEC));
    }
}

void TaskCreateMainWindow::on_mainTaskEdit_editingFinished() {
    qDebug() << ui->mainTaskEdit->text();
    modify_template.setmainTask(ui->mainTaskEdit->text());
}

void TaskCreateMainWindow::collectsAll() {
    modify_template.setpriority(static_cast<Task::TaskData::Priority>(
        ui->comboBox_priority->currentIndex()));
    modify_template.setgroupName("");
    modify_template.setdescription(ui->textEdit->toPlainText());
    modify_template.setstartFrom(ui->dateTimeEdit_startTime->dateTime());
    modify_template.setendAt(ui->dateTimeEdit_endTime->dateTime());
}

void TaskCreateMainWindow::closeEvent(QCloseEvent *event) {
    if (isCancelSessions) {
        event->accept();
        isCancelSessions = false;  // reset the flag
        return;
    }

    if (modify_template.getmainTask().isEmpty()) {
        QMessageBox::critical(
            this, "任务不允许为空！",
            "请确保你输入完成了你的任务(编辑框回车)或者，任务不允许是空的！");
        event->ignore();
        return;
    }
    event->accept();
    emit tellFetchTask();
}

void TaskCreateMainWindow::on_btn_cancel_clicked() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this, "真的放弃更改吗",
        "你确定要放弃更改吗？\n[不，我打算继续更改 | 是的，我要放弃更改 | "
        "我点错了！]",
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
        QMessageBox::Discard);

    if (reply == QMessageBox::Save) {
        return;  // nothing happens;
    } else if (reply == QMessageBox::Discard) {
        isCancelSessions = true;
        // set close this
        this->close();
    } else {
        return;
    }
}

void TaskCreateMainWindow::on_btn_create_clicked() {
    close();
}
