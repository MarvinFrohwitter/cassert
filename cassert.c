#define CASSERT_IMPLEMENTATION
#include "cassert.h"

Test test1() {
  Test test = {0};
  test.name = "Test1";

  const char *a = __FILE__;
  const char *c = a;
  cassert_ptr_eq(a, c);
  return test;
}

Test test2() {
  Test test = {0};
  test.name = "Test2";

  cassert_string_eq("h", "H");
  cassert_string_int64_eq("5", 5.01);
  cassert_float_eq(2.3, 5.01);
  return test;
}

int main(int argc, char *argv[]) {
  cassert_tests {
    cassert_dap(&tests, test1());
    cassert_dap(&tests, test2());
  }

  cassert_print_tests(&tests);
  cassert_free_tests(&tests);
  return 0;
}
