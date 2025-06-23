#ifndef UFSEXT_H
#define UFSEXT_H

#include <stddef.h>
#include <sys/types.h>

int insert(int fd, void *buf, size_t bytes, size_t offset);
int delete(int fd, size_t bytes, size_t offset);
int extract(int fd, void *buf, size_t bytes, size_t offset);

#endif
