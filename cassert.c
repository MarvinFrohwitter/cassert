#include <stddef.h>
#define CASSERT_IMPLEMENTATION
#include "cassert.h"

void test1(Casserts *casserts) {
  const char *a = __FILE__;
  const char *c = a;
  // TODO Set the name of the test.
  cassert_ptr_eq(a, c);
}

void test2(Casserts *casserts) {
  const char *a = __FILE__;

  cassert_string_eq("h", "H");
  cassert_string_int64_eq("5", 5.01);
  cassert_float_eq(2.3, 5.01);
}

int main(int argc, char *argv[]) {
  Casserts casserts = {0};
  cassert_cases() {
    test1(&casserts);
    test2(&casserts);
  }

  printf("[TEST] Amount:%zu\n", casserts.count);
  cassert_print_all_cases(&casserts);
  cassert_array_free_case_value_mem(&casserts);
  return 0;
}
