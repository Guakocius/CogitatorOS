#ifndef STATUS_H
#define STATUS_H

typedef struct {
    const char *desc;
    int (*check_fn)();
} Status;

extern Status statuses[];
extern const int status_count;

#endif // STATUS_H