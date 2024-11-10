#include "DataBaseCommons.h"
#include <QList>
static constexpr const char TUPLE_BEGIN = '(';
static constexpr const char TUPLE_END   = ')';

/*
    Oh my... I have to do this
*/

QString DataBaseCommons::fromIDGroup(const QList<int>& ids) {
    QString str_ids;
    for (const int id : ids) {
        str_ids += QString::number(id) + ',';
    }
    str_ids.removeLast();
    return QString("%1 %2 %3").arg(TUPLE_BEGIN).arg(str_ids).arg(TUPLE_END);
}
