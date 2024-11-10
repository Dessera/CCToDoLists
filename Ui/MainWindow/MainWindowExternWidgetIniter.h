#ifndef MAINWINDOWEXTERNWIDGETINITER_H
#define MAINWINDOWEXTERNWIDGETINITER_H

class CCToDoMainWindow;
class QTreeWidget;

struct MainWindowExternWidgetIniter {
public:
    static void initializeThis(CCToDoMainWindow* window);
    static void initializeAfterOpenDataBase(CCToDoMainWindow* window);
    static void final_initializing_ui_adjust(CCToDoMainWindow* window);
    static void makeResizeAsContext(QTreeWidget* widget);

private:
    static void initialize_tree_viewdock(CCToDoMainWindow* window);
    static void initStatusWidget(CCToDoMainWindow* window);
    static void initDateWidgets(CCToDoMainWindow* window);
    static void initGroupTabs(CCToDoMainWindow* window);
};

#endif  // MAINWINDOWEXTERNWIDGETINITER_H
