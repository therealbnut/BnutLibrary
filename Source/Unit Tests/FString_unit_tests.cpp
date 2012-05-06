//
//  FString_unit_tests.cpp
//  BnutLibrary
//
//  Created by Andrew Bennett on 6/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef BL_ENABLE_UNIT_TESTS

#include <BL/FString.h>

namespace BL
{
    void BL::FString::_runUnitTests(BL::UnitTest& unit_test)
    {
        BLTest("a"   == BL::fstring('a'), "char formatted");
        BLTest("a"   == BL::fstring("a"), "string formatted");
        BLTest("123" == BL::fstring(123), "int formatted");
        BLTest("1.2" == BL::fstring(1.2), "float formatted");
        
        BLTest("ab" == BL::fstring('a','b'), "2 arguments concatenated");
        BLTest("abc" == BL::fstring('a','b','c'), "3 arguments concatenated");
        BLTest("abcd" == BL::fstring('a','b','c','d'), "4 arguments concatenated");
        BLTest("abcde" == BL::fstring('a','b','c','d','e'), "5 arguments concatenated");
    }
}

#endif
