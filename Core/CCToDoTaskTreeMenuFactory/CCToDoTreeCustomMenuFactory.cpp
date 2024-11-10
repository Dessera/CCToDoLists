#include "CCToDoTreeCustomMenuFactory.h"
#include <QMenu>
#include "CCToDoTreeWidget.h"

QMenu* CCToDoTreeCustomMenuFactory::fetchMenu(CCToDoTreeWidget* tree) {
    QMenu* customMenu = new QMenu(tree);
    generateSupportiveActions(customMenu);
    return customMenu;
}

QMenu* CCToDoTreeCustomMenuFactory::fetchMenuOnNoItem(CCToDoTreeWidget* tree) {
    QMenu* customMenu = new QMenu(tree);
    generateSupportiveOnPlainOne(customMenu);
    return customMenu;
}

void CCToDoTreeCustomMenuFactory::generateSupportiveOnPlainOne(
    QMenu* onHandlingMenu) {
    auto display_task_action = onHandlingMenu->addAction(MenuName::ADDROOT);
    connect(display_task_action, &QAction::triggered, this,
            &CCToDoTreeCustomMenuFactory::tellAddToRoot);
}

void CCToDoTreeCustomMenuFactory::generateSupportiveActions(QMenu* menu) {
    auto new_task_action = menu->addAction(MenuName::ADD);
    connect(new_task_action, &QAction::triggered, this,
            &CCToDoTreeCustomMenuFactory::tellAddNewTaskAtHere);

    auto delete_task_action = menu->addAction(MenuName::DELETE);
    connect(delete_task_action, &QAction::triggered, this,
            &CCToDoTreeCustomMenuFactory::tellDeleteThisTaskAtHere);

    auto copy_task_action = menu->addAction(MenuName::COPY);
    connect(copy_task_action, &QAction::triggered, this,
            &CCToDoTreeCustomMenuFactory::tellCopyThisTaskAtHere);

    auto paste_task_action = menu->addAction(MenuName::PASTE);
    connect(paste_task_action, &QAction::triggered, this,
            &CCToDoTreeCustomMenuFactory::tellPasteTaskAtHere);

    auto display_task_action = menu->addAction(MenuName::DISPLAY);
    connect(display_task_action, &QAction::triggered, this,
            &CCToDoTreeCustomMenuFactory::tellDisplayDetailOfThisTask);
}
