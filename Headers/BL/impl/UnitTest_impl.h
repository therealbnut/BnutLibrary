//
//  UnitTest_impl.h
//  BnutLibrary
//
//  Created by Andrew Bennett on 6/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef BnutLibrary_UnitTest_impl_h
#define BnutLibrary_UnitTest_impl_h

#ifndef BL_ENABLE_UNIT_TESTS
#error Unit Testing not enabled!
#endif

#include <stack>
#include <string>

namespace BL
{
    class UnitTest
    {
    public:
        class AssertionFailure
        {
        public:
            AssertionFailure(const std::string& string);

            inline const std::string& msg(void)  const {return this->m_string;}

        private:
            const std::string m_string;
        };

        typedef void (*Tests)(UnitTest& test);

        static void RunSuite(Tests suite);
        static void RunTests(const std::string& name, Tests tests);

        static void Test(bool test, const std::string& context);

        BLDefineUnitTest("Unit Test");

        inline int passed(void) const {return this->m_passed.top();}
        inline int failed(void) const {return this->m_failed.top();}

    protected:
        void _runSuite(const std::string& name, Tests suite);

        inline int& _passed(void) {return this->m_passed.top();}
        inline int& _failed(void) {return this->m_failed.top();}

        void testPass(void) const;
        void testFail(void) const;

        void printMessage(const std::string& msg) const;
        void printError(const std::string& msg) const;
        
    private:
        UnitTest(bool shouldLog = true);

        std::stack<int> m_passed;
        std::stack<int> m_failed;
        bool            m_log;

        static UnitTest * CURRENT;
    };
}

#endif
