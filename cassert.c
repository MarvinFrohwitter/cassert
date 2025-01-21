#ifndef CASSERT_H_
#define CASSERT_H_

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define SIZE_MIN 0
#define UINT8_MIN 0
#define UINT16_MIN 0
#define UINT32_MIN 0
#define UINT64_MIN 0

#define UCHAR_MIN 0
#define USHRT_MIN 0
#define UINT_MIN 0
#define ULONG_MIN 0
#define ULLONG_MIN 0

typedef enum {
  UNKNOWN,
  STRING_EQ,
  PTR_EQ,

  CHAR_EQ,
  UCHAR_EQ,

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

  SIZE_T_MAX_EQ,
  SIZE_T_MIN_EQ,

  INT8_T_MAX_EQ,
  INT16_T_MAX_EQ,
  INT32_T_MAX_EQ,
  INT64_T_MAX_EQ,

  INT8_T_MIN_EQ,
  INT16_T_MIN_EQ,
  INT32_T_MIN_EQ,
  INT64_T_MIN_EQ,

  UINT8_T_MAX_EQ,
  UINT16_T_MAX_EQ,
  UINT32_T_MAX_EQ,
  UINT64_T_MAX_EQ,

  UINT8_T_MIN_EQ,
  UINT16_T_MIN_EQ,
  UINT32_T_MIN_EQ,
  UINT64_T_MIN_EQ,

  CHAR_MAX_EQ,
  UCHAR_MAX_EQ,
  SHORT_MAX_EQ,
  USHORT_MAX_EQ,
  INT_MAX_EQ,
  UINT_MAX_EQ,
  LONG_MAX_EQ,
  ULONG_MAX_EQ,
  LONG_LONG_MAX_EQ,
  ULONG_LONG_MAX_EQ,

  CHAR_MIN_EQ,
  UCHAR_MIN_EQ,
  SHORT_MIN_EQ,
  USHORT_MIN_EQ,
  INT_MIN_EQ,
  UINT_MIN_EQ,
  LONG_MIN_EQ,
  ULONG_MIN_EQ,
  LONG_LONG_MIN_EQ,
  ULONG_LONG_MIN_EQ,

  ASSERT_TYPE_COUNT,
} Assert_Type;

typedef struct {
  bool failed;
  int result;
  const void *value1;
  const void *value2;
  Assert_Type assert_type;
} Cassert;

Cassert cassert_string_eq(const char *a, const char *b);
Cassert cassert_ptr_eq(const void *a, const void *b);
const char *cassert_str_assert_type(Assert_Type assert_type);
int cassert_print(Cassert cassert);
int cassert_print_failure_case(Cassert cassert);

#define cassert_eq(a, compare, b)                                              \
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


Cassert cassert_char_eq(const char a, const char b);
Cassert cassert_uchar_eq(const unsigned char a, const unsigned char b);

Cassert cassert_short_eq(const short a, const short b);
Cassert cassert_int_eq(const int a, const int b);
Cassert cassert_long_eq(const long a, const long b);
Cassert cassert_long_long_eq(const long long a, const long long b);
Cassert cassert_ushort_eq(const unsigned short a, const unsigned short b);
Cassert cassert_uint_eq(const unsigned int a, const unsigned int b);
Cassert cassert_ulong_eq(const unsigned long a, const unsigned long b);
Cassert cassert_ulong_long_eq(const unsigned long long a,
                              const unsigned long long b);

Cassert cassert_char_max_eq(const char a);
Cassert cassert_short_max_eq(const short a);
Cassert cassert_int_max_eq(const int a);
Cassert cassert_long_max_eq(const long a);
Cassert cassert_long_long_max_eq(const long long a);

Cassert cassert_uchar_max_eq(const unsigned char a);
Cassert cassert_ushort_max_eq(const unsigned short a);
Cassert cassert_unit_max_eq(const unsigned int a);
Cassert cassert_ulong_max_eq(const unsigned long a);
Cassert cassert_ulong_long_max_eq(const unsigned long long a);

Cassert cassert_size_t_max_eq(const size_t a);
Cassert cassert_size_t_min_eq(const size_t a);

Cassert cassert_int8_t_max_eq(const int8_t a);
Cassert cassert_int16_t_max_eq(const int16_t a);
Cassert cassert_int32_t_max_eq(const int32_t a);
Cassert cassert_int64_t_max_eq(const int64_t a);

Cassert cassert_uint8_t_max_eq(const uint8_t a);
Cassert cassert_uint16_t_max_eq(const uint16_t a);
Cassert cassert_uint32_t_max_eq(const uint32_t a);
Cassert cassert_uint64_t_max_eq(const uint64_t a);

Cassert cassert_int8_t_min_eq(const int8_t a);
Cassert cassert_int16_t_min_eq(const int16_t a);
Cassert cassert_int32_t_min_eq(const int32_t a);
Cassert cassert_int64_t_min_eq(const int64_t a);

Cassert cassert_uint8_t_min_eq(const uint8_t a);
Cassert cassert_uint16_t_min_eq(const uint16_t a);
Cassert cassert_uint32_t_min_eq(const uint32_t a);
Cassert cassert_uint64_t_min_eq(const uint64_t a);

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

Cassert cassert_string_eq(const char *a, const char *b) {
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

Cassert cassert_ptr_eq(const void *a, const void *b) {
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

Cassert cassert_size_t_max_eq(const size_t a) {
  Cassert cassert = {0};
  cassert.assert_type = SIZE_T_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == SIZE_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_size_t_min_eq(const size_t a) {
  Cassert cassert = {0};
  cassert.assert_type = SIZE_T_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == SIZE_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_int8_t_max_eq(const int8_t a) {
  Cassert cassert = {0};
  cassert.assert_type = INT8_T_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == INT8_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_int8_t_min_eq(const int8_t a) {
  Cassert cassert = {0};
  cassert.assert_type = INT8_T_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == INT8_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_uint8_t_max_eq(const uint8_t a) {
  Cassert cassert = {0};
  cassert.assert_type = UINT8_T_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == UINT8_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_uint8_t_min_eq(const uint8_t a) {
  Cassert cassert = {0};
  cassert.assert_type = UINT8_T_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == UINT8_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_int16_t_max_eq(const int16_t a) {
  Cassert cassert = {0};
  cassert.assert_type = INT16_T_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == INT16_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_int16_t_min_eq(const int16_t a) {
  Cassert cassert = {0};
  cassert.assert_type = INT16_T_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == INT16_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_uint16_t_max_eq(const uint16_t a) {
  Cassert cassert = {0};
  cassert.assert_type = UINT16_T_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == UINT16_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_uint16_t_min_eq(const uint16_t a) {
  Cassert cassert = {0};
  cassert.assert_type = UINT16_T_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == UINT16_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_int32_t_max_eq(const int32_t a) {
  Cassert cassert = {0};
  cassert.assert_type = INT32_T_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == INT32_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_int32_t_min_eq(const int32_t a) {
  Cassert cassert = {0};
  cassert.assert_type = INT32_T_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == INT32_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_uint32_t_max_eq(const uint32_t a) {
  Cassert cassert = {0};
  cassert.assert_type = UINT32_T_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == UINT32_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_uint32_t_min_eq(const uint32_t a) {
  Cassert cassert = {0};
  cassert.assert_type = UINT32_T_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == UINT32_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_int64_t_max_eq(const int64_t a) {
  Cassert cassert = {0};
  cassert.assert_type = INT64_T_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == INT64_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_int64_t_min_eq(const int64_t a) {
  Cassert cassert = {0};
  cassert.assert_type = INT64_T_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == INT64_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_uint64_t_max_eq(const uint64_t a) {
  Cassert cassert = {0};
  cassert.assert_type = UINT64_T_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == UINT64_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_uint64_t_min_eq(const uint64_t a) {
  Cassert cassert = {0};
  cassert.assert_type = UINT64_T_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == UINT64_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_char_max_eq(const char a) {
  Cassert cassert = {0};
  cassert.assert_type = CHAR_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == CHAR_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_uchar_max_eq(const unsigned char a) {
  Cassert cassert = {0};
  cassert.assert_type = UCHAR_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == UCHAR_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_short_max_eq(const short a) {
  Cassert cassert = {0};
  cassert.assert_type = SHORT_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == SHRT_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_ushort_max_eq(const unsigned short a) {
  Cassert cassert = {0};
  cassert.assert_type = USHORT_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == USHRT_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_int_max_eq(const int a) {
  Cassert cassert = {0};
  cassert.assert_type = INT_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == INT_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_unit_max_eq(const unsigned int a) {
  Cassert cassert = {0};
  cassert.assert_type = UINT_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == UINT_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_long_max_eq(const long a) {
  Cassert cassert = {0};
  cassert.assert_type = LONG_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == LONG_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_ulong_max_eq(const unsigned long a) {
  Cassert cassert = {0};
  cassert.assert_type = ULONG_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == ULONG_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_long_long_max_eq(const long long a) {
  Cassert cassert = {0};
  cassert.assert_type = LONG_LONG_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == LLONG_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_ulong_long_max_eq(const unsigned long long a) {
  Cassert cassert = {0};
  cassert.assert_type = ULONG_LONG_MAX_EQ;
  cassert.value1 = &a;
  cassert.result = a == ULLONG_MAX ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_char_min_eq(const char a) {
  Cassert cassert = {0};
  cassert.assert_type = CHAR_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == CHAR_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_uchar_min_eq(const unsigned char a) {
  Cassert cassert = {0};
  cassert.assert_type = UCHAR_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == UCHAR_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_short_min_eq(const short a) {
  Cassert cassert = {0};
  cassert.assert_type = SHORT_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == SHRT_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_ushort_min_eq(const unsigned short a) {
  Cassert cassert = {0};
  cassert.assert_type = USHORT_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == USHRT_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_int_min_eq(const int a) {
  Cassert cassert = {0};
  cassert.assert_type = INT_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == INT_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_unit_min_eq(const unsigned int a) {
  Cassert cassert = {0};
  cassert.assert_type = UINT_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == UINT_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_long_min_eq(const long a) {
  Cassert cassert = {0};
  cassert.assert_type = LONG_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == LONG_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_ulong_min_eq(const unsigned long a) {
  Cassert cassert = {0};
  cassert.assert_type = ULONG_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == ULONG_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_long_long_min_eq(const long long a) {
  Cassert cassert = {0};
  cassert.assert_type = LONG_LONG_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == LLONG_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_ulong_long_min_eq(const unsigned long long a) {
  Cassert cassert = {0};
  cassert.assert_type = ULONG_LONG_MIN_EQ;
  cassert.value1 = &a;
  cassert.result = a == ULLONG_MIN ? 1 : 0;
  if (!cassert.result) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_char_eq(const char a, const char b) {
  Cassert cassert = {0};
  cassert.assert_type = CHAR_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (cassert.result != 0) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_uchar_eq(const unsigned char a, const unsigned char b) {
  Cassert cassert = {0};
  cassert.assert_type = UCHAR_EQ;
  cassert.value1 = &a;
  cassert.value2 = &b;
  cassert.result = a == b ? 1 : 0;
  if (cassert.result != 0) {
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
  return cassert_ptr_eq(a, c);
}

Cassert test2(void) {
  const char *a = __FILE__;
  return cassert_string_eq(a, __FILE__);
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
