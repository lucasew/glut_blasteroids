#include "error_reporter.h"
#include <stdio.h>

void report_error(const char *message) {
    if (message) {
        fprintf(stderr, "Error: %s\n", message);
    }
}