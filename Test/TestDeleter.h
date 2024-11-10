#ifndef TESTDELETER_H
#define TESTDELETER_H

#include "DoTest.h"

class TestDeleter : public DoTest {
public:
    TestDeleter()          = default;
    virtual ~TestDeleter() = default;
    void doTest() override;
};

#endif  // TESTDELETER_H
