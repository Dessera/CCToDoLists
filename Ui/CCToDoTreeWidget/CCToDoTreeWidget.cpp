#include "CCToDoTreeWidget.h"
#include <QDropEvent>
#include "CCToDoTaskTreeMenuFactory/CCToDoTreeCustomMenuFactory.h"
#include "CCToDoTreeDelegate/CCToDoTreeWidgetDelegate.h"
CCToDoTreeWidget::CCToDoTreeWidget(QWidget* parent) : QTreeWidget(parent) {
    auto delegate = new CCToDoTreeWidgetDelegate(this);
    setItemDelegate(delegate);
    setContextMenuPolicy(Qt::CustomContextMenu);
}

void CCToDoTreeWidget::startDrag(Qt::DropActions supportedActions) {
    qDebug() << "Start drag!";
    // record the target item
    beDragged = currentItem();
    return QTreeWidget::startDrag(supportedActions);
}

void CCToDoTreeWidget::dropEvent(QDropEvent* event) {
    qDebug() << "is dropping";
    /* gain the father item */
    QTreeWidgetItem* targetItem = itemAt(event->position().toPoint());
    emit             tellDragDropParentRelation(targetItem, beDragged);
    return QTreeWidget::dropEvent(event);
}
