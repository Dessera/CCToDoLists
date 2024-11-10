#include "MarkdownImporter.h"
#include <QFile>
#include <QRegularExpression>
#include "DataBaseAdder.h"
#include "Task.h"
// A Simple MultiChildren Tree contains the relationship
// between the parent and children

// Though map can also be used to do so, but i wanna
// try it by myself, challenge myself dude!
struct MarkDownParseNode {
    MarkDownParseNode*        parent = nullptr;
    QList<MarkDownParseNode*> possible_children;
    using NodeLevelPair = QPair<int, Task*>;
    NodeLevelPair* hold;
    void           setHold(NodeLevelPair* hold) {
        this->hold = hold;
    }

    void setParent(MarkDownParseNode* parent) {
        this->parent = parent;
    }
    void gatherInToChildern(MarkDownParseNode* child) {
        possible_children << child;
    }

    void popOutChild(MarkDownParseNode* child) {
        possible_children.removeOne(child);
    }

    bool isTop() const {
        return !parent;
    }

    bool ownsChildren() const {
        return !possible_children.empty();
    }
};

/*
    A state machine recording the parser process
    Welp, i am not good at naming, so i just call it
    'state machine', though it only stores the previous
    state and make decision that the current parsing node
    should be:
    case 1. sibling of previous,
    case 2. the next father
    case 3. be the child of the previous node
*/
struct MarkDownParserStateMachine {
    int this_level     = 0;
    int previous_level = INT_MAX;

    inline bool shell_be_brother() const {
        return this_level == previous_level;
    }

    inline bool shell_set_previous_as_parent() const {
        return this_level > previous_level;
    }

    inline bool isNewFather() const {
        return this_level < previous_level;
        // on this case, we should look up the records and
        // find the possible father :)
    }
    using NodeLevelPair = QPair<int, Task*>;
    // call this when we meet new father which is larger then the node we
    // previous handle
    // welp, i designed to use reverse iterator to find the biggest one
    // for most markdown, the nearest father should at about the latter of
    // the queue
    NodeLevelPair newBigFather() {
        for (auto iterator = recordsByTimes.rbegin();
             iterator != recordsByTimes.rend(); ++iterator) {
            if (iterator->first < this_level) {
                qDebug() << iterator->first;
                return *iterator;
            }
        }
        return {0, nullptr};
    }
    // if we luckily find the biggest one, then it shell be the top widget
    bool isTopBigFather(const NodeLevelPair& indicate) const {
        // 0 is the value indicate that current this_node
        // shall be at the top level
        return indicate.first == 0;
    }

    QList<NodeLevelPair> recordsByTimes;
};

// The Main Core, only parse By Line
struct SimpleParser {
    static constexpr const char  TITLE_LEVEL      = '#';
    static constexpr const char* VALID_START      = "# ";
    static constexpr const char* SPECIAL_SYMBOL[] = {"- ", "#", "# "};
    // markdown file's first header shell be the title, if not, then error!
    static bool isValidStart(const QString& first_line) {
        return first_line.startsWith(VALID_START);
    }

    static bool isPlainText(const QString& line) {
        // any who starts with # is not a plain text
        return !line.startsWith(TITLE_LEVEL);
    }

    static int checkLevel(const QString& line) {
        int level = 0;
        while (line[level] == TITLE_LEVEL) {
            ++level;
        }
        // if level is 0, means no level symbols
        return level == 0 ? INT_MAX : level;
    }

    // we convinced that text is plain text
    static QPair<int, Task*> fromEachRecordLine(const QString& record) {
        int     level  = checkLevel(record);  // level
        QString buffer = record;              // wait-parse-record
        cleanUpToRawText(buffer);
        Task task =
            TaskFactory::createTask().setMainTask().setThisMainTask(buffer);
        return {level, TaskFactory::toHeap(task)};
    }

private:
    static void cleanUpToRawText(QString& buffer) {
        for (const auto& symbol : SPECIAL_SYMBOL) {
            while (buffer.startsWith(symbol)) {
                buffer.remove(0, strlen(symbol));
            }
        }
        // come on, reg is static!
        // remove all the spaces in the front and back
        // trimmed can be, but i wanna try reg
        static QRegularExpression re("^\\s+|\\s+$");
        buffer.remove(re);
    }
};

struct FileFetcher {
    // if we can safely fetch the file, then return the content
    // else invalid value, using has_value to check
    static std::pair<std::optional<QString>, QPair<QFile::FileError, QString>>
    fromFile(const QString& filePath) {
        QFile f(filePath);
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return {std::nullopt, {f.error(), f.errorString()}};
        }
        return {f.readAll(), {QFile::NoError, f.errorString()}};
    }
};

MarkdownImporter::MarkdownImporter(QObject* parent) : QObject(parent) {
}

QString MarkdownImporter::displayErrorStatus() const {
    return errorString;
}

void MarkdownImporter::setParseSource(const QString& markdown_path) {
    this->markdown_path = markdown_path;
}

std::optional<QList<int>> MarkdownImporter::parse() {
    // check if the file is valid, if not, then return invalid value
    // else, we get the file context
    auto context = FileFetcher::fromFile(markdown_path);
    if (!context.first.has_value()) {
        error       = ErrorUtils::map_to_this_error_code(context.second.first);
        errorString = context.second.second;
        emit error_occured(error);
        return std::nullopt;
    }

    // now we get the context, parse it
    // first we shell check if we have things to parse
    // empty case include nothing else and only titles :)
    QStringList forEachLine = context.first.value().split("\n");

    if (forEachLine.size() <= 1) {
        error       = ParseError::PARSE_NOTHING_CONTAINS;
        errorString = ErrorStringPool::PARSE_NOTHING_CONTAINS_ERR;
        emit error_occured(error);
        return std::nullopt;
    }

    // parse if is satisfied our requirement
    if (!SimpleParser::isValidStart(forEachLine.first())) {
        error       = ParseError::NO_HEADER;
        errorString = ErrorStringPool::NO_HEADER_ERR;
        emit error_occured(error);
        return std::nullopt;
    }

    // now all satisfied, we can start to parse
    forEachLine.pop_front();    // remove the first line, as is title
    forEachLine.removeAll("");  // remove all the empty lines
    // result containers
    // hold the memory
    QList<Task*>               allTasks;
    MarkDownParserStateMachine machine;

    // first directly parse each line to the task
    for (const auto& each_record : forEachLine) {
        auto pairs = SimpleParser::fromEachRecordLine(each_record);
        allTasks << pairs.second;
        machine.recordsByTimes << pairs;
    }

    // state machine now contains the records, we can now
    // parse the tree level

    QList<MarkDownParseNode*> allNodes;

    for (auto& nodeLevelPair : machine.recordsByTimes) {
        // init some nodes

        machine.this_level = nodeLevelPair.first;
        // qDebug() << "Current handle task"
        //          << nodeLevelPair.second->getmainTask();
        MarkDownParseNode* this_node = new MarkDownParseNode;
        this_node->setHold(&nodeLevelPair);

        if (allNodes.empty()) {
            /* This is the first node we parse */
            machine.previous_level = nodeLevelPair.first;
            allNodes.append(this_node);
            continue;
        }
        // if we find a new father, that is, the level is smaller
        // (or the title level is bigger), we convinced that we fetch a
        // new tree hierarchy
        if (machine.isNewFather()) {
            // see this if has pareng
            auto father = machine.newBigFather();
            if (machine.isTopBigFather(father)) {
                // well, this is the largest one, we shell make it the top
                this_node->setParent(nullptr);
            } else {
                // find the parent
                int parent_index = 0;
                for (int i = 0; i < allNodes.size(); ++i) {
                    if (allNodes[i]->hold->first == father.first) {
                        parent_index = i;
                        break;
                    }
                }
                // we indicate according nodes
                auto parent_node = allNodes[parent_index];
                this_node->setParent(parent_node);
                parent_node->gatherInToChildern(this_node);
            }
        } else {
            if (machine.shell_be_brother()) {
                // if this is a brother, then the parent is the same as the
                // previous one
                this_node->setParent(allNodes.last()->parent);
                allNodes.last()->parent->gatherInToChildern(this_node);
            } else {
                // if this is a father, then the parent is the previous one
                this_node->setParent(allNodes.last());
                allNodes.last()->gatherInToChildern(this_node);
            }
        }
        // memo the previous level we do
        machine.previous_level = nodeLevelPair.first;
        allNodes.append(this_node);
    }

    // now we should actuall allocate the db_id according to the hierarchy
    // build up memo lists, which will be convenient
    QList<MarkDownParseNode*> remains;
    QList<int>                fetchId;
    for (auto& node : allNodes) {
        remains << node;
    }

    for (const auto& node : allNodes) {
        if (node->isTop()) {
            Task* task = node->hold->second;
            // allocate first
            DataBaseAdder::addTaskBack(*task);
            fetchId << task->gain_id();
            remains.removeOne(node);
        } else {
            // this is not the top node, what we should do is simple
            // to find out the parent, and then set parent_id as it!
            Task* task   = node->hold->second;
            Task* parent = node->parent->hold->second;
            task->setparent_id(*parent);
            DataBaseAdder::addTaskBack(*task);
            fetchId << task->gain_id();
            remains.removeOne(node);
        }
    }

    // clean up the sources
    for (const auto& task : allTasks) {
        delete task;
    }
    for (const auto& node : allNodes) {
        delete node;
    }
    emit parseFinish(fetchId);
    return {fetchId};
}
#undef TELL_ERROR
