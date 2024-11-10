#ifndef DOTEST_H
#define DOTEST_H

class DoTest {
public:
    DoTest()              = default;
    virtual ~DoTest()     = default;
    virtual void doTest() = 0;
};

class TestAll {
public:
    static void default_testAll();
};

#endif  // DOTEST_H
