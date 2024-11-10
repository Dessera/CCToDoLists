#include "UiSources.h"
#include <QComboBox>
#include "Task.h"
QIcon UiSources::IconsStorage::fromTaskPriority(const Task& task) {
    switch (task.getpriority()) {
        case Task::TaskData::Priority::Low:
            return QIcon(Low);
        case Task::TaskData::Priority::Medium:
            return QIcon(Medium);
        case Task::TaskData::Priority::High:
            return QIcon(High);
    }
    return QIcon();
}

int UiSources::PriorityMapForComboBox::fromPriorityString(
    const QString& priority) {
    if (priority == Low) return static_cast<int>(Task::TaskData::Priority::Low);
    if (priority == Medium)
        return static_cast<int>(Task::TaskData::Priority::Medium);
    if (priority == High)
        return static_cast<int>(Task::TaskData::Priority::High);
    return static_cast<int>(Task::TaskData::Priority::Medium);
}

QComboBox* UiSources::PriorityMapForComboBox::fetchPriorityComboBox(
    QWidget* holding_parent) {
    QComboBox*  combox = new QComboBox(holding_parent);
    QStringList items;
    items << Low << Medium << High;
    combox->addItems(items);
    return combox;
}
