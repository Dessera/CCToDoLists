#ifndef CCTODOTREEWIDGETITEM_H
#define CCTODOTREEWIDGETITEM_H
#include <QTreeWidget>
#include <QTreeWidgetItem>

class CCToDoTreeWidgetItem : public QTreeWidgetItem {
public:
    /*
        real override at here, oh man, I have to do this
    */
    void setData(int column, int role, const QVariant &value) override;

public:
    /*  Holy shit! for more support of signals of checkbox, I have to override
     *  Such a piece of shit!
     *  May Qt add itemCheckboxStatusChangeSignals later!
     */

    explicit CCToDoTreeWidgetItem(int type = Type) : QTreeWidgetItem(type) {
    }
    explicit CCToDoTreeWidgetItem(const QStringList &strings, int type = Type)
        : QTreeWidgetItem(strings, type) {
    }
    explicit CCToDoTreeWidgetItem(QTreeWidget *treeview, int type = Type)
        : QTreeWidgetItem(treeview, type) {
    }
    CCToDoTreeWidgetItem(QTreeWidget *treeview, const QStringList &strings,
                         int type = Type)
        : QTreeWidgetItem(treeview, strings, type) {
    }
    CCToDoTreeWidgetItem(QTreeWidget *treeview, QTreeWidgetItem *after,
                         int type = Type)
        : QTreeWidgetItem(treeview, after, type) {
    }
    explicit CCToDoTreeWidgetItem(QTreeWidgetItem *parent, int type = Type)
        : QTreeWidgetItem(parent, type) {
    }
    CCToDoTreeWidgetItem(QTreeWidgetItem *parent, const QStringList &strings,
                         int type = Type)
        : QTreeWidgetItem(parent, strings, type) {
    }
    CCToDoTreeWidgetItem(QTreeWidgetItem *parent, QTreeWidgetItem *after,
                         int type = Type)
        : QTreeWidgetItem(parent, after, type) {
    }
    CCToDoTreeWidgetItem(const QTreeWidgetItem &other)
        : QTreeWidgetItem(other) {
    }
    ~CCToDoTreeWidgetItem() = default;
};

#endif  // CCTODOTREEWIDGETITEM_H
