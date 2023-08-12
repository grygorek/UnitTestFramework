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

#include "TestFramework.h"

#include <stdlib.h>
#include <iostream>
#include <functional>
#include <map>
#include <vector>
#include <string>

namespace Test
{
// Collection of all tests in the application
std::map<std::string, TestCases> g_test_groups;
// Filter. Collection of tests that should run. All other will be skipped.
std::map<std::string, std::vector<std::string>> g_run_only;
// Names of failed tests
std::vector<std::string> g_failed_cases;
// Count of failed conditions from one test case
int g_failed_conditions;
}

using namespace Test;

namespace
{
void PrintFailed()
{
  using namespace Test;

  if (g_failed_cases.size() == 0)
  {
    std::cout << "\n------------------\nTestResult: PASS\n------------------\n";
    return;
  }

  std::cout << "\n\n\n------------------\nFailed tests:\n";
  for (auto& name : g_failed_cases)
  {
    std::cout << "\t" << name << "\n";
  }

  std::cout << "------------------\nTestResult: FAIL\n------------------\n";
}

bool SkipTest(const std::string &group_name, const std::string &name)
{
  if (g_run_only.size() == 0)
    // No filter. All tests should run
    return false;

  auto& group = g_run_only[group_name];
  if (group.size() == 1 && group[0] == "")
    // Group is elected and the function name is empty.
    // Run all tests from this group
    return false;

  // If the test is not found, means it is not selected to run - skip it.
  bool skip = std::find(group.begin(), group.end(), name) == group.end();
  return skip;
}

std::pair<int, int> CountTests(auto &map)
{
  int groups = static_cast<int>(map.size());
  int all_tests = 0;
  for (auto& [gname, group] : map)
    all_tests += static_cast<int>(group.size());

  return { groups, all_tests };
}

bool RunTests()
{
  if (g_run_only.size() == 0)
  {
    auto [groups_cnt, tests] = CountTests(g_test_groups);
    std::cout << "Running all " << tests << " test cases from " << groups_cnt << " groups.\n\n";
  }
  else
  {
    std::cout << "Running only selected test cases\n\n";
  }

  for (auto& [group_name, group] : g_test_groups)
  {
    for (auto& [test_name, function] : group)
    {
      if (SkipTest(group_name, test_name))
        continue;

      std::cout << "\n\n------------------\nRun... " << group_name << "." << test_name << "\n";
      g_failed_conditions = 0;

      auto result = function();

      std::cout << "------------------\n" << test_name
        << (g_failed_conditions || result == Result::Exit ? "   FAIL" : "   PASS")
        << " \n------------------\n";

      if (Result::Exit == result)
      {
        std::cout << "Test completed and requested exit.\n\n";
        g_failed_cases.push_back(test_name);
        return false;
      }
    }
  }
 
  return true;
}

}

int main()
{
  if (!RunTests())
  {
    PrintFailed();
    return EXIT_FAILURE;
  }

  PrintFailed();
  return EXIT_FAILURE;
}

