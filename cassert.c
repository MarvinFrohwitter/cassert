#define PRINT_OPERATION_AND_DESCRIPTION
#define CASSERT_IMPLEMENTATION
#include "cassert.h"

Test test1() {
    Test test = cassert_init_test("Test1");

    const char *a = __FILE__;
    const char *c = a;
    cassert_ptr_eq(a, c);
    cassert_char_number_eq('S', 83);
    return test;
}

Test test2() {
    Test test = {0};
    test.name = "Test2";

    cassert_string_neq("h", "H");

    char *five = "5.0000001";
    cassert_string_int64_eq(five, 5.2);
    cassert_string_float_eq(five, 5.0000002);
    cassert_string_double_neq(five, 5.0000002);

    cassert_float_neq(2.3, 5.01);
    return test;
}

Test test3() {
    Test test = {0};
    test.name = "Test3";

    typedef struct {
        int number;
        double rational;
        double _rational;
    } A;
    A a = {
        .number = 9,
        .rational = 4.5,
        ._rational = 444.5,
    };
    typedef struct {
        int number;
        double rational;
    } B;
    B b = {
        .number = 90,
        .rational = 4.5,
    };

    cassert_eq(&a, &a);
    cassert_neq(&a, (A*)&b);

    cassert_struct_eq(a, a);
    cassert_struct_neq(a, b);

    return test;
}

int main() {
    cassert_tests {
        cassert_dap(&tests, test1());
        cassert_dap(&tests, test2());
        cassert_dap(&tests, test3());
    }

    // cassert_short_print_tests(&tests);
    cassert_print_tests(&tests);
    cassert_free_tests(&tests);
    return 0;
}
