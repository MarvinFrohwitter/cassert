#ifndef CASSERT_H_
#define CASSERT_H_

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
  UNKNOWN,
  STRING_EQ,
  PTR_EQ,

  SHORT_EQ,
  INT_EQ,
  LONG_EQ,
  LONG_LONG_EQ,

  USHORT_EQ,
  UINT_EQ,
  ULONG_EQ,
  ULONG_LONG_EQ,

  SSIZE_T_EQ,
  SIZE_T_EQ,

  INT8_T_EQ,
  INT16_T_EQ,
  INT32_T_EQ,
  INT64_T_EQ,

  UINT8_T_EQ,
  UINT16_T_EQ,
  UINT32_T_EQ,
  UINT64_T_EQ,
  FLOAT_T_EQ,
  DOUBLE_T_EQ,

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

#define ca_assert_eq(a, compare, b)                                            \
  do {                                                                         \
    Cassert cassert = {0};                                                     \
    cassert.assert_type = UNKNOWN;                                             \
    cassert.value1 = &a;                                                       \
    cassert.value2 = &b;                                                       \
    cassert.result = a compare b ? 1 : 0;                                      \
    if (!cassert.result) {                                                     \
      cassert.failed = true;                                                   \
    }                                                                          \
    return cassert;                                                            \
  } while (0);


Cassert cassert_short_eq(const short a, const short b);
Cassert cassert_int_eq(const int a, const int b);
Cassert cassert_long_eq(const long a, const long b);
Cassert cassert_long_long_eq(const long long a, const long long b);
Cassert cassert_ushort_eq(const unsigned short a, const unsigned short b);
Cassert cassert_uint_eq(const unsigned int a, const unsigned int b);
Cassert cassert_ulong_eq(const unsigned long a, const unsigned long b);
Cassert cassert_ulong_long_eq(const unsigned long long a,
                              const unsigned long long b);


Cassert cassert_size_t_eq(const size_t a, const size_t b);
Cassert cassert_int8_t_eq(const int8_t a, const int8_t b);
Cassert cassert_int16_t_eq(const int16_t a, const int16_t b);
Cassert cassert_int32_t_eq(const int32_t a, const int32_t b);
Cassert cassert_int64_t_eq(const int64_t a, const int64_t b);
Cassert cassert_uint8_t_eq(const uint8_t a, const uint8_t b);
Cassert cassert_uint16_t_eq(const uint16_t a, const uint16_t b);
Cassert cassert_uint32_t_eq(const uint32_t a, const uint32_t b);
Cassert cassert_uint64_t_eq(const uint64_t a, const uint64_t b);
Cassert cassert_float_t_eq(const float_t a, const float_t b);
Cassert cassert_double_t_eq(const double_t a, const double_t b);

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
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_short_eq(const short a, const short b) {
  Cassert cassert = {0};
  cassert.assert_type = SHORT_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_int_eq(const int a, const int b) {
  Cassert cassert = {0};
  cassert.assert_type = INT_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_long_eq(const long a, const long b) {
  Cassert cassert = {0};
  cassert.assert_type = LONG_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_long_long_eq(const long long a, const long long b) {
  Cassert cassert = {0};
  cassert.assert_type = LONG_LONG_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_ushort_eq(const unsigned short a, const unsigned short b) {
  Cassert cassert = {0};
  cassert.assert_type = USHORT_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_uint_eq(const unsigned int a, const unsigned int b) {
  Cassert cassert = {0};
  cassert.assert_type = UINT_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_ulong_eq(const unsigned long a, const unsigned long b) {
  Cassert cassert = {0};
  cassert.assert_type = ULONG_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_ulong_long_eq(const unsigned long long a,
                              const unsigned long long b) {
  Cassert cassert = {0};
  cassert.assert_type = ULONG_LONG_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_size_t_eq(const size_t a, const size_t b) {
  Cassert cassert = {0};
  cassert.assert_type = SIZE_T_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}
Cassert cassert_int8_t_eq(const int8_t a, const int8_t b) {
  Cassert cassert = {0};
  cassert.assert_type = INT8_T_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}
Cassert cassert_int16_t_eq(const int16_t a, const int16_t b) {
  Cassert cassert = {0};
  cassert.assert_type = INT16_T_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}
Cassert cassert_int32_t_eq(const int32_t a, const int32_t b) {
  Cassert cassert = {0};
  cassert.assert_type = INT32_T_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}
Cassert cassert_int64_t_eq(const int64_t a, const int64_t b) {
  Cassert cassert = {0};
  cassert.assert_type = INT64_T_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}
Cassert cassert_uint8_t_eq(const uint8_t a, const uint8_t b) {
  Cassert cassert = {0};
  cassert.assert_type = UINT8_T_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}
Cassert cassert_uint16_t_eq(const uint16_t a, const uint16_t b) {
  Cassert cassert = {0};
  cassert.assert_type = UINT16_T_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}
Cassert cassert_uint32_t_eq(const uint32_t a, const uint32_t b) {
  Cassert cassert = {0};
  cassert.assert_type = UINT32_T_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}
Cassert cassert_uint64_t_eq(const uint64_t a, const uint64_t b) {
  Cassert cassert = {0};
  cassert.assert_type = UINT64_T_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}
Cassert cassert_float_t_eq(const float_t a, const float_t b) {
  Cassert cassert = {0};
  cassert.assert_type = FLOAT_T_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}
Cassert cassert_double_t_eq(const double_t a, const double_t b) {
  Cassert cassert = {0};
  cassert.assert_type = DOUBLE_T_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (!cassert.result) {
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
