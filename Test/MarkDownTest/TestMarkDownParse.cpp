#include "TestMarkDownParse.h"
#include <QDebug>
#include "MarkDownParser/Importer/MarkdownImporter.h"
#include "TestDataBase.h"
void TestMarkDownParse::testParse() {
    // open the database
    TestDataBase test;
    test.doTest();

    MarkdownImporter importer;
    importer.setParseSource(
        "D:/QT projects/CCToDoManager/Test/MarkDownTest/sample.md");
    auto res = importer.parse();
    if (res.has_value()) {
        qDebug() << res.value();
    }
}
