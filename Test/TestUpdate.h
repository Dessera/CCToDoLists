#ifndef TESTUPDATE_H
#define TESTUPDATE_H
#include "DoTest.h"

struct TestUpdate : public DoTest {
    TestUpdate()  = default;
    ~TestUpdate() = default;
    virtual void doTest() override;
};

#endif  // TESTUPDATE_H
