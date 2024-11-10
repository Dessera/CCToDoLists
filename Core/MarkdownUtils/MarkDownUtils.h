#ifndef MARKDOWNUTILS_H
#define MARKDOWNUTILS_H
#include <QString>
class QWidget;

struct MarkDownUtils {
    /*
        THIS will open the markdown file and return the file Path ready fro
        reads
    */
    static QString fetchTargetMarkdownPath(QWidget *parent);
};

#endif  // MARKDOWNUTILS_H
