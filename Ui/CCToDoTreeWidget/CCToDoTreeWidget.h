#ifndef CCTODOTREEWIDGET_H
#define CCTODOTREEWIDGET_H
#include <QTreeWidget>

// we only support this as main tree widget
// for example the dateTreeWidget_tasks
class CCToDoTreeWidget : public QTreeWidget {
    Q_OBJECT
public:
    CCToDoTreeWidget(QWidget* parent = nullptr);
    // start drag handling the drag item sources;
    void startDrag(Qt::DropActions supportedActions) override;
    // handle the drop, we only cares the drop event, as we inform who
    // is new parent and who is new son:)
    void dropEvent(QDropEvent* event) override;
signals:
    // Qt TreeWidget has no drag drop signals
    // make it by ourselves!
    void tellDragDropParentRelation(QTreeWidgetItem* new_parent,
                                    QTreeWidgetItem* beDragged);
    void itemCheckboxStatusChanged(QTreeWidgetItem* item, int column);

private:
    QTreeWidgetItem* beDragged = nullptr;
};

#endif  // CCTODOTREEWIDGET_H
