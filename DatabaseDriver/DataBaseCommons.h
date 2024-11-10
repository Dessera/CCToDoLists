#ifndef DATABASECOMMONS_H
#define DATABASECOMMONS_H
#include <QString>
/*
    There provides some common operations

*/

struct DataBaseCommons {
    static QString fromIDGroup(const QList<int>& ids);
};

#endif  // DATABASECOMMONS_H
