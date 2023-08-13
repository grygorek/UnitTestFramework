// Copyright 2023 Piotr Grygorczuk <grygorek@gmail.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
// 
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include <string>
#include <map>
#include <vector>
#include <functional>
#include <iostream>

namespace Test
{
enum class Result { Continue, Exit };
using TestCases = std::map<std::string, std::function<Result()>>;
extern TestCases g_test_cases;
extern std::map<std::string, TestCases> g_test_groups;
extern std::vector<std::string> g_failed_cases;
extern std::map<std::string, std::vector<std::string>> g_run_only;
extern std::function<Result()> g_TestAppInit;
extern std::function<void()> g_TestAppDestroy;
extern int g_failed_conditions;
}

namespace Test
{
inline void equal(const char* msg, const char* expected, const char* v)
{
  if (std::string(expected) != v)
  {
    g_failed_conditions++;
    std::cout << msg << " FAILED\n\t\t"
      << v << " != expected=" << expected << "\n";
  }
}

inline void equal(const char* msg, const auto &expected, const auto &v)
{
  if (expected != v)
  {
    g_failed_conditions++;
    std::cout << msg << " FAILED\n\t\t"
      << v << " != expected=" << expected << "\n";
  }
}

inline bool assert(const char* msg, bool cond)
{
  if (!cond)
  {
    g_failed_conditions++;
    std::cout << msg << " FAILED\n";
    return false;
  }
  return true;
}

}

#define TEST_APP_INIT_() \
  struct TestAppInit_ { \
    TestAppInit_() \
    { \
      Test::g_TestAppInit = [this] {return RunOnStartup(); }; \
    } \
    Test::Result RunOnStartup(); \
  }; \
  static TestAppInit_ g_TestAppInitAdd_; \
  Test::Result TestAppInit_::RunOnStartup()


#define TEST_APP_DESTROY_() \
  struct TestAppDestroy_ { \
    TestAppDestroy_() \
    { \
      Test::g_TestAppDestroy = [this] { RunOnExit(); }; \
    } \
    void RunOnExit(); \
  }; \
  static TestAppDestroy_ g_TestAppDestroyAdd_; \
  void TestAppDestroy_::RunOnExit()


// Create a new test case
// Tests can be grouped
#define TEST_F_(group, function) \
  struct TestCase##group##function \
  { /* ctor will add the test case to g_test_groups */ \
    TestCase##group##function() \
    { \
      Test::g_test_groups[#group][#function] = [this] { \
        auto r = TestBody();\
        if(Test::g_failed_conditions)\
          Test::g_failed_cases.push_back(#group "." #function);\
        return r;\
      };\
    }\
    Test::Result TestBody();\
  };\
  /* Create a global instance so the c-tor will be called*/ \
  static TestCase##group##function case##group##function; \
  /* Start the body of the test function. */ \
  Test::Result TestCase##group##function::TestBody()


// Filter tests. Select a test for execution
// Instead of commenting out all the tests, just pick those you want to run.
#define TEST_ONLY_(group,test_name) \
  struct FilterTestCase##group##test_name\
  { /* Ctor will add this case to the filtered tests*/ \
    FilterTestCase##group##test_name()\
    {\
      Test::g_run_only[#group].push_back(#test_name); \
    } \
  }; \
  /* Create a global instance so the c-tor will be called*/ \
  static FilterTestCase##group##test_name filtercase##group##test_name;

