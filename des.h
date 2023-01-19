#include <math.h>
#include <stdio.h>
#include <stdint.h>

char* DES_encrypt(char* plaintext, char* key);

uint64_t* key_schedule(uint64_t key);

uint32_t f_function(uint32_t R, uint64_t sub_key);

// 32b in, 48b out
uint64_t f_expansion(uint32_t x);

// 32b in, 32b out
uint32_t f_permutation(uint32_t x);

// x is 6 bits, y is 4 bits.
uint8_t f_S(int s_index, uint8_t x);
