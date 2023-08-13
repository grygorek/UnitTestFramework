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

TEST_APP_INIT()
{
  std::cout << "Test Application Initialize - This runs as first, before anything else!\n";
  return Test::Result::Continue;

  // Returning Result::Exit will not start the test at all.
  // Also, it will not run the TEST_APP_DESTROY function at exit.
  // return Test::Result::Exit;
}

TEST_APP_DESTROY()
{
  std::cout << "Test Application Destruction - This runs as last, after anything else!\n";
}


//
// Group 1 tests

TEST_F(group1, MyExampleTestCase)
{
  int value = 77;
  TEST_EQ(77, value);
  TEST_EQ(5, value);
  TEST_ASSERT(value == 77);
  TEST_ASSERT(value == 55);

  TEST_ASSERT_EXIT(value == 77);
  //TEST_ASSERT_EXIT(value == 55);

  return Test::Result::Continue;
}

TEST_F(group1, TestCase_2) {
  TEST_EQ(5, 5);
  return Test::Result::Continue;
}


//
// Group 2 tests

TEST_F(group2, MyExampleTestCase)
{
  TEST_EQ(5,5);
  return Test::Result::Continue;
}

TEST_F(group2, TestCase_2)
{
  TEST_EQ("hello", "world");
  return Test::Result::Continue;
}


// Uncomment this one to run only this single test
//TEST_ONLY(group1,TestCase_2);

// Uncomment this one to run all tests from the group1
//TEST_ONLY(group1,);
