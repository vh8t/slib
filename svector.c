#include <memory.h>
#include <stdlib.h>

#include "svector.h"

svector_t *svector_create(svector_type_t type, unsigned long initial_capacity) {
  svector_t *svector = (svector_t *)malloc(sizeof(svector_t));

  if (initial_capacity == 0)
    initial_capacity = 1;

  switch (type) {
  case Int: {
    svector->element_size = sizeof(int);
    break;
  }
  case Str: {
    svector->element_size = sizeof(char *);
    break;
  }
  case Bool: {
    svector->element_size = sizeof(bool);
    break;
  }
  case Float: {
    svector->element_size = sizeof(float);
    break;
  }
  default: {
    free(svector);
    return NULL;
  }
  }

  svector->capacity = initial_capacity;
  svector->size = 0;
  svector->type = type;

  svector->data = malloc(svector->element_size * svector->capacity);

  if (!svector->data) {
    free(svector);
    return NULL;
  }

  return svector;
}

void svector_free(svector_t *svector) {
  if (svector) {
    free(svector->data);
    free(svector);
  }
}

int svector_push(svector_t *svector, void *element) {
  if (svector->size >= svector->capacity) {
    unsigned long new_capacity = svector->capacity * 2;
    void *new_data =
        realloc(svector->data, new_capacity * svector->element_size);

    if (!new_data)
      return 0;

    svector->data = new_data;
    svector->capacity = new_capacity;
  }

  memcpy((char *)svector->data + (svector->size * svector->element_size),
         element, svector->element_size);
  svector->size++;

  return 1;
}

int svector_get(svector_t *svector, unsigned long index, void *out_element) {
  if (index >= svector->size)
    return 0;

  memcpy(out_element, (char *)svector->data + (index * svector->element_size),
         svector->element_size);
  return 1;
}

int svector_pop(svector_t *svector) {
  if (svector->size > 0) {
    svector->size--;
    return 1;
  }
  return 0;
}

int svector_size(svector_t *svector) { return svector->size; }

int svector_capacity(svector_t *svector) { return svector->capacity; }

int svector_insert(svector_t *svector, unsigned long index, void *element) {
  if (index > svector->size)
    return 0;

  if (svector->size >= svector->capacity) {
    unsigned long new_capacity = svector->capacity * 2;
    void *new_data =
        realloc(svector->data, new_capacity * svector->element_size);

    if (!new_data)
      return 0;

    svector->data = new_data;
    svector->capacity = new_capacity;
  }

  void *dest = (char *)svector->data + index * svector->element_size;

  memmove((char *)dest + svector->element_size, dest,
          (svector->size - index) * svector->element_size);
  memcpy(dest, element, svector->element_size);
  svector->size++;

  return 1;
}

int svector_set(svector_t *svector, unsigned long index, void *element) {
  if (index >= svector->size)
    return 0;

  void *dest = (char *)svector->data + index * svector->element_size;

  memcpy(dest, element, svector->element_size);

  return 1;
}

int svector_remove(svector_t *svector, unsigned long index) {
  if (index >= svector->size)
    return 0;

  char *data = (char *)svector->data;
  unsigned long element_size = svector->element_size;

  memmove(data + (index * element_size), data + ((index + 1) * element_size),
          (svector->size - index - 1) * element_size);
  svector->size--;

  return 1;
}

void svector_clear(svector_t *svector) { svector->size = 0; }

int svector_fit(svector_t *svector) {
  if (svector->size == 0) {
    free(svector->data);
    svector->data = NULL;
    svector->capacity = 0;
    return 1;
  }

  void *new_data =
      realloc(svector->data, svector->size * svector->element_size);

  if (!new_data)
    return 0;

  svector->data = new_data;
  svector->capacity = svector->size;

  return 1;
}
