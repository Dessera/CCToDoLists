#include "MarkdownExporter.h"
#include <QFile>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "TaskTreeWidgetItemFactory/TaskTreeWidegtItemFactory.h"
#include "ToDoTreeWidgetHandler/ToDoTreeWidgetHandler.h"

struct MarkdownSentenseProducer {
    static constexpr const short LEAF_LEVEL = -1;
    static QString               makeTitle(const int& level) {
        if (level == LEAF_LEVEL) {
            return "";
        }
        // always set as the second header
        // because the first header is the title :)
        return QString("#").repeated(level + 1) + " ";
    }

    static QString toMarkDownSingleLine(int            level,
                                        const QString& line_content) {
        return makeTitle(level) + line_content + "\n";
    }
};

/*
    Welp, I write a recursive function :)
    I am afraid of the stack crash, but it works well, welp
    for the depth only about 7 in Markdown
*/
static QString parse_current_level(QTreeWidgetItem* item, int level) {
    QString result;
    if (item->childCount() == 0) {
        return MarkdownSentenseProducer::toMarkDownSingleLine(
            MarkdownSentenseProducer::LEAF_LEVEL,
            item->text(TaskTreeWidegtItemFactory::MainTaskDescriptions));
    }

    result += MarkdownSentenseProducer::toMarkDownSingleLine(
        level, item->text(TaskTreeWidegtItemFactory::MainTaskDescriptions));

    for (int i = 0; i < item->childCount(); ++i) {
        result += parse_current_level(item->child(i), level + 1);
    }
    return result;
}

/*
    Markdown can be seen as a forest with lots of fucking trees
    So, transfer it one by one :)
*/
static QString parse_tree(QTreeWidget* widget) {
    QString result;
    for (int i = 0; i < widget->topLevelItemCount(); ++i) {
        result += parse_current_level(widget->topLevelItem(i), 1);
    }
    return result;
}

/*
    Front End Function
*/
QString MarkdownExporter::parse() const {
    return parse_tree(bindingHandle->fetchTree());
}
