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

#include "TestFrameworkInternal.h"

// Define a function with this macro to run as first, before any tests.
// This can be usefull to setup an environment.
// Should return Test::Result::Continue to proceed with a next test.
// Can return Test::Result::Exit to interrupt the test. None of the tests will run
// nor the TEST_APP_DESTROY will be called too.
#define TEST_APP_INIT() TEST_APP_INIT_()

// Define a function with this macro to run as a cleanup of the environment.
// It will run before the test application exit, after any tests, regardless pass or fail.
// It will not run only if the TEST_APP_INIT has failed and returned Test::Result::Exit.
// Returns void.
#define TEST_APP_DESTROY() TEST_APP_DESTROY_()

// Create a new test case function.
// Tests can be grouped
// Should return Test::Result::Continue to proceed with the next test.
// Can return Test::Result::Exit to interrupt the test app. None of the remaining tests will run.
#define TEST_F(group_name, test_case_name) TEST_F_(group_name, test_case_name) 

// Filter tests.
// Select a test for execution
// Instead of commenting out all the tests, just pick those you want to run.
// This can be useful, for example, if there is many tests and only one is failing.
// The failing one can be filtered for execution, ignoring the remaining tests.
#define TEST_ONLY(group_name, test_case_name) TEST_ONLY_(group_name, test_case_name)

// Macros to test conditions

// test bool condtion - if failed it will not terminate the test app
#define TEST_ASSERT(cond) Test::assert("TEST_ASSERT(" #cond ")", cond)

// test bool condition - if failed it will terminate the test app
#define TEST_ASSERT_EXIT(cond) if( !Test::assert("TEST_ASSERT_EXIT(" #cond ")", cond) ) { return Test::Result::Exit; }

// test equality
#define TEST_EQ(expected, v) Test::equal("TEST_EQ(" #expected "," #v ")", expected, v)
