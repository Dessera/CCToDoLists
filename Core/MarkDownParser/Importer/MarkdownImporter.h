#ifndef MARKDOWNIMPORTER_H
#define MARKDOWNIMPORTER_H

#include <QObject>
class Task;

class MarkdownImporter : public QObject {
    Q_OBJECT
public:
    enum ParseError {
        NO_ERROR,
        NO_HEADER,
        PARSE_NOTHING_CONTAINS,
        FILE_ERROR_BASE
    };

    struct ErrorUtils {
        /* Map back from the errorCode */
        static int map_to_this_error_code(int file_error_code) {
            return file_error_code + FILE_ERROR_BASE;
        }
        static int fetch_real_file_error(int error_code) {
            return error_code - FILE_ERROR_BASE;
        }
    };

    explicit MarkdownImporter(QObject* parent = nullptr);
    QString displayErrorStatus() const;
    /* Markdown file path g/setter */
    void    setParseSource(const QString& markdown_path);
    QString parseSource() const {
        return markdown_path;
    }
    /*
        1. If the markdown is valid, then we shell return a valid value
        otherwise, we shell return a invalid value, using has_value to check
        2. functions can be sync with wait return result, or
        async by using signals and slots :)
    */
    std::optional<QList<int>> parse();
signals:
    void error_occured(int error);
    void parseFinish(QList<int> result);

private:
    QString markdown_path;
    int     error = ParseError::NO_ERROR;
    struct ErrorStringPool {
        static constexpr const char* NO_ERR        = "No error!";
        static constexpr const char* NO_HEADER_ERR = "No header found!";
        static constexpr const char* PARSE_NOTHING_CONTAINS_ERR =
            "Nothing to parse!";
        static constexpr const char* FILE_ERROR_BASE_ERR = "File error!";
    };
    QString errorString = ErrorStringPool::NO_ERR;
};

#endif  // MARKDOWNIMPORTER_H
