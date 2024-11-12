project(
  'CCToDoLists',
  'cpp',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=gnu++17'],
)

qt6 = import('qt6')
qt6_dep = dependency('qt6', modules: ['Core', 'Gui', 'StateMachine', 'Sql', 'Charts'])

material = subproject('qt-material-widgets')
material_dep = material.get_variable('dep')

CCToDo_deps = [qt6_dep, material_dep]

CCToDo_inc = include_directories(
    'Ui',
    'Core',
    'DatabaseDriver',
    'Ui/MainWindow',
    'Ui/TaskCreateWindow',
    'Ui/TaskDisplayWindow',
    'Ui/DisplayStatus',
    'Ui/CCToDoTreeWidget',
    'Core/Task',
    'Core/TaskHelpUtils',
    'Core/TaskCreatorManager'
)

CCToDo_inc_files = files(
    'Core/CCToDoTaskTreeMenuFactory/CCToDoTreeCustomMenuFactory.h',
    'Core/MarkDownParser/Exporter/MarkdownExporter.h',
    'Core/MarkDownParser/Importer/MarkdownImporter.h',
    'Core/MarkdownUtils/MarkDownUtils.h',
    'Core/Task/Task.h',
    'Core/TaskCreatorManager/TaskCreateManager.h',
    'Core/TaskHelpUtils/TaskHelpUtils.h',
    'Core/TaskListsHandle/TaskListsHandle.h',
    'DatabaseDriver/CCToDoDataBase.h',
    'DatabaseDriver/CCToDoDataBaseImpl.h',
    'DatabaseDriver/DataBaseAdder.h',
    'DatabaseDriver/DataBaseCommons.h',
    'DatabaseDriver/DataBaseQuery.h',
    'DatabaseDriver/DataBaseUpdater.h',
    'DatabaseDriver/DatabaseDeleter.h',
    'DatabaseDriver/TaskQueryAdapter.h',
    'Ui/CCToDoTreeDelegate/CCToDoTreeWidgetDelegate.h',
    'Ui/CCToDoTreeWidget/CCToDoTreeWidget.h',
    'Ui/CCToDoTreeWidgetItem/CCToDoTreeWidgetItem.h',
    'Ui/DisplayStatus/DisplayStatus.h',
    'Ui/Externs/include/qt-material/qtmaterialflatbutton.h',
    'Ui/MainWindow/CCToDoMainWindow.h',
    'Ui/MainWindow/MainWindowExternWidgetIniter.h',
    'Ui/MarkDownImportWindow/MarkDownImportWindow.h',
    'Ui/MarkdownExportWindow/MarkdownExportWindow.h',
    'Ui/TaskCreateWindow/TaskCreateMainWindow.h',
    'Ui/TaskDisplayWindow/TaskDisplayDialog.h',
    'Ui/TaskTreeWidgetItemFactory/TaskTreeWidegtItemFactory.h',
    'Ui/ToDoTreeWidgetHandler/ToDoTreeWidgetHandler.h',
    'Ui/UiSources/UiSources.h'
)

CCToDo_src = files(
    'Core/CCToDoTaskTreeMenuFactory/CCToDoTreeCustomMenuFactory.cpp',
    'Core/MarkDownParser/Exporter/MarkdownExporter.cpp',
    'Core/MarkDownParser/Importer/MarkdownImporter.cpp',
    'Core/MarkdownUtils/MarkDownUtils.cpp',
    'Core/Task/Task.cpp',
    'Core/TaskCreatorManager/TaskCreateManager.cpp',
    'Core/TaskHelpUtils/TaskHelpUtils.cpp',
    'Core/TaskListsHandle/TaskListsHandle.cpp',
    'DatabaseDriver/CCToDoDataBase.cpp',
    'DatabaseDriver/CCToDoDataBaseImpl.cpp',
    'DatabaseDriver/DataBaseAdder.cpp',
    'DatabaseDriver/DataBaseCommons.cpp',
    'DatabaseDriver/DataBaseQuery.cpp',
    'DatabaseDriver/DataBaseUpdater.cpp',
    'DatabaseDriver/DatabaseDeleter.cpp',
    'DatabaseDriver/TaskQueryAdapter.cpp',
    'Main/main.cpp',
    'Ui/CCToDoTreeDelegate/CCToDoTreeWidgetDelegate.cpp',
    'Ui/CCToDoTreeWidget/CCToDoTreeWidget.cpp',
    'Ui/CCToDoTreeWidgetItem/CCToDoTreeWidgetItem.cpp',
    'Ui/DisplayStatus/DisplayStatus.cpp',
    'Ui/MainWindow/CCToDoMainWindow.cpp',
    'Ui/MainWindow/MainWindowExternWidgetIniter.cpp',
    'Ui/MarkDownImportWindow/MarkDownImportWindow.cpp',
    'Ui/MarkdownExportWindow/MarkdownExportWindow.cpp',
    'Ui/TaskCreateWindow/TaskCreateMainWindow.cpp',
    'Ui/TaskDisplayWindow/TaskDisplayDialog.cpp',
    'Ui/TaskTreeWidgetItemFactory/TaskTreeWidegtItemFactory.cpp',
    'Ui/ToDoTreeWidgetHandler/ToDoTreeWidgetHandler.cpp',
    'Ui/UiSources/UiSources.cpp'
)

CCToDo_ui = files(
    'Ui/DisplayStatus/DisplayStatus.ui',
    'Ui/MainWindow/CCToDoMainWindow.ui',
    'Ui/MarkDownImportWindow/MarkDownImportWindow.ui',
    'Ui/MarkdownExportWindow/MarkdownExportWindow.ui',
    'Ui/TaskCreateWindow/TaskCreateMainWindow.ui',
    'Ui/TaskDisplayWindow/TaskDisplayDialog.ui'
)

CCToDo_ui_header = qt6.compile_ui(sources: CCToDo_ui) 
CCToDo_moc = qt6.compile_moc(
  headers: CCToDo_inc_files + CCToDo_ui_header, 
  sources: CCToDo_src, 
  dependencies: CCToDo_deps,
  include_directories: CCToDo_inc
)

CCToDoLists = executable(
  'CCToDoLists',
  sources: CCToDo_src + CCToDo_moc,
  include_directories: CCToDo_inc,
  dependencies: CCToDo_deps,
  install: false
)

# qtodolist = executable(
#   'qtodolist',
#   qtodolist_src,
#   include_directories: qtodolist_inc,
#   dependencies: qtodolist_deps,
#   install: true,
# )
