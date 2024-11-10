#ifndef CCTODOTREECUSTOMMENUFACTORY_H
#define CCTODOTREECUSTOMMENUFACTORY_H
#include <QMenu>
#include <QObject>
class CCToDoTreeWidget;

/*
    Custom Menu creator
    The right button click make the menu appear at
    the tree widget
*/

class CCToDoTreeCustomMenuFactory : public QObject {
    Q_OBJECT
public:
    struct MenuName {
        static constexpr const char* ADD     = "添加子任务";
        static constexpr const char* DELETE  = "删除任务";
        static constexpr const char* COPY    = "复制任务";
        static constexpr const char* DISPLAY = "查看任务";
        static constexpr const char* PASTE   = "粘贴任务";
        static constexpr const char* ADDROOT = "添加任务到根...";
    };

    explicit CCToDoTreeCustomMenuFactory(QObject* parent = nullptr)
        : QObject(parent) {
    }

    QMenu* fetchMenu(CCToDoTreeWidget* tree);
    QMenu* fetchMenuOnNoItem(CCToDoTreeWidget* tree);
signals:
    void tellAddNewTaskAtHere();
    void tellAddToRoot();
    void tellDeleteThisTaskAtHere();
    void tellCopyThisTaskAtHere();
    void tellDisplayDetailOfThisTask();
    void tellPasteTaskAtHere();

private:
    void generateSupportiveActions(QMenu* onHandlingMenu);
    void generateSupportiveOnPlainOne(QMenu* onHandlingMenu);
};

#endif  // CCTODOTREECUSTOMMENUFACTORY_H
