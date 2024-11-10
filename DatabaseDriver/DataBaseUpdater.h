#ifndef DATABASEUPDATER_H
#define DATABASEUPDATER_H
#include <QPair>
#include <QString>
#include "Task.h"
struct DataBaseUpdater {
    // to change as the update goes
    static bool updateTargetTask(Task& update);
};

#endif  // DATABASEUPDATER_H
