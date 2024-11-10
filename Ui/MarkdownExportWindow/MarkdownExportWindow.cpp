#include "MarkdownExportWindow.h"
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include "Core/MarkDownParser/Exporter/MarkdownExporter.h"
#include "ui_MarkdownExportWindow.h"

/*
    Write files to target
*/
struct FileWriter {
    static QPair<QFile::FileError, QString> writeToFile(
        const QString& filePath, const QString& content) {
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            return {file.error(), file.errorString()};
        }
        file.write(content.toUtf8());
        return {file.error(), ""};
    }
};

MarkdownExportWindow::MarkdownExportWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MarkdownExportWindow) {
    ui->setupUi(this);
    ui->lineEdit_titleName->setLabel("来一个Title!");
    ui->lineEdit_titleName->setText("今日任务！");
}

bool MarkdownExportWindow::param_assertion() {
    if (ui->lineEdit_titleName->text().isEmpty()) {
        QMessageBox::critical(this, "标题不能为空", "标题不能为空!");
        return false;
    }

    if (ui->label_displayExport->text().isEmpty()) {
        QMessageBox::critical(this, "文件路径不存在", "文件路径不存在!");
        return false;
    }
    return true;
}

MarkdownExportWindow::~MarkdownExportWindow() {
    delete ui;
}

void MarkdownExportWindow::on_btn_setExportPlace_clicked() {
    QString filePath = QFileDialog::getSaveFileName(
        this, tr("保存到！"), "", tr("Markdown Files (*.md)"));
    if (!filePath.isEmpty()) {
        ui->label_displayExport->setText(filePath);
    }
}

void MarkdownExportWindow::on_btn_preview_export_clicked() {
    if (!param_assertion()) {
        return;
    }
    stores = "";
    stores += QString("# %1\n").arg(ui->lineEdit_titleName->text());
    MarkdownExporter exporter(holdings);
    stores += exporter.parse();

    ui->display_result->setMarkdown(stores);
}

void MarkdownExportWindow::on_btn_cancel_export_clicked() {
    close();
}

void MarkdownExportWindow::on_btn_accept_export_clicked() {
    if (!stores.isEmpty()) {
        FileWriter::writeToFile(ui->label_displayExport->text(), stores);
    }

    if (!param_assertion()) {
        return;
    }
    // clear the stores
    stores = "";
    stores += QString("# %1\n").arg(ui->lineEdit_titleName->text());
    MarkdownExporter exporter(holdings);
    stores += exporter.parse();
    FileWriter::writeToFile(ui->label_displayExport->text(), stores);
    close();
}
