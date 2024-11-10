#ifndef TODOTREEWIDGETHANDLER_H
#define TODOTREEWIDGETHANDLER_H
#include "TaskListsHandle/TaskListsHandle.h"
#include "TaskTreeWidgetItemFactory/TaskTreeWidegtItemFactory.h"

class QTreeWidget;
class TaskCreateMainWindow;
class TaskListsHandle;
class CCToDoTreeWidget;
class CCToDoTreeCustomMenuFactory;
class QMenu;

class ToDoTreeWidgetHandler : public QObject {
    Q_OBJECT
public:
    ToDoTreeWidgetHandler(QTreeWidget* widget, QObject* parent = nullptr);
    ToDoTreeWidgetHandler()                                        = delete;
    ~ToDoTreeWidgetHandler()                                       = default;
    ToDoTreeWidgetHandler(const ToDoTreeWidgetHandler&)            = delete;
    ToDoTreeWidgetHandler& operator=(const ToDoTreeWidgetHandler&) = delete;
    void                   setTasks(QList<Task*> handlingTask);

    // some treeWidget shell be draggble, some not
    // for example, dateTreeWidget shell be dragable, some not!
    void         setAsDragable(bool isDragable);
    void         setSortable(bool isSortable);
    void         sortByDDLDate(Qt::SortOrder order = Qt::AscendingOrder);
    QList<Task*> borrowFrom() const;
    QTreeWidget* fetchTree() const {
        return handling_tree;
    };
    void clearAll();

signals:
    void tellDisplayTask(Task* task, QTreeWidgetItem* item);
    void tell_no_source_copy_error();
    void tell_refresh_group();

public slots:
    void setEditBaseTime(const QDateTime& time) {
        editBaseTime = time;
    }
    // plain
    void handle_add_root_action();

private slots:
    friend class CCToDoMainWindow;
    void handle_the_incoming_new_task_from_window();
    void handle_customMenuEvent(const QPoint& point);
    // this is using in inform the CCToDoTreeHandler to receive the handle of
    // drags, only CCToDoTree is available of this handle, shell check in
    // dynamic
    void receiveHandleOfDrags(QTreeWidgetItem* new_parent,
                              QTreeWidgetItem* beDragged);
    void handle_value_change();

    // special menu events handler
    void handle_add_action();
    bool handle_delete_action();
    void handle_display_action();
    void handle_copy_action();
    void handle_paste_action();

private:
    void handle_CCToDoTreeSpecial(CCToDoTreeWidget* tree);
    void do_initMenuFactory();

    QMenu* handle_plain_menu(CCToDoTreeWidget* special_tree);
    QMenu* handle_special_menu(CCToDoTreeWidget* special_tree);

    void do_initPlainFactory();
    void do_initCreateWindow();
    void addTasksSingleFromQuery();
    void handle_new_add_task(Task* inHeap, QTreeWidgetItem* parent);
    TaskTreeWidegtItemFactory factory;
    // for those who can edit, support create, else we don't
    std::shared_ptr<TaskCreateMainWindow>        createWindow;
    std::shared_ptr<CCToDoTreeCustomMenuFactory> menuFactory;
    TaskListsHandle                              tasksHandler;
    QTreeWidget*                                 handling_tree;
    /* copy paste one */
    struct {
        QTreeWidgetItem* copyItem{nullptr};
        QTreeWidgetItem* pasteItem{nullptr};
        Task*            holding_copy{nullptr};
        bool             isPastable() const {
            return copyItem != nullptr;
        }
    } copy_paste_memo;

    /* using in create window */
    QDateTime editBaseTime;
};

#endif  // TODOTREEWIDGETHANDLER_H
