#ifndef TESTADD_H
#define TESTADD_H

#include "DoTest.h"

struct TestAdd : public DoTest {
    TestAdd()          = default;
    virtual ~TestAdd() = default;
    void doTest() override;
};

#endif  // TESTADD_H
