# The cassert header only library that provide a simple testing scope.

1. First include the header and enable the `CASSERT_IMPLEMENTATION` macro to get the references for the linker.

### An example to get started:
```C
// A simple test function that compares the same ptr.
Test test1() {
  Test test = cassert_init_test("Test1");

  const char *a = __FILE__;
  const char *c = a;
  cassert_ptr_neq(a, c);
  return test;
}

Test test2() {
  Test test = cassert_init_test("Test1");

  const char *a = __FILE__;
  cassert_ptr_neq(a, NULL);
  return test;
}

// Call in a function. Common use is to just place it in the main function.
cassert_tests {
    cassert_dap(&tests, test1());
    cassert_dap(&tests, test2());
}

// Printing options
1. cassert_short_print_tests(&tests);
2. cassert_print_tests(&tests);

// Call at the end of all tests and after printing.
// This can be omitted when it is the last function in the program the OS
// will deallocate the memory automatically. If the tests are a separate program
// (which it usualy is) it doesn't matter to free the tests manually.
cassert_free_tests(&tests);
```
