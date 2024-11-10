#include "MarkDownUtils.h"
#include <QFileDialog>
#include <QStandardPaths>

QString MarkDownUtils::fetchTargetMarkdownPath(QWidget* parent) {
    return QFileDialog::getOpenFileName(
        parent, "选取一份包含ToDo的Markdown文件",
        QStandardPaths::writableLocation(
            QStandardPaths::StandardLocation::DesktopLocation),
        "Markdown Files (*.md)");
}
