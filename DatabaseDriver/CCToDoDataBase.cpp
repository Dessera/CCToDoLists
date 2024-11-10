#include "CCToDoDataBase.h"
#include <QMutexLocker>
std::unique_ptr<CCToDoDataBaseImpl> CCToDoDataBase::instance = nullptr;

/*
    Typical Singleton pattern implementation.
*/
CCToDoDataBaseImpl* CCToDoDataBase::getInstance() {
    static QMutex mutex;
    if (!instance) {
        QMutexLocker locker(&mutex);
        if (!instance) {
            instance.reset(new CCToDoDataBaseImpl);
        }
    }
    return instance.get();
}

bool CCToDoDataBase::isKey(const QString& aKey) {
    for (const auto it : AVAILABLE_KEYS) {
        if (aKey == it) return true;
    }
    return false;
}
