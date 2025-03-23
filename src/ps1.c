#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ps1.h"

// Function to set the custom PS1 prompt
void set_ps1(const char *ps1) {
    setenv("PS1", ps1, 1);
}

char *read_ps1_from_config(const char *config_file) {
    FILE *file = fopen(config_file, "r"); // Open the file in read mode
    if (file == NULL) {
        perror("Error opening config file");
        return NULL;
    }

    static char ps1[256]; // Buffer to store the PS1 prompt
    if (fgets(ps1, sizeof(ps1), file) == NULL) {
        perror("Error reading PS1 from config file");
        fclose(file);
        return NULL;
    }

    ps1[strcspn(ps1, "\n")] = '\0'; // Remove the newline character from the end
    fclose(file);
    return ps1;
}