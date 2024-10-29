#ifndef SSTRING_H
#define SSTRING_H

typedef struct {
  char *data;
  unsigned long length;
  unsigned long capacity;
} sstring_t;

sstring_t *sstring_create(const char *initial_value);
void sstring_free(sstring_t *str);
void sstring_append(sstring_t *str, const char *suffix);
void sstring_insert(sstring_t *str, unsigned long index, const char *substring);
void sstring_clear(sstring_t *str);
char sstring_get(const sstring_t *str, unsigned long index);
const char *sstring_cstr(const sstring_t *str);
int sstring_equals(const sstring_t *str1, const sstring_t *str2);
void sstring_to_upper(sstring_t *str);
void sstring_to_lower(sstring_t *str);
int sstring_is_empty(sstring_t *str);
unsigned long sstring_size(sstring_t *str);

#endif // SSTRING_H
