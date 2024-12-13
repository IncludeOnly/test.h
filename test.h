/**
 * test.h
 *
 * A tiny data-driven testing framework
 *
 * Written by KDesp73
 */

#ifndef TEST_H
#define TEST_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#ifndef TESTAPI
    #define TESTAPI static
#endif // TESTAPI

TESTAPI int test(int first, ...);
TESTAPI void load_test(const char* name);

#undef ANSI_RED
#define ANSI_RED "\e[0;31m"
#undef ANSI_RESET
#define ANSI_RESET "\e[0;39m"
#undef ANSI_GREEN
#define ANSI_GREEN "\e[0;32m"

#define FAIL(fen, fmt, ...) \
    fprintf(stderr, ANSI_RED "FAILED: (" #fen ")" fmt ANSI_RESET "\n", ##__VA_ARGS__)
#define SUCC(fmt, ...) \
    printf(ANSI_GREEN "SUCCESS: " fmt ANSI_RESET "\n", ##__VA_ARGS__)

#define START_TESTS \
        return !test(

#define END -1
#define END_TESTS \
        ,END \
    );

#define LOAD_TEST(test) \
    load_test(test)

#define RUN_TEST(test) \
    TEST_##test

#ifdef TEST_IMPLEMENTATION
#define STRAPPEND(buffer, fmt, ...) \
    snprintf(buffer + strlen(buffer), sizeof(buffer), fmt "\n", ##__VA_ARGS__)

TESTAPI void load_test(const char* name)
{
    char input_path[128];
    snprintf(input_path, sizeof(input_path), "test/%s.ct", name);
    FILE* input_file = fopen(input_path, "r");
    if (input_file == NULL) {
        perror("Failed to open input file");
        return;
    }

    char output_path[128];
    snprintf(output_path, sizeof(output_path), "test/%s.h", name);
    FILE* output_file = fopen(output_path, "w");
    if (output_file == NULL) {
        perror("Failed to open output file");
        fclose(input_file);
        return;
    }

    char line[256];
    int line_count = 0;

    while (fgets(line, sizeof(line), input_file)) {
        line_count++;
    }
    rewind(input_file);

    fprintf(output_file, "#ifndef %s_h\n", name);
    fprintf(output_file, "#define %s_h\n", name);
    // fprintf(output_file, "#include \"tests.h\"\n");
    fprintf(output_file, "\n#define TEST_%s \\\n", name);

    int current_line = 0;
    while (fgets(line, sizeof(line), input_file)) {
        line[strlen(line) - 1] = '\0'; // Remove newline character
        if (current_line < line_count - 1) {
            fprintf(output_file, "\t%s(%s), \\\n", name, line);
        } else {
            fprintf(output_file, "\t%s(%s)\n", name, line);
        }
        current_line++;
    }

    fprintf(output_file, "\n#endif\n");

    // Close files
    fclose(input_file);
    fclose(output_file);
}


TESTAPI int test(int first, ...)
{
    size_t passed = 0, failed = 0;
    int result = 1;

    va_list args;
    va_start(args, first);

    if (first == 0) {
        failed++;
        result = 0;
    } else passed++;

    int current;
    while ((current = va_arg(args, int)) != END) {
        if (current == 0) {
            result = 0;
            failed++;
        } else passed++;
    }

    va_end(args);

    printf("\n%sPASSED: %zu/%zu%s\n", ANSI_GREEN, passed, passed + failed, ANSI_RESET);
    printf("%sFAILED: %zu/%zu%s\n", ANSI_RED, failed, passed + failed, ANSI_RESET);
    return result;
}
#endif // TEST_IMPLEMENTATION

#endif // TEST_H
