#ifndef STATUS_CHECK_H
#define STATUS_CHECK_H

#include "../../../../src/include/os_stdio.h"

int check_hardware();
int check_network();
int check_diagnostic();
int perform_checks(bool (*check_fn)());

#endif // STATUS_CHECK_H