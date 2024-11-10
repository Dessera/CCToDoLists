#ifndef MARKDOWNEXPORTER_H
#define MARKDOWNEXPORTER_H
#include <QObject>
#include <QString>
// this classes using in export the task to markdown file
class ToDoTreeWidgetHandler;

class MarkdownExporter : public QObject {
    Q_OBJECT
public:
    MarkdownExporter() = delete;
    // bind a handle :)
    explicit MarkdownExporter(ToDoTreeWidgetHandler* handle,
                              QObject*               parent = nullptr)
        : QObject(parent), bindingHandle(handle) {};
    MarkdownExporter(const MarkdownExporter&)            = delete;
    MarkdownExporter& operator=(const MarkdownExporter&) = delete;
    QString           parse() const;
signals:
    void error_occured(int error);
    void parseFinish();

private:
    ToDoTreeWidgetHandler* bindingHandle;
    QString                save_at;
};

#endif  // MARKDOWNEXPORTER_H
