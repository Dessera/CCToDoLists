#ifndef TESTQUERY_H
#define TESTQUERY_H
#include "DoTest.h"

class TestQuery : public DoTest {
public:
    TestQuery()          = default;
    virtual ~TestQuery() = default;
    virtual void doTest() override;
};

#endif  // TESTQUERY_H
