# ----------------------------------------------------------------------
#   ATTENSION: This file is the project file for the CCToDoManager
#   project. It is used to build the project.
#
#   At this version, Project are not supported to build
#   What you need to do is to:
#   Compile the qt-material project independently, which following is
#   the github address:
#       https://github.com/laserpants/qt-material-widgets
#   Download this are required to compile the project.
#   1. git clone the qt-material
#   2. cd qt-material, run the qmake
#   3. copy the libmaterials.a to the project at the creation Time!
#   4. edit the project file, let qmake knows the path of the libmaterials.a
#
#   OR
#       You can let the edit back to the normal edit without the qt-material
#       This can also make project able to compile
#   In windows, if u do not know how to compile the qt-material, you can
#   see my blog posted at:
#   https://blog.csdn.net/charlie114514191/article/details/143374274?spm=1001.2014.3001.5501
#
# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
# Notes
# If u wanna use it as an normal application
# In windows, using the windeployqt to wrap the qt application!
# Copy the data/database/TodoDataBase.db to the exe install path
# This will be help:)
# ----------------------------------------------------------------------

# Must using
QT       += core gui statemachine

# Using SQL Database in current version
QT       += sql

# Using chart block for display the task status
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Add IncludePath For convinient include
INCLUDEPATH += \
    Ui/ \   # Ui Subfolder
    Core/ \ # Core Subfolder
    DatabaseDriver/ \  # DatabaseDriver Subfolder
    Ui/MainWindow/ \
    Ui/TaskCreator \
    Ui/TaskDisplay \
    Ui/DisplayStatus \
    Ui/CCToDoTreeWidget \
    Core/Task/ \
    Core/TaskHelpUtils/ \
    Core/TaskCreatorManager/ \


# Project Defines
DEFINES +=  \
            \ SET_ON_DEBUG \ # on debug promise some debug info
            \ # REQ_TEST

contains(DEFINES, SET_ON_DEBUG){
    DEFINES += ON_DEBUG
}

contains(DEFINES, REQ_TEST){
    DEFINES += ON_TEST
    INCLUDEPATH += Test \
                    Test/utils

    SOURCES += \
    Test/DoTest.cpp \
    Test/TestAdd.cpp \
    Test/TestDataBase.cpp \
    Test/TestDeleter.cpp \
    Test/TestQuery.cpp \
    Test/TestTask.cpp \
    Test/TestUpdate.cpp \
    Test/TestSources.cpp \
    Test/utils/TestHelpUtils.cpp
    Test/MarkDownTest/TestMarkDownParse.cpp


    HEADERS += \
    Test/MarkDownTest/TestMarkDownParse.h \
    Test/DoTest.h \
    Test/TestAdd.h \
    Test/TestDataBase.h \
    Test/TestDeleter.h \
    Test/TestQuery.h \
    Test/TestTask.h \
    Test/TestUpdate.h \
    Test/TestSources.h \
    Test/utils/TestHelpUtils.h
}

SOURCES += \
    Core/CCToDoTaskTreeMenuFactory/CCToDoTreeCustomMenuFactory.cpp \
    Core/MarkDownParser/Exporter/MarkdownExporter.cpp \
    Core/MarkDownParser/Importer/MarkdownImporter.cpp \
    Core/MarkdownUtils/MarkDownUtils.cpp \
    Core/Task/Task.cpp \
    Core/TaskCreatorManager/TaskCreateManager.cpp \
    Core/TaskHelpUtils/TaskHelpUtils.cpp \
    Core/TaskListsHandle/TaskListsHandle.cpp \
    DatabaseDriver/CCToDoDataBase.cpp \
    DatabaseDriver/CCToDoDataBaseImpl.cpp \
    DatabaseDriver/DataBaseAdder.cpp \
    DatabaseDriver/DataBaseCommons.cpp \
    DatabaseDriver/DataBaseQuery.cpp \
    DatabaseDriver/DataBaseUpdater.cpp \
    DatabaseDriver/DatabaseDeleter.cpp \
    DatabaseDriver/TaskQueryAdapter.cpp \
    Main/main.cpp \
    Ui/CCToDoTreeDelegate/CCToDoTreeWidgetDelegate.cpp \
    Ui/CCToDoTreeWidget/CCToDoTreeWidget.cpp \
    Ui/CCToDoTreeWidgetItem/CCToDoTreeWidgetItem.cpp \
    Ui/DisplayStatus/DisplayStatus.cpp \
    Ui/MainWindow/CCToDoMainWindow.cpp \
    Ui/MainWindow/MainWindowExternWidgetIniter.cpp \
    Ui/MarkDownImportWindow/MarkDownImportWindow.cpp \
    Ui/MarkdownExportWindow/MarkdownExportWindow.cpp \
    Ui/TaskCreateWindow/TaskCreateMainWindow.cpp \
    Ui/TaskDisplayWindow/TaskDisplayDialog.cpp \
    Ui/TaskTreeWidgetItemFactory/TaskTreeWidegtItemFactory.cpp \
    Ui/ToDoTreeWidgetHandler/ToDoTreeWidgetHandler.cpp \
    Ui/UiSources/UiSources.cpp

HEADERS += \
    Core/CCToDoTaskTreeMenuFactory/CCToDoTreeCustomMenuFactory.h \
    Core/MarkDownParser/Exporter/MarkdownExporter.h \
    Core/MarkDownParser/Importer/MarkdownImporter.h \
    Core/MarkdownUtils/MarkDownUtils.h \
    Core/Task/Task.h \
    Core/TaskCreatorManager/TaskCreateManager.h \
    Core/TaskHelpUtils/TaskHelpUtils.h \
    Core/TaskListsHandle/TaskListsHandle.h \
    DatabaseDriver/CCToDoDataBase.h \
    DatabaseDriver/CCToDoDataBaseImpl.h \
    DatabaseDriver/DataBaseAdder.h \
    DatabaseDriver/DataBaseCommons.h \
    DatabaseDriver/DataBaseQuery.h \
    DatabaseDriver/DataBaseUpdater.h \
    DatabaseDriver/DatabaseDeleter.h \
    DatabaseDriver/TaskQueryAdapter.h \
    Ui/CCToDoTreeDelegate/CCToDoTreeWidgetDelegate.h \
    Ui/CCToDoTreeWidget/CCToDoTreeWidget.h \
    Ui/CCToDoTreeWidgetItem/CCToDoTreeWidgetItem.h \
    Ui/DisplayStatus/DisplayStatus.h \
    Ui/Externs/include/qt-material/qtmaterialflatbutton.h \
    Ui/MainWindow/CCToDoMainWindow.h \
    Ui/MainWindow/MainWindowExternWidgetIniter.h \
    Ui/MarkDownImportWindow/MarkDownImportWindow.h \
    Ui/MarkdownExportWindow/MarkdownExportWindow.h \
    Ui/TaskCreateWindow/TaskCreateMainWindow.h \
    Ui/TaskDisplayWindow/TaskDisplayDialog.h \
    Ui/TaskTreeWidgetItemFactory/TaskTreeWidegtItemFactory.h \
    Ui/ToDoTreeWidgetHandler/ToDoTreeWidgetHandler.h \
    Ui/UiSources/UiSources.h

FORMS += \
    Ui/DisplayStatus/DisplayStatus.ui \
    Ui/MainWindow/CCToDoMainWindow.ui \
    Ui/MarkDownImportWindow/MarkDownImportWindow.ui \
    Ui/MarkdownExportWindow/MarkdownExportWindow.ui \
    Ui/TaskCreateWindow/TaskCreateMainWindow.ui \
    Ui/TaskDisplayWindow/TaskDisplayDialog.ui

# Copy the database file for extensive using
COPY_DIR = $$PWD/
COPY_FILES.files = $$COPY_DIR/data/database/TodoDataBase.db
COPY_FILES.path = data/database/
COPIES += COPY_FILES

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# For qt-material external libs
win32 {

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Ui/Externs/lib/release/ -lcomponents
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Ui/Externs/lib/debug/ -lcomponents

INCLUDEPATH += $$PWD/Ui/Externs/include/qt-material
DEPENDPATH += $$PWD/Ui/Externs/include/qt-material

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/Ui/Externs/lib/release/libcomponents.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/Ui/Externs/lib/debug/libcomponents.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/Ui/Externs/lib/release/components.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/Ui/Externs/lib/debug/components.lib
}

# In linux, u should add it by ur own

# icon sources are here
RESOURCES += \
    icons.qrc

# Executable icon:
RC_ICONS = data/icons/CCToDoIcon.ico





