#ifndef DISK_H
#define DISK_H

int disk_read_sector(int sector, char *buffer);
int disk_write_sector(int sector, char *buffer);

#endif // DISK_H