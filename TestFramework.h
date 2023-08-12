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

// Create a new test case
// Tests can be grouped
#define TEST_F(group, function) TEST_F_(group, function) 

// Filter tests.
// Select a test for execution
// Instead of commenting out all the tests, just pick those you want to run.
#define TEST_ONLY(group,test_name) TEST_ONLY_(group,test_name)

// Macros to test conditions

// test bool condtion - this will not terminate the test app
#define TEST_ASSERT(cond) Test::assert("TEST_ASSERT(" #cond ")", cond)

// test bool condition - if failed, this will terminate the test app
#define TEST_ASSERT_EXIT(cond) if( !Test::assert("TEST_ASSERT_EXIT(" #cond ")", cond) ) { return Test::Result::Exit; }

// test equality
#define TEST_EQ(expected, v) Test::equal("TEST_EQ(" #expected "," #v ")", expected, v)
