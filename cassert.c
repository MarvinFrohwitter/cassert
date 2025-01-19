#ifndef CASSERT_H_
#define CASSERT_H_

#include <assert.h>
#include <stdbool.h>

typedef enum {
  UNKNOWN,
  STRING_EQ,
  PTR_EQ,
  ASSERT_TYPE_COUNT,
} Assert_Type;

typedef struct {
  bool failed;
  int result;
  const void *value1;
  const void *value2;
  Assert_Type assert_type;
} Cassert;

Cassert ca_assert_string_eq(const char *a, const char *b);
Cassert ca_assert_ptr_eq(const void *a, const void *b);
const char *cassert_str_assert_type(Assert_Type assert_type);
int cassert_print(Cassert cassert);
int cassert_print_failure_case(Cassert cassert);

#endif // CASSERT_H_

// ===========================================================================

#ifdef CASSERT_IMPLEMENTATION

#include <stdio.h>
#include <string.h>

Cassert ca_assert_string_eq(const char *a, const char *b) {
  Cassert cassert = {0};
  cassert.assert_type = STRING_EQ;
  cassert.value1 = a;
  cassert.value2 = b;
  cassert.result = strcmp(a, b);
  if (cassert.result != 0) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert ca_assert_ptr_eq(const void *a, const void *b) {
  Cassert cassert = {0};
  cassert.assert_type = PTR_EQ;
  cassert.value1 = a;
  cassert.value2 = b;
  if (a != b) {
    cassert.failed = true;
  }
  return cassert;
}

const char *cassert_str_assert_type(Assert_Type assert_type) {
  static_assert(ASSERT_TYPE_COUNT == 3, "assert types count has changed");
  switch (assert_type) {
  case STRING_EQ:
    return "STRING_EQ";
  case PTR_EQ:
    return "PTR_EQ";
  case UNKNOWN:
  default:
    return "";
  }
}

int cassert_print(Cassert cassert) {
  switch (cassert.assert_type) {
  case STRING_EQ:
    return fprintf(stderr, "%s%s%s\n", (char *)cassert.value1,
                   cassert_str_assert_type(cassert.assert_type),
                   (char *)cassert.value2);
  case PTR_EQ:
    return fprintf(stderr, "%p%s%p\n", cassert.value1,
                   cassert_str_assert_type(cassert.assert_type),
                   cassert.value2);
  case UNKNOWN:
  default:
    return fprintf(stderr, "%s \n",
                   cassert_str_assert_type(cassert.assert_type));
  }
}

int cassert_print_failure_case(Cassert cassert) {
  return cassert_print(cassert);
}

Cassert test1(void) {
  const char *a = __FILE__;
  const char *c = a;
  // TODO Set the name of the test.
  return ca_assert_ptr_eq(a, c);
}

Cassert test2(void) {
  const char *a = __FILE__;
  return ca_assert_string_eq(a, __FILE__);
}

Cassert cassert_cases() {
  Cassert ctest1 = test1();
  if (ctest1.failed)
    cassert_print_failure_case(ctest1);
  return ctest1;

  Cassert ctest2 = test2();
  if (ctest2.failed)
    cassert_print_failure_case(ctest2);
  return ctest2;

  return (Cassert){0};
}

#endif // CASSERT_IMPLEMENTATION
