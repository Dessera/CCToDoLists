#ifndef MARKDOWNIMPORTWINDOW_H
#define MARKDOWNIMPORTWINDOW_H

#include <QMainWindow>
class ToDoTreeWidgetHandler;
namespace Ui {
class MarkDownImportWindow;
}

class MarkDownImportWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MarkDownImportWindow(QWidget *parent = nullptr);
    void setTargets(const QList<int> &ids);
    ~MarkDownImportWindow();
signals:
    void tell_shell_refresh_all();
private slots:
    void on_btn_cancel_clicked();

    void on_btn_acceptFinish_clicked();

private:
    void                                   initHandler();
    void                                   initTree();
    void                                   updateToAll();
    void                                   removeAll();
    std::shared_ptr<ToDoTreeWidgetHandler> handler;
    Ui::MarkDownImportWindow              *ui;
};

#endif  // MARKDOWNIMPORTWINDOW_H
