# Very basic unit test framework for C++ applications.

## Inspiration

Inspired by Google test framework but way more simplified.

Main requirement is to have a simple framework to use in embedded systems running standalone application, where Google test might be too heavy.

## Features

(Goal features, not all the features are implemented yet)

1. Easy to create a test case, without thinking how it will be executed.
2. Allows grouping test cases. 
   * Single test application may test features from different components.
3. Allows filtering tests.
   * During debugging we may wish to run a single test or all tests from a group. Google test allows filtering from a command line but an embedded standalone application does not have a command line.
4. Initialize the environment for the whole application.
   * Test may require to load data (e.g. using ARM semihosting, etc.) needed for the test application, but not specific to a particular test case. 
5. Setup a test environment specific for a group of tests.
   * Group of tests may require a specific setting that may be invalid for another group of tests.
6. Destroy the test environment created for a group of tests.
   * Group of tests may require a specific setting that may be invalid for another group of tests.
7. Provide API to test conditions.
8. Each test case should print a short pass/fail summary.
9. Failed condition should result in printing the input condition and a short information what has failed.
10. Finished test application should print a list of failing tests.
11. Finished test application should print a final pass/fail result.

## Usage

Add `TestFramework.cpp` to your project. The file has the `main` function already. So your project should not have the main.
Include `TestFramework.h` file in your test applicaiton cpp file.

### Application Environment Setup and Destruction

Define a function with the `TEST_APP_INIT` macro to setup your test application environment. This function is called at the very start of the execution. Before any of the tests are executed.

If setting the environment was successfull, function should return Result::Continue to progress with the test cases. In the case of the environment setup failure, it maybe that there is no point to run any of the tests. Function should return Result::Exit in that case. Doing so, none of the tests will run and also TEST_APP_DESTROY will not run either.

Define a function with the `TEST_APP_DESTROY` macro to cleanup your application environment. This funciton is called at the very end of the application execution. After all the tests. Function is called always, regardless if tests have passed or failed. It will be called also, if any of the tests returned Result::Exit. The only time when this function will NOT be called, when the TEST_APP_INIT returned Result::Exit, indicating the setup has failed.

Example:

```cpp
TEST_APP_INIT()
{
  ...Init your test environment here...
  return Test::Result::Continue;
}

TEST_APP_DESTROY()
{
  ...Do cleanup of your test environment...
}
```

### Test Cases


Create a new file where you want to put functions for your test cases. You can create a test case with `TEST_F` macro. Example:

```cpp
TEST_F(module1, TestCase1)
{
  TEST_EQ(1024, pow2(10));
  return Test::Result::Continue;
}

TEST_F(module1, TestCase2)
{
  TEST_ASSERT_EXIT(true == InitializePeripherals());
  ...use the peripherals...
  return Test::Result::Continue;
}
```

In the example above we create a `TestCase1`, which is a test function. That function belongs to a `module1` group. The unit test framework will execute your test function for you. The TEST_EQ macro will check the condition if 2 to the power of 10 is 1024. The macro will print a short report on failure. The function returns `Result::Continue` to indicate that we still want to continue with the other test cases. If we returned `Result::Exit`, the test application would not continue with the remaining tests. The test application would return and the whole test would FAIL. 

In the `TestCase2` we use an assert macro with the exit on failure. In this case, if the `InitializePeriperals` function fails, most likely there is no point continuing the test application. The function will return with the `Result::Exit` result and the whole application will exit with the FAIL result.

### Filtering

It may happen that your application has many test cases and it takes time to run them. Unfortunately one of them may be failing and you would end up debugging it. What you may want to do is to disable all other tests and run just the one which is failing. Disabling all the tests would require commenting out all tests, which would be tedious. Instead, you may tell which tests you want to run. For example:

```cpp
TEST_ONLY(module1,TestCase1);
TEST_ONLY(module2,);
```

In this example we want to run ALL the test cases from the `module2` and only the `TestCase1` from the `module1`. All other tests will not execute.
