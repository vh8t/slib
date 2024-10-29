#ifndef SVECTOR_H
#define SVECTOR_H

#include <stdbool.h>

#ifdef SVEC_HELPER

#define push_int(svector, element) (svector_push(svector, &(int){element}))
#define push_str(svector, element) (svector_push(svector, &(char *){element}))
#define push_bool(svector, element) (svector_push(svector, &(bool){element}))
#define push_float(svector, element) (svector_push(svector, &(float){element}))
#define push_var(svector, element) (svector_push(svector, &element))

#define insert_int(svector, index, element)                                    \
  (svector_insert(svector, index, &(int){element}))
#define insert_str(svector, index, element)                                    \
  (svector_insert(svector, index, &(char *){element}))
#define insert_bool(svector, index, element)                                   \
  (svector_insert(svector, index, &(bool){element}))
#define insert_float(svector, index, element)                                  \
  (svector_insert(svector, index, &(float){element}))
#define insert_var(svector, index, element)                                    \
  (svector_insert(svector, index, &element))

#define set_int(svector, index, element)                                       \
  (svector_set(svector, index, &(int){element}))
#define set_str(svector, index, element)                                       \
  (svector_set(svector, index, &(char *){element}))
#define set_bool(svector, index, element)                                      \
  (svector_set(svector, index, &(bool){element}))
#define set_float(svector, index, element)                                     \
  (svector_set(svector, index, &(float){element}))
#define set_var(svector, index, element) (svector_set(svector, index, &element))

#define loop(item, vec)                                                        \
  for (int __i = 0, __res = svector_get(vec, __i, &item); __res;               \
       __res = svector_get(vec, ++__i, &item))

#endif // SVEC_HELPER

typedef enum {
  Int,
  Str,
  Bool,
  Float,
  Ref,
} svector_type_t;

typedef struct {
  void *data;
  unsigned long size;
  unsigned long capacity;
  unsigned long element_size;
  svector_type_t type;
} svector_t;

svector_t *svector_create(svector_type_t type, unsigned long initial_capacity);
void svector_free(svector_t *svector);

int svector_push(svector_t *svector, void *element);

int svector_get(svector_t *svector, unsigned long index, void *out_element);
int svector_pop(svector_t *svector);
int svector_insert(svector_t *svector, unsigned long index, void *element);
int svector_set(svector_t *svector, unsigned long index, void *element);
int svector_remove(svector_t *svector, unsigned long index);
void svector_clear(svector_t *svector);
int svector_fit(svector_t *svector);

int svector_size(svector_t *svector);
int svector_capacity(svector_t *svector);

#endif // SVECTOR_H
