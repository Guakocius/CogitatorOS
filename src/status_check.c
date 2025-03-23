#include "status_check.h"
#include <unistd.h>
#include <stdbool.h>

int check_hardware() {
    sleep(1);
    return 0;
}

int check_network() {
    sleep(1);
    return 0;
}

int check_diagnostic() {
    sleep(1);
    return 0;
}

int perform_checks(bool (*check_fn)()) {
    bool result = check_fn();
    return result ? 1 : 0;
}