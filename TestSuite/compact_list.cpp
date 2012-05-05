//
//  compact_list.cpp
//  BnutLibrary
//
//  Created by Andrew Bennett on 5/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "test_suite.h"

void compact_list_test(void)
{
    BL::CompactList<int> test;
    {
        BL::CompactList<int>::reference a, b, c;

        a = test.create( 1);
        b = test.create( 2);
        c = test.create( 3);

        c = test.create(13);
        b = test.create( 4);
        a = test.create(11);

        b = test.create(12);

        struct compact_list
        {
            static void check(const BL::CompactList<int>::const_reference& a)
            {
                assert(*a > 10);
            }
        };
        test.foreach(compact_list::check);

        assert(test.size() == 3);
        assert(test.capacity() == 4);
        //        test.report();
    }
    //    test.report();
}
