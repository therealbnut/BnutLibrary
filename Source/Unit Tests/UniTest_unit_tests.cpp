//
//  UniTest_unit_tests.cpp
//  BnutLibrary
//
//  Created by Andrew Bennett on 6/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef BL_ENABLE_UNIT_TESTS

#include <BL/UnitTest.h>

namespace BL
{
    void UnitTest_testSuccess(BL::UnitTest& unit_test)
    {
        BLTest(true, "should pass.");
    }
    void UnitTest_testFailure(BL::UnitTest& unit_test)
    {
        BLTest(false, "should fail.");
    }
    void UnitTest_assertSuccess(BL::UnitTest& unit_test)
    {
        BLAssert(true, "should pass.");
    }
    void UnitTest_assertFailure(BL::UnitTest& unit_test)
    {
        BLAssert(false, "should fail.");
    }
    void UnitTest_assertExit(BL::UnitTest& unit_test)
    {
        BLAssert(false, "should fail.");
        BLTest(true, "shouldn't get here.");
    }
    void BL::UnitTest::_runUnitTests(BL::UnitTest& unit_test)
    {
        {
            BL::UnitTest sub_tests(false); // silent
            sub_tests._runSuite("BLTest(true)", UnitTest_testSuccess);
            BLTest(sub_tests.passed() == 1, "BLTest(true, ...) must pass.");
            BLTest(sub_tests.failed() == 0, "BLTest(true, ...) must not fail.");
        }
        {
            BL::UnitTest sub_tests(false); // silent
            sub_tests._runSuite("BLTest(false)", UnitTest_testFailure);
            BLTest(sub_tests.passed() == 0, "BLTest(false, ...) must not pass.");
            BLTest(sub_tests.failed() == 1, "BLTest(false, ...) must fail.");
        }
        {
            BL::UnitTest sub_tests(false); // silent
            sub_tests._runSuite("BLAssert(true)", UnitTest_assertSuccess);
            BLTest(sub_tests.passed() == 0, "BLAssert(true) must not pass.");
            BLTest(sub_tests.failed() == 0, "BLAssert(true) must not fail.");
        }
        {
            BL::UnitTest sub_tests(false); // silent
            sub_tests._runSuite("BLAssert(false)", UnitTest_assertFailure);
            BLTest(sub_tests.passed() == 0, "BLAssert(false) must not pass.");
            BLTest(sub_tests.failed() == 1, "BLAssert(false) must fail.");
        }
        {
            BL::UnitTest sub_tests(false); // silent
            sub_tests._runSuite("BLAssert(exit)", UnitTest_assertExit);
            BLTest(sub_tests.passed() == 0, "BLAssert(false) exits.");
        }
    }
}

#endif
