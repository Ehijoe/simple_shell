#ifndef IO_H
#define IO_H

#define MIN_LINE_SIZE 16

int print(int fd, char *s);
int readline(char **buffer, unsigned int *n, int fd);

#endif
