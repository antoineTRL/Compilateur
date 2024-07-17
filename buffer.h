#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>
#include <stdbool.h>

#define BUF_SIZE 1024

typedef struct {
  char content[BUF_SIZE];
  FILE *fd;
  size_t it;
  size_t end;
  size_t lock;
  bool islocked;
  size_t avail;
  size_t bytesread;
  size_t bytesreadsincelock;
  size_t currchar;
  bool eof;
} buffer_t;

void buf_init(buffer_t *buffer, FILE *fd);
bool buf_eof_strict(buffer_t *buffer);
bool buf_eof(buffer_t *buffer);
void buf_lock(buffer_t *buffer);
void buf_unlock(buffer_t *buffer);
char buf_getchar(buffer_t *buffer);
void buf_rollback(buffer_t *buffer, size_t n);
size_t buf_skipblank(buffer_t *buffer);
char buf_getchar_rollback(buffer_t *buffer);

#endif // BUFFER_H
