#include "Config.h"
#include "Test.h"
#include "TestList.h"
#include "TestResults.h"
#include "AssertException.h"
#include "MemoryOutStream.h"
#include "ExecuteTest.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstring>
#include <iostream>

#ifdef UNITTEST_POSIX

#include "Posix/SignalTranslator.h"

#endif

long id=0;

namespace UnitTest {

    using namespace std;

    TestList &Test::GetTestList() {
        static TestList s_list;
        return s_list;
    }

    Test::Test(char const *testName, char const *suiteName, char const *filename, int lineNumber)
            : m_details(testName, suiteName, filename, lineNumber), m_nextTest(0), m_isMockTest(false) {}

    Test::~Test() {}

    void Test::Run() {
        long _id = id++;
        std::cerr << "Executing test: [" << _id << "] '" << this->m_details.suiteName << "'::'" << this->m_details.testName << "'\n";
//        std::cerr << "  Next test would be: '" << this->m_nextTest->m_details.suiteName << "', '" << this->m_nextTest->m_details.testName << "', '" << "'\n";
        ExecuteTest(*this, m_details, m_isMockTest);
        std::cerr << ".. Finished [" << _id << "]\n";
    }

    void Test::RunImpl() const {}

}
