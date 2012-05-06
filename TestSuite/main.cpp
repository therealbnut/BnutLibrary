//
//  main.cpp
//  BnutLibrary
//
//  Created by Andrew Bennett on 5/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <BL/BL.h>

void all_tests(BL::UnitTest& unit_test)
{
    BL::CompactList<int>::RunUnitTests();
    BL::UnitTest::RunUnitTests();
    BL::FString::RunUnitTests();
    BL::Vec2f::RunUnitTests();
}

int main(int argc, const char * argv[])
{
    BL::UnitTest::RunSuite(all_tests);

    return EXIT_SUCCESS;
}

