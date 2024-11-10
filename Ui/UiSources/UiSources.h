#ifndef UISOURCES_H
#define UISOURCES_H
#include <QIcon>

class Task;
class QComboBox;
class QWidget;

/*
    UiSources provides basic adapter between GUI and Internal
    data structure, which, i do mean: it's a bridge between the GUI and the Core
*/
struct UiSources {
    struct HeaderViewProviders {
        static QStringList proviceCommonHeader() {
            return QStringList()
                   << "任务描述" << "优先级" << "开始时间" << "DDL";
        }
    };

    struct IconsStorage {
        static constexpr const char* Low =
            ":/icons/priority/data/icons/priority/low_priority.png";
        static constexpr const char* Medium =
            ":/icons/priority/data/icons/priority/middle_priority.png";
        static constexpr const char* High =
            ":/icons/priority/data/icons/priority/high_priority.jpg";

        static constexpr const char* MainTask =
            ":/icons/treewidgetitem/data/icons/treewidgetitemicon/mainTask.png";

        static constexpr const char* StartTime =
            ":/icons/treewidgetitem/data/icons/treewidgetitemicon/"
            "starttime.png";

        static constexpr const char* DeadLine =
            ":/icons/treewidgetitem/data/icons/treewidgetitemicon/"
            "Deadlines.png";

        static QIcon fromTaskPriority(const Task& task);
        static QIcon lowPriorityIcon() {
            return QIcon(Low);
        }

        static QIcon mediumPriorityIcon() {
            return QIcon(Medium);
        }

        static QIcon highPriorityIcon() {
            return QIcon(High);
        }

        static QIcon MainTaskIcon() {
            return QIcon(MainTask);
        }

        static QIcon StartLineIcon() {
            return QIcon(DeadLine);
        }

        static QIcon DeadLineIcon() {
            return QIcon(DeadLine);
        }
    };

    struct PriorityMapForComboBox {
        static constexpr const char* Low    = "低优先级";
        static constexpr const char* Medium = "中优先级";
        static constexpr const char* High   = "高优先级";

        static int fromPriorityString(const QString& priority);

        static QComboBox* fetchPriorityComboBox(QWidget* holding_parent);
    };
};

#endif  // UISOURCES_H
