#include "../kernel/include/disk.h"
#include <stdio.h>

#define SECTOR_SIZE 512

int disk_read_sector(int sector, char *buffer) {
    FILE *file = fopen("disk.img", "r");
    if (file == NULL) {
        printf("Error: Could not open disk.img\n");
        return -1;
    }

    fseek(file, sector * SECTOR_SIZE, SEEK_SET);
    fread(buffer, SECTOR_SIZE, 1, file);

    fclose(file);
    return 0;
}

int disk_write_sector(int sector, char *buffer) {
    FILE *file = fopen("disk.img", "r+");
    if (file == NULL) {
        printf("Error: Could not open disk.img\n");
        return -1;
    }

    fseek(file, sector * SECTOR_SIZE, SEEK_SET);
    fwrite(buffer, SECTOR_SIZE, 1, file);

    fclose(file);
    return 0;
}