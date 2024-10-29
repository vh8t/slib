/* !!! This is just a demo file how both sstring and svector can be used !!! */

#define SVEC_HELPER

#include <stdio.h>

#include "sstring.h"
#include "svector.h"

// svector demo {{{
void svector_demo() {
  printf("Svector demo:\n");

  svector_t *int_vec = svector_create(Int, 5);
  int number;

  printf("Push 4 numbers, [10, 20, 30, 40]\n");
  push_int(int_vec, 10);
  push_int(int_vec, 20);
  push_int(int_vec, 30);
  push_int(int_vec, 40);

  printf("int_vec = [");
  loop(number, int_vec) {
    if (__i != 0)
      printf(", ");
    printf("%d", number);
  }
  printf("]\n\n");

  printf("Insert 15 on index 1\n");
  insert_int(int_vec, 1, 15);

  printf("int_vec = [");
  loop(number, int_vec) {
    if (__i != 0)
      printf(", ");
    printf("%d", number);
  }
  printf("]\n\n");

  printf("Remove index 2\n");
  svector_remove(int_vec, 2);

  printf("int_vec = [");
  loop(number, int_vec) {
    if (__i != 0)
      printf(", ");
    printf("%d", number);
  }
  printf("]\n\n");

  svector_free(int_vec);
}
// svector demo }}}

// sstring demo {{{
void sstring_demo() {
  printf("Sstring demo:\n");

  sstring_t *string = sstring_create("Hello");
  printf("string = \"%s\"\n\n", sstring_cstr(string));

  printf("Append `orld!`\n");
  sstring_append(string, "orld!");
  printf("string = \"%s\"\n\n", sstring_cstr(string));

  printf("Insert `, W` at index 5\n");
  sstring_insert(string, 5, ", W");
  printf("string = \"%s\"\n\n", sstring_cstr(string));

  printf("Convert to upper cased\n");
  sstring_to_upper(string);
  printf("string = \"%s\"\n\n", sstring_cstr(string));

  printf("Clear the string\n");
  sstring_clear(string);
  printf("string = \"%s\"\n\n", sstring_cstr(string));

  sstring_free(string);
}
// sstring demo }}}

int main() {
  svector_demo();
  printf("\n\n");
  sstring_demo();

  return 0;
}
