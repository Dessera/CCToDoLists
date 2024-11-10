#ifndef CCTODODATABASE_H
#define CCTODODATABASE_H
#include <QString>
#include "CCToDoDataBaseImpl.h"

/*
    pImpl method:)
    We promised the singleton pattern
*/

class CCToDoDataBase {
    static std::unique_ptr<CCToDoDataBaseImpl> instance;

public:
    /* fetch instance from here */
    static CCToDoDataBaseImpl*   getInstance();
    static constexpr const char* KEY_ID              = "ID";
    static constexpr const char* KEY_MAIN_TASK       = "MainTask";
    static constexpr const char* KEY_DESCRIPTIONS    = "Descriptions";
    static constexpr const char* KEY_PRIORITY        = "Priority";
    static constexpr const char* KEY_BEGIN_DATE      = "BeginDate";
    static constexpr const char* KEY_END_DATE        = "EndDate";
    static constexpr const char* KEY_BELONGING_GROUP = "BelongingGroup";
    static constexpr const char* KEY_PARENTID        = "Parent";
    static constexpr const char* KEY_IS_FINISHED     = "isFinished";

    /* Gain Database key at a compile time */
    /* U can use navicat or something else to see the database.db */
    static constexpr const char* AVAILABLE_KEYS[] = {
        KEY_ID,         KEY_MAIN_TASK, KEY_DESCRIPTIONS,    KEY_PRIORITY,
        KEY_BEGIN_DATE, KEY_END_DATE,  KEY_BELONGING_GROUP, KEY_PARENTID,
        KEY_IS_FINISHED};
    static bool isKey(const QString& aKey);
};

#endif  // CCTODODATABASE_H
