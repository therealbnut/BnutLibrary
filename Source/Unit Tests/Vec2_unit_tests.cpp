//
//  Vec2_unit_tests.cpp
//  BnutLibrary
//
//  Created by Andrew Bennett on 6/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef BL_ENABLE_UNIT_TESTS
#include <BL/Vec2.h>

#include <iostream>

namespace BL
{
    template<>
    void BL::Vec2f::_runUnitTests(BL::UnitTest& unit_test)
    {
        BL::Vec2f a = BL::Vec2f(1.0, 2.0);
        BL::Vec2f b = BL::Vec2f(4.0, 6.0);

        BLTest(a.x == 1.0 && a.y == 2.0, "Vec2f(a,b) construction.");

        BLTest( (a == BL::Vec2f(1.0, 2.0)), "Vec2f   a == a.");
        BLTest( (a != BL::Vec2f(4.0, 6.0)), "Vec2f   a != b.");
        BLTest(!(a == BL::Vec2f(4.0, 6.0)), "Vec2f !(a == b).");
        BLTest(!(a != BL::Vec2f(1.0, 2.0)), "Vec2f !(a != b).");

        BLTest( (a+b == BL::Vec2f( 5.0,  8.0)), "Vec2f   a + a.");
        BLTest( (a-b == BL::Vec2f(-3.0, -4.0)), "Vec2f   a - b.");

        BLTest((a-b).length2() == 25, "(a-b).length2()");
        BLTest((a-b).length()  ==  5, "(a-b).length()");

        BLTest(BL::Vec2f::Distance2(a,b) == 25, "Distance2(a, b)");
        BLTest(BL::Vec2f::Distance(a,b)  ==  5, "Distance(a, b)");

        BLTest(BL::Vec2f::Dot(a, b) == 16.0, "Dot(a,b)");

        BLTest((fabs((a-b).normalized().x+0.6) < 0.000001), "|a-b|.x");
        BLTest((fabs((a-b).normalized().y+0.8) < 0.000001), "|a-b|.y");
    }
}

#endif
