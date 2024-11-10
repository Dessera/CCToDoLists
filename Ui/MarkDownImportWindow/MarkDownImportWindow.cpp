#include "MarkDownImportWindow.h"
#include "DataBaseQuery.h"
#include "DataBaseUpdater.h"
#include "DatabaseDeleter.h"
#include "ToDoTreeWidgetHandler/ToDoTreeWidgetHandler.h"
#include "UiSources/UiSources.h"
#include "ui_MarkDownImportWindow.h"
MarkDownImportWindow::MarkDownImportWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MarkDownImportWindow) {
    ui->setupUi(this);
    initTree();
    initHandler();
    setWindowTitle("Markdown导入");
}

static void adjustToBase(QList<Task *> allTask) {
    for (const auto &each : allTask) {
        each->setstartFrom(QDateTime::currentDateTime());
        each->setendAt(QDateTime(QDate::currentDate(), QTime(23, 59, 59)));
    }
}

void MarkDownImportWindow::initTree() {
    auto header = UiSources::HeaderViewProviders::proviceCommonHeader();
    ui->modifyingWidget->setColumnCount(header.count());
    ui->modifyingWidget->setHeaderLabels(header);
}

void MarkDownImportWindow::initHandler() {
    handler = std::make_shared<ToDoTreeWidgetHandler>(ui->modifyingWidget);
}

void MarkDownImportWindow::setTargets(const QList<int> &ids) {
    auto fetchFromDatabase = DataBaseQuery::queryByIDs(ids);
    adjustToBase(fetchFromDatabase);
    handler->setTasks(fetchFromDatabase);
}

MarkDownImportWindow::~MarkDownImportWindow() {
    delete ui;
}

void MarkDownImportWindow::on_btn_cancel_clicked() {
    close();
}

void MarkDownImportWindow::removeAll() {
    const auto allTask = handler->borrowFrom();
    for (const auto &each : allTask) {
        DatabaseDeleter::deleteTaskInDataBase(*each);
    }
}

void MarkDownImportWindow::updateToAll() {
    const auto allTask = handler->borrowFrom();
    for (const auto &each : allTask) {
        DataBaseUpdater::updateTargetTask(*each);
    }
}

void MarkDownImportWindow::on_btn_acceptFinish_clicked() {
    updateToAll();
    emit tell_shell_refresh_all();
    close();
}
