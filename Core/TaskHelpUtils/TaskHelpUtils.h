#ifndef TASKHELPUTILS_H
#define TASKHELPUTILS_H
#include <QDateTime>
#include "Task.h"

/*
    Some task helpers
*/
struct TaskHelpUtils {
    struct PriorityString {
        static constexpr const char* Low    = "低";
        static constexpr const char* Medium = "中";
        static constexpr const char* High   = "高";
    };

    static QString toDateTime(const QDateTime& dateTime) {
        return dateTime.toString("yyyy-MM-dd hh:mm:ss");
    }

    static QDateTime fromDateTime(const QString& dateTime) {
        return QDateTime::fromString(dateTime, "yyyy-MM-dd hh:mm:ss");
    }

    // display in a format
    static void display_as_format(const Task& task);

    static Task::TaskData::Priority fromInt(int priority) {
        return static_cast<Task::TaskData::Priority>(priority);
    }
    /* SQL property creator */
    static QString toValueMapString(const Task& task);

    static QString gainPriorityString(const Task& task);
    static QString gainPriorityString(Task::TaskData::Priority priority);
    static int     fromPriorityString(const QString& priority);

    // sometime we need to query a temp gen tasks and find match in
    // already live in list, and this helps :)
    static Task* queryTempTaskInList(const Task&        task,
                                     const QList<Task*> tasks);
};

#endif  // TASKHELPUTILS_H
