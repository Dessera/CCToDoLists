#include "CCToDoTreeWidgetDelegate.h"
#include <QComboBox>
#include <QDateTimeEdit>
#include "Task.h"
#include "TaskHelpUtils.h"
#include "TaskTreeWidgetItemFactory/TaskTreeWidegtItemFactory.h"
#include "UiSources/UiSources.h"

/*
    For most cases, we need to create the editor for each column
    at colomn level, we provide these editors...
*/

QWidget* CCToDoTreeWidgetDelegate::createEditor(
    QWidget* parent, const QStyleOptionViewItem& option,
    const QModelIndex& index) const {
    // create editors for each;

    // create priority editor
    if (index.column() == TaskTreeWidegtItemFactory::ColumnIndex::Priority) {
        // create a combobox
        QComboBox* editor =
            UiSources::PriorityMapForComboBox::fetchPriorityComboBox(parent);
        return editor;
    }

    if (index.column() == TaskTreeWidegtItemFactory::ColumnIndex::StartTime) {
        // create a dateTimeEdit
        QDateTimeEdit* editor = new QDateTimeEdit(parent);
        editor->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
        editor->setCalendarPopup(true);
        return editor;
    }

    // create the dateTimeEditor
    if (index.column() == TaskTreeWidegtItemFactory::ColumnIndex::DeadLine) {
        // create a dateTimeEdit
        QDateTimeEdit* editor = new QDateTimeEdit(parent);
        editor->setDisplayFormat("yyyy-MM-dd hh:mm:ss");
        editor->setCalendarPopup(true);
        return editor;
    }

    // promise the default behavior
    return QStyledItemDelegate::createEditor(parent, option, index);
}

// this will be called when the editor is closed
// what it reflect will appare  on UI after we call this
void CCToDoTreeWidgetDelegate::setEditorData(QWidget*           editor,
                                             const QModelIndex& index) const {
    if (index.column() == TaskTreeWidegtItemFactory::ColumnIndex::Priority) {
        // set the editor data
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        comboBox->setCurrentText(index.data().toString());
        return;
    }

    if (index.column() == TaskTreeWidegtItemFactory::ColumnIndex::StartTime) {
        // set the editor data
        QDateTimeEdit* dateTimeEdit = static_cast<QDateTimeEdit*>(editor);
        dateTimeEdit->setDateTime(
            TaskHelpUtils::fromDateTime(index.data().toString()));
        return;
    }

    if (index.column() == TaskTreeWidegtItemFactory::ColumnIndex::DeadLine) {
        // set the editor data
        QDateTimeEdit* dateTimeEdit = static_cast<QDateTimeEdit*>(editor);
        dateTimeEdit->setDateTime(
            TaskHelpUtils::fromDateTime(index.data().toString()));
        return;
    }

    // promise the default behavior
    QStyledItemDelegate::setEditorData(editor, index);
}

// this will be called when the editor is closed
// and the model way we display at here
// actually set the core data
void CCToDoTreeWidgetDelegate::setModelData(QWidget*            editor,
                                            QAbstractItemModel* model,
                                            const QModelIndex&  index) const {
    if (index.column() == TaskTreeWidegtItemFactory::ColumnIndex::Priority) {
        // set the model data
        QComboBox*               comboBox = static_cast<QComboBox*>(editor);
        Task::TaskData::Priority priority =
            static_cast<Task::TaskData::Priority>(
                UiSources::PriorityMapForComboBox::fromPriorityString(
                    comboBox->currentText()));
        model->setData(index, TaskHelpUtils::gainPriorityString(priority));
        return;
    }

    if (index.column() == TaskTreeWidegtItemFactory::ColumnIndex::StartTime) {
        // set the model data
        QDateTimeEdit* dateTimeEdit = static_cast<QDateTimeEdit*>(editor);
        model->setData(
            index, dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        return;
    }

    if (index.column() == TaskTreeWidegtItemFactory::ColumnIndex::DeadLine) {
        // set the model data
        QDateTimeEdit* dateTimeEdit = static_cast<QDateTimeEdit*>(editor);
        model->setData(
            index, dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
        return;
    }

    // promise the default behavior
    QStyledItemDelegate::setModelData(editor, model, index);
}
