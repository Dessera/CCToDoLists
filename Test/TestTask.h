#ifndef TESTTASK_H
#define TESTTASK_H
#include "DoTest.h"

class TestTask : public DoTest {
public:
    TestTask()          = default;
    virtual ~TestTask() = default;
    void doTest() override;
};

#endif  // TESTTASK_H
