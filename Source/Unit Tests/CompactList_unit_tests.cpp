//
//  CompactList.cpp
//  BnutLibrary
//
//  Created by Andrew Bennett on 6/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef BL_ENABLE_UNIT_TESTS

#include <BL/CompactList.h>

namespace BL
{
    struct compact_list_test
    {
        static bool in_range;
        static int allThere[8];
        static void init(void)
        {
            in_range = true;
            for (int i=0; i<8; ++i)
                allThere[i] = 0;
        }
        static void check(const BL::CompactList<int>::const_reference& a)
        {
            in_range &= (0 < *a) && (*a < 8);
            if (in_range)
            {
                ++allThere[*a];
            }
        }
    };
    bool compact_list_test::in_range;
    int compact_list_test::allThere[8];

    template<>
    void BL::CompactList<int>::_runUnitTests(BL::UnitTest& unit_test)
    {
        BL::CompactList<int> test;
        {
            BL::CompactList<int>::reference a, b, c;
            
                a = test.create(1);
                b = test.create(2);
                c = test.create(3);
            c = test.create(7);
                b = test.create(4);
            a = test.create(5);
            b = test.create(6);

            compact_list_test::init();
            test.foreach(compact_list_test::check);

            BLTest(compact_list_test::in_range,     "All iterated values in range.");
            BLTest(compact_list_test::allThere[1]==0, "Test value 1 invalidated.");
            BLTest(compact_list_test::allThere[2]==0, "Test value 2 invalidated.");
            BLTest(compact_list_test::allThere[3]==0, "Test value 3 invalidated.");
            BLTest(compact_list_test::allThere[4]==0, "Test value 4 invalidated.");

            BLTest(compact_list_test::allThere[5]>=1, "Test value 5 iterated.");
            BLTest(compact_list_test::allThere[6]>=1, "Test value 6 iterated.");
            BLTest(compact_list_test::allThere[7]>=1, "Test value 7 iterated.");

            BLTest(compact_list_test::allThere[5]==1, "Test value 5 iterated once.");
            BLTest(compact_list_test::allThere[6]==1, "Test value 6 iterated once.");
            BLTest(compact_list_test::allThere[7]==1, "Test value 7 iterated once.");

            BLTest(test.size()     == 3, "List object count equal to the number of active references.");
            BLTest(test.capacity() <= 4, "List capacity at most the expected capacity.");
//        test.report();
        }
//    test.report();
    }
}

#endif
