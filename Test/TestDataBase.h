#ifndef TESTDATABASE_H
#define TESTDATABASE_H
#include "DoTest.h"
class TestDataBase : public DoTest {
public:
    TestDataBase()          = default;
    virtual ~TestDataBase() = default;
    virtual void doTest() override;
};

#endif  // TESTDATABASE_H
