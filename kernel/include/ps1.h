#ifndef PS1_H
#define PS1_H

// Function to set the custom PS1 prompt
void set_custom_ps1(const char *new_ps1);

// Function to read the PS1 setting from the system.conf file
char* read_ps1_from_config(const char *config_file);

#endif  // PS1_H
