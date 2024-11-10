#ifndef MARKDOWNEXPORTWINDOW_H
#define MARKDOWNEXPORTWINDOW_H
#include <QMainWindow>

namespace Ui {
class MarkdownExportWindow;
}
class ToDoTreeWidgetHandler;

/*
    Export markdown!
*/

class MarkdownExportWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MarkdownExportWindow(QWidget *parent = nullptr);
    void setTreeHandler(ToDoTreeWidgetHandler *handler) {
        holdings = handler;
    }
    /*
        Some settings gain from GUI should be
        Checked!
    */
    bool param_assertion();
    ~MarkdownExportWindow();

private slots:
    void on_btn_setExportPlace_clicked();

    void on_btn_preview_export_clicked();

    void on_btn_cancel_export_clicked();

    void on_btn_accept_export_clicked();

private:
    ToDoTreeWidgetHandler    *holdings;
    Ui::MarkdownExportWindow *ui;
    QString                   stores{};
};

#endif  // MARKDOWNEXPORTWINDOW_H
