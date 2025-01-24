#ifndef CASSERT_H_
#define CASSERT_H_

#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  UNKNOWN_EQ,
  ANY_EQ,
  STRING_EQ,
  STRING_NUMBER_EQ,
  CHAR_NUMBER_EQ,
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
  Assert_Type assert_type;
  bool failed;
  int result;
  const void *value1;
  const void *value2;
  size_t line;
  const char *file;
} Cassert;

typedef struct {
  Cassert *elements;
  size_t count;
  size_t capacity;
} Casserts;

/** @brief The initial capacity of the dynamic arrays. */
#define CASSERT_DAP_CAP 64

/**
 * @brief The macro pushes the new array element at the end of the dynamic
 * array.
 *
 * @param dynamic_array The given array by a pointer.
 * @param element The given new element by value of the same type the array
 * holds elements.
 */
#define cassert_dap(dynamic_array, element)                                    \
  do {                                                                         \
    if ((dynamic_array)->capacity <= (dynamic_array)->count) {                 \
      if ((dynamic_array)->capacity == 0)                                      \
        (dynamic_array)->capacity = CASSERT_DAP_CAP;                           \
      else                                                                     \
        (dynamic_array)->capacity = (dynamic_array)->capacity * 2;             \
                                                                               \
      (dynamic_array)->elements = realloc((dynamic_array)->elements,           \
                                          sizeof(*(dynamic_array)->elements) * \
                                              (dynamic_array)->capacity);      \
                                                                               \
      if ((dynamic_array)->elements == NULL) {                                 \
        fprintf(                                                               \
            stderr,                                                            \
            "The allocation for the dynamic array has failed in: %s: %d\n",    \
            __FILE__, __LINE__);                                               \
      }                                                                        \
    }                                                                          \
                                                                               \
    (dynamic_array)->elements[(dynamic_array)->count] = (element);             \
    (dynamic_array)->count = (dynamic_array)->count + 1;                       \
  } while (0)

/**
 * @brief The macro pushes the given amount of new elements to the end of the
 * dynamic array.
 *
 * @param dynamic_array The given array by a pointer.
 * @param new_element The given new elements by pointer of the same type the
 * array holds elements.
 * @param new_elements_count The amount of elements to add to the array.
 */
#define cassert_dapc(dynamic_array, new_elements, new_elements_count)          \
  do {                                                                         \
    if (new_elements != NULL) {                                                \
      if ((dynamic_array)->capacity <                                          \
          (dynamic_array)->count + new_elements_count) {                       \
        if ((dynamic_array)->capacity == 0) {                                  \
          (dynamic_array)->capacity = CASSERT_DAP_CAP;                         \
        }                                                                      \
        while ((dynamic_array)->capacity <                                     \
               (dynamic_array)->count + new_elements_count) {                  \
          (dynamic_array)->capacity = (dynamic_array)->capacity * 2;           \
        }                                                                      \
        (dynamic_array)->elements = realloc(                                   \
            (dynamic_array)->elements,                                         \
            sizeof(*(dynamic_array)->elements) * (dynamic_array)->capacity);   \
        if ((dynamic_array)->elements == NULL) {                               \
          fprintf(                                                             \
              stderr,                                                          \
              "The allocation for the dynamic array has failed in: %s: %d\n",  \
              __FILE__, __LINE__);                                             \
        }                                                                      \
      }                                                                        \
      memcpy((dynamic_array)->elements + (dynamic_array)->count, new_elements, \
             sizeof(*(dynamic_array)->elements) * new_elements_count);         \
      (dynamic_array)->count = (dynamic_array)->count + new_elements_count;    \
    }                                                                          \
  } while (0)

Cassert cassert_string_eq(const char *a, const char *b);
Cassert cassert_ptr_eq(const void *a, const void *b);
const char *cassert_str_assert_type(Assert_Type assert_type);

int cassert_print(Cassert cassert);
int cassert_print_failure_case(Cassert cassert);
int cassert_print_success_case(Cassert cassert);
int cassert_print_all_cases(Casserts *casserts);
int cassert_print_all_failure_cases(Casserts *casserts);
int cassert_print_all_success_cases(Casserts *casserts);

#define cassert_eq(cassert, a, compare, b)                                     \
  do {                                                                         \
    cassert.line = __LINE__ - 1; /* The offset this next line. */              \
    cassert.file = __FILE__;                                                   \
    cassert.assert_type = ANY_EQ;                                              \
    cassert.value1 = &a;                                                       \
    cassert.value2 = &b;                                                       \
    cassert.result = a compare b ? 1 : 0;                                      \
    if (!cassert.result) {                                                     \
      cassert.failed = true;                                                   \
    }                                                                          \
  } while (0)

Cassert cassert_string_number_eq(const char *string, const double_t number);
Cassert cassert_char_number_eq(const char c, const unsigned char number);

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

int cassert_min(int a, int b) { return a < b ? a : b; }

Cassert cassert_string_eq(const char *a, const char *b) {
  Cassert cassert = {0};
  cassert.assert_type = STRING_EQ;
  cassert.value1 = a;
  cassert.value2 = b;
  cassert.result = strncmp(a, b, cassert_min(strlen(a), strlen(b)));
  if (cassert.result != 0) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_string_number_eq(const char *string, const double_t number) {
  Cassert cassert = {0};
  cassert.assert_type = STRING_NUMBER_EQ;
  cassert.value1 = string;
  cassert.value2 = &number;
  char number_string[64] = {0};
  if (snprintf(number_string, sizeof(number_string), "%lf\n", number) < 0) {
    exit(EXIT_FAILURE);
  };
  cassert.result = strncmp(string, number_string,
                           cassert_min(strlen(string), strlen(number_string)));
  if (cassert.result != 0) {
    cassert.failed = true;
  }
  return cassert;
}

Cassert cassert_char_number_eq(const char c, const unsigned char number) {
  Cassert cassert = {0};
  cassert.assert_type = CHAR_NUMBER_EQ;
  cassert.value1 = &c;
  cassert.value2 = &number;
  cassert.result = c + 48 == number ? 1 : 0;
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
  static_assert(ASSERT_TYPE_COUNT == 66, "assert types count has changed");
  switch (assert_type) {
  case STRING_EQ:
    return "STRING_EQ";
  case STRING_NUMBER_EQ:
    return "STRING_NUMBER_EQ";
  case CHAR_NUMBER_EQ:
    return "CHAR_NUMBER_EQ";
  case PTR_EQ:
    return "PTR_EQ";
  case CHAR_EQ:
    return "CHAR_EQ";
  case UCHAR_EQ:
    return "UCHAR_EQ";
  case SHORT_EQ:
    return "SHORT_EQ";
  case INT_EQ:
    return "INT_EQ";
  case LONG_EQ:
    return "LONG_EQ";
  case LONG_LONG_EQ:
    return "LONG_LONG_EQ";
  case USHORT_EQ:
    return "USHORT_EQ";
  case UINT_EQ:
    return "UINT_EQ";
  case ULONG_EQ:
    return "ULONG_EQ";
  case ULONG_LONG_EQ:
    return "ULONG_LONG_EQ";
  case SSIZE_T_EQ:
    return "SSIZE_T_EQ";
  case SIZE_T_EQ:
    return "SIZE_T_EQ";
  case INT8_T_EQ:
    return "INT8_T_EQ";
  case INT16_T_EQ:
    return "INT16_T_EQ";
  case INT32_T_EQ:
    return "INT32_T_EQ";
  case INT64_T_EQ:
    return "INT64_T_EQ";
  case UINT8_T_EQ:
    return "UINT8_T_EQ";
  case UINT16_T_EQ:
    return "UINT16_T_EQ";
  case UINT32_T_EQ:
    return "UINT32_T_EQ";
  case UINT64_T_EQ:
    return "UINT64_T_EQ";
  case FLOAT_T_EQ:
    return "FLOAT_T_EQ";
  case DOUBLE_T_EQ:
    return "DOUBLE_T_EQ";
  case SIZE_T_MAX_EQ:
    return "SIZE_T_MAX_EQ";
  case SIZE_T_MIN_EQ:
    return "SIZE_T_MIN_EQ";
  case INT8_T_MAX_EQ:
    return "INT8_T_MAX_EQ";
  case INT16_T_MAX_EQ:
    return "INT16_T_MAX_EQ";
  case INT32_T_MAX_EQ:
    return "INT32_T_MAX_EQ";
  case INT64_T_MAX_EQ:
    return "INT64_T_MAX_EQ";
  case INT8_T_MIN_EQ:
    return "INT8_T_MIN_EQ";
  case INT16_T_MIN_EQ:
    return "INT16_T_MIN_EQ";
  case INT32_T_MIN_EQ:
    return "INT32_T_MIN_EQ";
  case INT64_T_MIN_EQ:
    return "INT64_T_MIN_EQ";
  case UINT8_T_MAX_EQ:
    return "UINT8_T_MAX_EQ";
  case UINT16_T_MAX_EQ:
    return "UINT16_T_MAX_EQ";
  case UINT32_T_MAX_EQ:
    return "UINT32_T_MAX_EQ";
  case UINT64_T_MAX_EQ:
    return "UINT64_T_MAX_EQ";
  case UINT8_T_MIN_EQ:
    return "UINT8_T_MIN_EQ";
  case UINT16_T_MIN_EQ:
    return "UINT16_T_MIN_EQ";
  case UINT32_T_MIN_EQ:
    return "UINT32_T_MIN_EQ";
  case UINT64_T_MIN_EQ:
    return "UINT64_T_MIN_EQ";
  case CHAR_MAX_EQ:
    return "CHAR_MAX_EQ";
  case UCHAR_MAX_EQ:
    return "UCHAR_MAX_EQ";
  case SHORT_MAX_EQ:
    return "SHORT_MAX_EQ";
  case USHORT_MAX_EQ:
    return "USHORT_MAX_EQ";
  case INT_MAX_EQ:
    return "INT_MAX_EQ";
  case UINT_MAX_EQ:
    return "UINT_MAX_EQ";
  case LONG_MAX_EQ:
    return "LONG_MAX_EQ";
  case ULONG_MAX_EQ:
    return "ULONG_MAX_EQ";
  case LONG_LONG_MAX_EQ:
    return "LONG_LONG_MAX_EQ";
  case ULONG_LONG_MAX_EQ:
    return "ULONG_LONG_MAX_EQ";
  case CHAR_MIN_EQ:
    return "CHAR_MIN_EQ";
  case UCHAR_MIN_EQ:
    return "UCHAR_MIN_EQ";
  case SHORT_MIN_EQ:
    return "SHORT_MIN_EQ";
  case USHORT_MIN_EQ:
    return "USHORT_MIN_EQ";
  case INT_MIN_EQ:
    return "INT_MIN_EQ";
  case UINT_MIN_EQ:
    return "UINT_MIN_EQ";
  case LONG_MIN_EQ:
    return "LONG_MIN_EQ";
  case ULONG_MIN_EQ:
    return "ULONG_MIN_EQ";
  case LONG_LONG_MIN_EQ:
    return "LONG_LONG_MIN_EQ";
  case ULONG_LONG_MIN_EQ:
    return "ULONG_LONG_MIN_EQ";

  case ASSERT_TYPE_COUNT:
  case UNKNOWN_EQ:
  default:
    return "";
  }
}

int cassert_print(Cassert cassert) {
  switch (cassert.assert_type) {
  case STRING_EQ:
    return fprintf(stderr, "%s:%s:%s\n", (char *)cassert.value1,
                   cassert_str_assert_type(cassert.assert_type),
                   (char *)cassert.value2);
  case STRING_NUMBER_EQ:
    return fprintf(stderr, "%s:%s:%lf\n", (char *)cassert.value1,
                   cassert_str_assert_type(cassert.assert_type),
                   *(double_t *)cassert.value2);
  case PTR_EQ:
    return fprintf(stderr, "%p:%s:%p\n", (uintptr_t *)cassert.value1,
                   cassert_str_assert_type(cassert.assert_type),
                   (uintptr_t *)cassert.value2);
  case UNKNOWN_EQ:
  default:
    return fprintf(stderr, "%s \n",
                   cassert_str_assert_type(cassert.assert_type));
  }
}

int cassert_print_failure_case(Cassert cassert) {
  if (cassert.failed) {
    return cassert_print(cassert);
  }
  return 0;
}

int cassert_print_success_case(Cassert cassert) {
  if (!cassert.failed) {
    return cassert_print(cassert);
  }
  return 0;
}

int cassert_print_all_cases(Casserts *casserts) {
  int result = 0;
  for (size_t c = 0; c < casserts->count; ++c) {
    if (cassert_print(casserts->elements[c]) < 0) {
      result = -1;
    }
  }
  return result;
}

int cassert_print_all_failure_cases(Casserts *casserts) {
  int result = 0;
  for (size_t c = 0; c < casserts->count; ++c) {
    if (cassert_print_failure_case(casserts->elements[c]) < 0) {
      result = -1;
    }
  }
  return result;
}

int cassert_print_all_success_cases(Casserts *casserts) {
  int result = 0;
  for (size_t c = 0; c < casserts->count; ++c) {
    if (cassert_print_success_case(casserts->elements[c]) < 0) {
      result = -1;
    }
  }
  return result;
}

#endif // CASSERT_IMPLEMENTATION
