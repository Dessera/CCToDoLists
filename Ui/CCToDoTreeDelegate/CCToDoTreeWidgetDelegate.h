#ifndef CCTODOTREEWIDGETDELEGATE_H
#define CCTODOTREEWIDGETDELEGATE_H
#include <QObject>
#include <QStyledItemDelegate>
class QTreeWidgetItem;
// handling the edit way of the tree widgets!

/*
    Hola! My first time using this
    Notings: this provide the editor interface of GUI View
    We need to, actually always need to override the functions to handle the
    change (User tell his willing of change, and we provide this:) )
*/
class CCToDoTreeWidgetDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    CCToDoTreeWidgetDelegate(QObject *parent = nullptr)
        : QStyledItemDelegate(parent) {};

    // delegate shell override some functions to handle the display
    // this includes createEditor, setEditorData, setModelData

    // createEditor is using to create the editor widget for the item
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    // setEditorData is using to set the data from model to the editor
    void setEditorData(QWidget           *editor,
                       const QModelIndex &index) const override;

    // setModelData is using to set the data from editor to the model
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;
};

#endif  // CCTODOTREEWIDGETDELEGATE_H
