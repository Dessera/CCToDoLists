#include "CCToDoTreeWidgetItem.h"
#include "CCToDoTreeWidget.h"

void CCToDoTreeWidgetItem::setData(int column, int role,
                                   const QVariant& value) {
    const bool isCheckChange =
        column == 0 && role == Qt::CheckStateRole &&
        data(column, role).isValid()  // Don't "change" during initialization
        && checkState(0) != value;
    QTreeWidgetItem::setData(column, role, value);
    if (isCheckChange) {
        CCToDoTreeWidget* tree = dynamic_cast<CCToDoTreeWidget*>(treeWidget());
        /* Only the special tree can handle the change others don't! */
        if (tree) {
            tree->setCurrentItem(this);
            emit tree->itemCheckboxStatusChanged(this, column);
        }
    }
}
