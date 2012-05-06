//
//  UnitTest.h
//  BnutLibrary
//
//  Created by Andrew Bennett on 6/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BnutLibrary_UnitTest_h
#define BnutLibrary_UnitTest_h

#ifdef BL_ENABLE_UNIT_TESTS
    #define BLDefineUnitTest(NAME) \
        static inline void RunUnitTests(void) {BL::UnitTest::RunTests(NAME,_runUnitTests);} \
    private: \
        static void _runUnitTests(BL::UnitTest& unit_test); \
    public:

    #define BLAssert(TEST, MSG) \
    {\
        if (!(TEST)) throw BL::UnitTest::AssertionFailure((MSG));\
    }
    #define BLTest(TEST,MSG) \
        BL::UnitTest::Test((TEST),(MSG))

    #include <BL/impl/UnitTest_impl.h>

#else
    #define BLDefineUnitTest(NAME)
    #define BLAssert(TEST,MSG) {}
    #define BLTest(TEST,MSG)  {}

#endif

#endif
