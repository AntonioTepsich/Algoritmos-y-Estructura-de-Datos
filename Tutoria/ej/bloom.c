#include "testing.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define N_HASH 5
#define INIT 50



typedef struct item{
  size_t *hash;
} item_t;

typedef struct bloom {
  bool *off;
  uint8_t size;
} bloom_t;

// Bernstein's
size_t hash_f(const char *key, size_t level) {
  size_t h = level;

  for (size_t i = 0; key[i] != 0; ++i)
    h = 33 * h + (size_t)key[i];

  return h;
}

bloom_t *create(uint8_t n) {
  bloom_t *bloom =(bloom_t*) malloc(sizeof(bloom_t));
  if (!bloom)
    return NULL;
  bloom->off = (bool*) malloc(sizeof(bool)*INIT);
  if (!bloom->off){
    free(bloom);
    return NULL;
  }
  for (uint64_t i = 0; i < INIT; i++){
    bloom->off[i] = false;
  }
  bloom->size = INIT;
  return bloom;
}

void add(bloom_t *bloom, const char *str) {
  size_t *hash= (size_t*) malloc(sizeof(size_t)*N_HASH);
  if (!hash){
    return;
  }
  for (uint64_t i = 0; i < N_HASH; i++){
    hash[i] = hash_f(str, i);
  }
  for (uint64_t i = 0; i < N_HASH; i++){
    bloom->off[hash[i]%bloom->size] = true;
  }
  free(hash);
}

bool contains(bloom_t *bloom, const char *str) {
  size_t *hash = (size_t*) malloc(sizeof(size_t)*N_HASH);
  if (!hash){
    return false;
  }
  for (uint64_t i = 0; i < N_HASH; i++){
    hash[i] = hash_f(str, i);
  }
  for (uint64_t i = 0; i < N_HASH; i++){
    if (bloom->off[hash[i]%bloom->size]==false){
      free(hash);
      return false;
    }
  }
  free(hash);
  return true;
}

void destroy(bloom_t *bloom) {
  free(bloom->off);
  free(bloom);
}

bool test_create_and_insert() {
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bloom_t *bloom = create(N_HASH);
  if (!bloom)
    return false;
  add(bloom, "key1");
  bool retval = test_assert("Bloom creado con exito", true);
  destroy(bloom);
  return retval;
}

bool test_insert_contains() {
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bloom_t *bloom = create(N_HASH);
  if (!bloom)
    return false;
  add(bloom, "key1");
  bool retval = test_assert("Bloom contiene key1", contains(bloom, "key1"));
  destroy(bloom);
  return retval;
}

bool test_not_contains() {
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bloom_t *bloom = create(N_HASH);
  if (!bloom)
    return false;
  bool retval = test_assert("Bloom no contiene key1", !contains(bloom, "key1"));
  destroy(bloom);
  return retval;
}

bool test_insert_not_contains() {
  printf("========== %s ==========\n", __PRETTY_FUNCTION__);
  bloom_t *bloom = create(N_HASH);
  if (!bloom)
    return false;
  
  // for(int i = 0; i < bloom->size; i++){
  //   printf("%d\n", bloom->off[i]);
  // }
  // printf("END\n");

  add(bloom, "key1");
  
  // for(int i = 0; i < bloom->size; i++){
  //   printf("%d\n", bloom->off[i]);
  // }
  bool retval = test_assert("Bloom no contiene key2", !contains(bloom, "key2"));
  destroy(bloom);
  return retval;
}

bool test_insert_lots(size_t n, size_t bogus, unsigned int seed) {
  printf("========== %s (n=%lu, seed=%u) ==========\n", __PRETTY_FUNCTION__, n,
         seed);

  bloom_t *bloom = create(N_HASH);
  if (!bloom)
    return false;

  srand(seed);
  for (size_t i = 0; i < n; i++) {
    int random_number = rand();
    int length = snprintf(NULL, 0, "%d", random_number);
    char *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", random_number);
    add(bloom, str);
    free(str);
  }

  size_t matches = 0;

  srand(seed);
  for (size_t i = 0; i < n; i++) {
    int random_number = rand();
    int length = snprintf(NULL, 0, "%d", random_number);
    char *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", random_number);
    // printf("inserting %s\n", str);
    matches += contains(bloom, str) ? 1 : 0;
    free(str);
  }

  bool matches_ok = test_assert("Matches are ok", matches == n);

  size_t bogus_matches = 0;

  srand(seed + 1);
  for (size_t i = 0; i < bogus; i++) {
    int random_number = rand();
    int length = snprintf(NULL, 0, "%d", random_number);
    char *str = malloc(length + 1);
    snprintf(str, length + 1, "%d", random_number);
    // printf("testing for %s is %d\n", str, contains(bloom, str));
    bogus_matches += contains(bloom, str) ? 1 : 0;
    free(str);
  }

  bool bogus_matches_ok =
      bogus
          ? test_assert("There should be some bogus matches", bogus_matches > 0)
          : true;

  if (bogus)
    printf("There were %lu bogus tests and got %lu matches\n", bogus,
           bogus_matches);

  destroy(bloom);
  return matches_ok && bogus_matches_ok;
}

int main(void) {
  srand(117);
  printf("is %lu\n", sizeof(uint64_t));
  int return_code = 0;
  return_code += !test_create_and_insert();
  return_code += !test_insert_contains();
  return_code += !test_not_contains();
  return_code += !test_insert_not_contains();
  return_code += !test_insert_lots(100, 0, 117);
  return_code += !test_insert_lots(100, 10000, 117);
  if (return_code == 0) {
    printf("Todo ok!\n");
  } else {
    printf("Error code is %d\n", return_code);
  }
  return return_code;
}
