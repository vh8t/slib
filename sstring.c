#include "sstring.h"
#include <stdlib.h>
#include <string.h>

sstring_t *sstring_create(const char *initial_value) {
  sstring_t *str = malloc(sizeof(sstring_t));
  if (!str)
    return NULL;

  str->length = initial_value ? strlen(initial_value) : 0;
  str->capacity = str->length + 1;
  str->data = malloc(str->capacity);

  if (!str->data) {
    free(str);
    return NULL;
  }

  if (initial_value)
    strcpy(str->data, initial_value);
  else
    str->data[0] = '\0';

  return str;
}

void sstring_free(sstring_t *str) {
  if (str) {
    free(str->data);
    free(str);
  }
}

void sstring_append(sstring_t *str, const char *suffix) {
  if (!str || !suffix)
    return;

  unsigned long suffix_len = strlen(suffix);
  str->capacity = str->length + suffix_len;
  str->data = realloc(str->data, str->capacity);

  strcpy(str->data + str->length, suffix);
  str->length += suffix_len;
}

void sstring_insert(sstring_t *str, unsigned long index,
                    const char *substring) {
  if (!str || !substring)
    return;

  unsigned long sub_len = strlen(substring);
  str->capacity = str->length + sub_len;
  str->data = realloc(str->data, str->capacity);

  memmove(str->data + index + sub_len, str->data + index,
          str->length - index + 1);
  memcpy(str->data + index, substring, sub_len);
  str->length += sub_len;
}

void sstring_clear(sstring_t *str) {
  if (str) {
    str->length = 0;
    str->data[0] = '\0';
  }
}

char sstring_get(const sstring_t *str, unsigned long index) {
  if (index < str->length) {
    return str->data[index];
  }
  return '\0';
}

const char *sstring_cstr(const sstring_t *str) { return str->data; }

int sstring_equals(const sstring_t *str1, const sstring_t *str2) {
  if (str1->length != str2->length)
    return 0;

  if (strcmp(str1->data, str2->data) == 0)
    return 1;
  return 0;
}

void sstring_to_lower(sstring_t *str) {
  if (!str || str->length == 0)
    return;

  for (unsigned long i = 0; i < str->length; i++) {
    if ('A' <= str->data[i] && str->data[i] <= 'Z')
      str->data[i] += 32;
  }
}

void sstring_to_upper(sstring_t *str) {
  if (!str || str->length == 0)
    return;

  for (unsigned long i = 0; i < str->length; i++) {
    if ('a' <= str->data[i] && str->data[i] <= 'z')
      str->data[i] -= 32;
  }
}

int sstring_is_empty(sstring_t *str) { return !str || str->length == 0; }

unsigned long sstring_size(sstring_t *str) { return str->length; }
