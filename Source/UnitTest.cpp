//
//  UnitTest.cpp
//  BnutLibrary
//
//  Created by Andrew Bennett on 6/05/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifdef BL_ENABLE_UNIT_TESTS

#include <BL/UnitTest.h>
#include <BL/FString.h>
#include <iostream>

BL::UnitTest * BL::UnitTest::CURRENT = NULL;

BL::UnitTest::UnitTest(bool shouldLog) : m_log(shouldLog)
{
    this->m_passed.push(0);
    this->m_failed.push(0);
}

BL::UnitTest::AssertionFailure::AssertionFailure(const std::string& str)
  : m_string(str)
{
}

void BL::UnitTest::printError(const std::string& msg) const
{
    if (this->m_log)
    {
        for (int i=1; i<this->m_passed.size(); ++i)
            std::cout << "* ";
        std::cout << msg << std::endl;
    }
}

void BL::UnitTest::printMessage(const std::string& msg) const
{
    if (this->m_log)
    {
        for (int i=1; i<this->m_passed.size(); ++i)
            std::cerr << "| ";
        std::cerr << msg << std::endl;
    }
}

void BL::UnitTest::_runSuite(const std::string& name, Tests suite)
{
    BL::UnitTest * old_test = BL::UnitTest::CURRENT;
    BL::UnitTest::CURRENT = this;
    BL::UnitTest::RunTests(name, suite);
    BL::UnitTest::CURRENT = old_test;
}

void BL::UnitTest::RunSuite(Tests suite)
{
    BL::UnitTest unit_test_main;
    BLAssert(BL::UnitTest::CURRENT == NULL, "BL::UnitTest is already running a suite!");
    unit_test_main._runSuite("All Unit Tests", suite);
}

void BL::UnitTest::RunTests(const std::string& name, Tests tests)
{
    UnitTest * ut = BL::UnitTest::CURRENT;
    BLAssert(ut != NULL, "BL::UnitTest not ready!");

    ut->printMessage(BL::fstring(name, ":"));

    ut->m_passed.push(0);
    ut->m_failed.push(0);

    try
    {
        tests(*ut);
    }
    catch(const BL::UnitTest::AssertionFailure& failure)
    {
        ut->printError(BL::fstring("Critical failure: ", failure.msg()));
        ut->testFail();
    }
    catch(const std::exception& e)
    {
        ut->printError(BL::fstring("Uncaught exception: ", e.what()));
        ut->testFail();
    }

    int  pass  = ut->passed();
    int  fail  = ut->failed();

    ut->m_passed.pop();
    ut->m_failed.pop();

    ut->printMessage(BL::fstring("(", pass, " / ", (pass + fail), ")"));

    if (!ut->m_passed.empty())
    {
        if (fail > 0)
        {
            ut->printMessage(BL::fstring("Failure in ", name));
        }
        ut->_passed() += pass;
        ut->_failed() += fail;
    }
}

void BL::UnitTest::Test(bool test, const std::string& context)
{
    UnitTest * ut = BL::UnitTest::CURRENT;
    BLAssert(ut != NULL, "BL::UnitTest not ready!");

    std::string msg = BL::fstring(test ? "pass" : "fail", ": ", context);
    if (test)
    {
        ut->printMessage(msg);
        ut->testPass();
    }
    else
    {
        ut->printError(msg);
        ut->testFail();
    }
}

void BL::UnitTest::testPass(void) const
{
    UnitTest * ut = BL::UnitTest::CURRENT;
    BLAssert(ut != NULL, "BL::UnitTest not ready!");

    ++ut->_passed();
}

void BL::UnitTest::testFail(void) const
{
    UnitTest * ut = BL::UnitTest::CURRENT;
    BLAssert(ut != NULL, "BL::UnitTest not ready!");

    ++ut->_failed();
}

#endif
