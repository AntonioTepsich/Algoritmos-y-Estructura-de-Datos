#include "test_malloc.h"
#include "testing.h"
#include "operable_dict.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Acá implementa tus tests
bool crear(){
  bool tests_result = true;
  dictionary_t *dict = dictionary_create(NULL);
  tests_result &= test_assert("El tamaño es cero", dictionary_size(dict) == 0);
  int one = 1, two = 2;
  tests_result &=
      test_assert("Se puede insertar key1", dictionary_put(dict, "key1", &one));
  tests_result &= test_assert("El diccionario contiene key1",
                              dictionary_contains(dict, "key1"));
  tests_result &= test_assert("El diccionario no contiene key2",
                              !dictionary_contains(dict, "key2"));
  tests_result &= test_assert("El tamaño es uno", dictionary_size(dict) == 1);
  tests_result &=
      test_assert("Se puede insertar key2", dictionary_put(dict, "key2", &two));

  tests_result &= test_assert("El diccionario contiene key1",
                              dictionary_contains(dict, "key1"));
  tests_result &= test_assert("El diccionario contiene key2",
                              dictionary_contains(dict, "key2"));
  tests_result &= test_assert("El tamaño es dos", dictionary_size(dict) == 2);
  
  
  dictionary_destroy(dict);
  return tests_result;
}

int main_operable_dict(void) {
  srand(117);
  int return_code = 0;
  return_code += crear(); // Agrega tus propios tests acá
  exit(return_code);
}
