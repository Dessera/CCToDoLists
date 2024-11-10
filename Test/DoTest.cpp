#include "DoTest.h"
#include "TestAdd.h"
#include "TestDataBase.h"
#include "TestDeleter.h"
#include "TestQuery.h"
#include "TestTask.h"
#include "TestUpdate.h"

void TestAll::default_testAll() {
    TestTask taskTest;
    taskTest.doTest();

    TestDataBase dataBaseTest;
    dataBaseTest.doTest();

    TestQuery queryTest;
    queryTest.doTest();

    TestAdd addTest;
    addTest.doTest();

    TestUpdate updateTest;
    updateTest.doTest();

    TestDeleter deleteTest;
    deleteTest.doTest();
}
