#ifndef TASK_H
#define TASK_H

#include <QDateTime>
#include <QString>

/*
    Builder design patterns are used
    Latter I found it convience in Markdown import module!
*/

class Task {
public:
    static constexpr short INVALID_DB_ID = -1;

    enum class SupportiveRole {
        ROLE_PRIORITY,
        ROLE_START_FROM,
        ROLE_END_AT,
        ROLE_DESCRIPTION,
        ROLE_MAIN_TASK,
    };

    struct TaskData {
        /* Priority, default as the Priority::Medium */
        enum class Priority { Low, Medium, High } priority = Priority::Medium;
        /* DateTime Related */
        QDateTime startFrom, endAt;
        /* Descriptions */
        QString description, mainTask;
        /* using in tree structured */
        int     parent_id{INVALID_DB_ID};
        int     id_from_db{INVALID_DB_ID};
        QString groupName;
        bool    isFinished{false};
    };

#define DEFINE_GET_SET(TYPE, MEMBER)      \
    void set##MEMBER(const TYPE& value) { \
        taskData.MEMBER = value;          \
    }                                     \
    TYPE get##MEMBER() const {            \
        return taskData.MEMBER;           \
    }
    DEFINE_GET_SET(int, id_from_db)
    DEFINE_GET_SET(QString, groupName)
    DEFINE_GET_SET(QString, description)
    DEFINE_GET_SET(QString, mainTask)
    DEFINE_GET_SET(TaskData::Priority, priority)
    DEFINE_GET_SET(QDateTime, startFrom)
    DEFINE_GET_SET(QDateTime, endAt)
    DEFINE_GET_SET(bool, isFinished)
#undef DEFINE_GET_SET
    int gain_id() const {
        return taskData.id_from_db;
    }

    void setparent_id(const Task& task) {
        taskData.parent_id = task.taskData.id_from_db;
    }

    void set_no_parent() {
        taskData.parent_id = INVALID_DB_ID;
    }

    int getparent_id() const {
        return taskData.parent_id;
    }

    friend bool operator==(const Task& a1, const Task& a2) {
        return a1.taskData.id_from_db == a2.taskData.id_from_db;
    }

private:
    friend struct TaskCreatorBase;
    friend struct TaskCreatorFrontEnd;
    friend struct TaskHelpUtils;
    friend struct TaskTimeCreator;
    friend struct TaskMainDescriptorCreator;
    friend struct TaskExtraDescriptorCreator;
    friend struct TaskPriorityCreator;
    friend struct TaskFactory;
    friend struct TaskSetGroupCreator;
    friend struct TaskQueryAdapter;
    Task() = default;
    /* Plain Copy */
    Task(const Task& task);
    Task(Task&& task) noexcept;
    const Task& operator=(const Task& task);
    TaskData    taskData;
};

/*
    Preannouncement of the following
*/

struct TaskTimeCreator;
struct TaskMainDescriptorCreator;
struct TaskExtraDescriptorCreator;
struct TaskPriorityCreator;
struct TaskSetGroupCreator;

struct TaskCreatorBase {
    explicit TaskCreatorBase(Task& task) : holdingTask(task) {
    }
    virtual ~TaskCreatorBase() = default;
    struct TaskTimeCreator            setTime();
    struct TaskMainDescriptorCreator  setMainTask();
    struct TaskExtraDescriptorCreator setDescription();
    struct TaskPriorityCreator        setPriority();
    struct TaskSetGroupCreator        setGroup();
    operator Task() const {
        return std::move(holdingTask);
    }

protected:
    Task& holdingTask;
};

struct TaskCreatorFrontEnd : TaskCreatorBase {
public:
    explicit TaskCreatorFrontEnd() : TaskCreatorBase(holding_task) {
    }
    virtual ~TaskCreatorFrontEnd() = default;

private:
    Task holding_task;
};

class QSqlQuery;
struct TaskFactory {
    static TaskCreatorFrontEnd createTask() {
        return TaskCreatorFrontEnd();
    }
    static Task* toHeap(const Task& task) {
        return new Task(std::move(task));
    }
};

struct TaskTimeCreator : TaskCreatorBase {
    explicit TaskTimeCreator(Task& task) : TaskCreatorBase(task) {
    }
    virtual ~TaskTimeCreator() = default;
    struct TaskTimeCreator& setStartTime(const QDateTime& start);
    struct TaskTimeCreator& setEndTime(const QDateTime& start);
};

struct TaskMainDescriptorCreator : TaskCreatorBase {
    explicit TaskMainDescriptorCreator(Task& task) : TaskCreatorBase(task) {
    }
    virtual ~TaskMainDescriptorCreator() = default;
    struct TaskMainDescriptorCreator& setThisMainTask(const QString& mainTask);
};

struct TaskExtraDescriptorCreator : TaskCreatorBase {
    explicit TaskExtraDescriptorCreator(Task& task) : TaskCreatorBase(task) {
    }
    virtual ~TaskExtraDescriptorCreator() = default;
    struct TaskExtraDescriptorCreator& setThisDescription(
        const QString& description);
};

struct TaskPriorityCreator : TaskCreatorBase {
    explicit TaskPriorityCreator(Task& task) : TaskCreatorBase(task) {
    }
    virtual ~TaskPriorityCreator() = default;
    struct TaskPriorityCreator& setThisPriority(
        Task::TaskData::Priority priority);
};

struct TaskSetGroupCreator : TaskCreatorBase {
    explicit TaskSetGroupCreator(Task& task) : TaskCreatorBase(task) {
    }
    virtual ~TaskSetGroupCreator() = default;
    struct TaskSetGroupCreator& setThisGroup(const QString& groupName);
};

#endif  // TASK_H
