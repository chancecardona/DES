#include <math.h>
#include <stdio.h>
#include <stdint.h>

int main(){
    // Get Key (file or string)
    
    // Get Plaintext
    
    // Call DES
    ciphertext = DES_encrypt(plaintext, key); 
    // Put Ciphertext
    printf("{}", ciphertext);
}

char* DES_encrypt(char* plaintext, char* key){
    // Plaintext is 64 bits. Do initial Permutation.
    // TODO fix indexing
    uint32_t L_0;
    uint32_t R_0;
    int i;
    for(i = 0; i < 32; i++){ 
        L_0[i] = plaintext[i];
        R_0[i] = plaintext[i+32];
    key = PC_1(key);
    k_0 = DES_key_transform(key);
    L_1 = R_0;
    R_1 = L_0 ^ DES_round_function(R_0, k_0);
    //TODO continue looping.
    for(i = 0; i < 16; i++){
        key = DES_key_transform(key, i);
        L_i = R;
        R = L_0 ^ DES_round_function(key, R);
    }
}

uint64_t* key_schedule(uint64_t key, int round){ 
    //key is 64bits with parity bits. left/right are 28.
    int i;
    uint32_t C, D;
    uint64_t key_round[16];
    // Permutation Choice 1
    // TODO: do this with delta options. See:
    // https://reflectionsonsecurity.wordpress.com/2014/05/11/efficient-bit-permutation-using-delta-swaps/
    for(i = 0; i < 56; i++){
        key[i] = key[PC_1_table[i]];
    }
    //for(i = 0; i < 28; i++){
    //    C[i] = key[i];
    //    D[i] = key[i+28];
    //}
    // 0xFFFFFFF is 28 1's
    C = (key >> 28) & 0xFFFFFFF;
    D = key & 0xFFFFFFF;
    
    // 16 Key rounds
    for(i = 0; i < 16; i++){
        if(i == 0 || i == 1 || i == 8 || i == 15){
            //Rotate 1 bit left
            C = (C << 1) & 0xFFFFFFF | (C >> 27) & 0xFFFFFFF;
            D = (D << 1) & 0xFFFFFFF | (D >> 27) & 0xFFFFFFF;
        } else {
            //Rotate 2 bit left
            C = (C << 2) & 0xFFFFFFF | (C >> 26) & 0xFFFFFFF;
            D = (D << 2) & 0xFFFFFFF | (D >> 26) & 0xFFFFFFF;
        }
        // Concatenate with bit ops
        uint64_t CD = (C << 28) | D;
        // Permuted Choice 2
        key_round[i] = 0
        for(int j = 0; j < 48; j++){
            //key_round[i][j] = CD[PC_2_table[j]];
            //PC_2_table[j] //gives an int to move the shit to.
            //TODO: do this with delta swaps
            sub_key[i] <<= 1;
            sub_key[i] |= (CD >> (56-PC2[j])) & LB64_MASK;
        }
    }
    return key_out;
};

uint8_t* f_function(uint8_t* R, uint8_t* key){
    s_input = f_expansion(R) ^ k;
    // S1 to S8
    for(int i = 0; i < 8; i++){
        // Have array of S functions. Pass ptr with size (6b) to each. 
        // Returns a ptr with size (4b).
        s_output[i*4] = f_s(i, s_input[i*6]);
    }
    // Permutation
    return f_permutation(s_output);
}
// 32b in, 48b out
uint8_t* f_expansion(uint8_t* x, uint8_t* e_table){
    uint8_t[48] y;
    for(int i = 0; i < 48; i++){
        y[i] = x[e_table[i] - 1];
    }
    return y;
}
// 32b in, 32b out
uint8_t* f_permutation(uint8_t* x, uint8_t* p_table){
    // TODO: just operate on x by reference?
    uint8_t[32] y;
    for(int i = 0; i < 32; i++){
        y[i] = x[p_table[i] - 1];
    }
    return y;
}
// x is 6 bits, y is 4 bits.
uint8_t* f_S(int s_index, uint8_t* x){
    // Use binary array to get indices
    int i;
    int col_index; 
    int row_index; 
    uint8_t y[4];
    for(i = 1; i <= 4; i++){
        col_index *= 2;
        col_index += x[i];
    }
    row_index = x[0]*2 + x[5];
    // TODO: do this a better way or move this.
    static const uint8_t** S_table = { S1_table, S2_table, S3_table, S4_table, S5_table, S6_table, S7_table, S8_table };
    y[0] = S_table[s_index][col_index + 16*row_index];
}

static uint8_t IP_table[64] = { 58, 50, 42, 34, 26, 18, 10,  2, 
                                60, 52, 44, 36, 28, 20, 12,  4, 
                                62, 54, 46, 38, 30, 22, 14,  6, 
                                64, 56, 48, 40, 32, 24, 16,  8, 
                                57, 49, 41, 33, 25, 17,  9,  1, 
                                59, 51, 43, 35, 27, 19, 11,  3, 
                                61, 53, 45, 37, 29, 21, 13,  5, 
                                63, 55, 47, 39, 31, 23, 15,  7 };
static uint8_t FP_table[64] = { 40,  8, 48, 16, 56, 24, 64, 32, 
                                39,  7, 47, 15, 55, 23, 63, 31, 
                                38,  6, 46, 14, 54, 22, 62, 30, 
                                37,  5, 45, 13, 53, 21, 61, 29, 
                                36,  4, 44, 12, 52, 20, 60, 28, 
                                35,  3, 43, 11, 51, 19, 59, 27, 
                                34,  2, 42, 10, 50, 18, 58, 26, 
                                33,  1, 41,  9, 49, 17, 57, 25 };

static uint8_t E_table[32] = { 32,  1,  2,  3,  4,  5,
                                4,  5,  6,  7,  8,  9,
                                8,  9, 10, 11, 12, 13,
                               12, 13, 14, 15, 16, 17,
                               16, 17, 18, 19, 20, 21,
                               20, 21, 22, 23, 24, 25,
                               24, 25, 26, 27, 28, 29,
                               28, 29, 30, 31, 32,  1 }

static uint8_t P_table[32] = { 16,  7, 20, 21, 29, 12, 28, 17, 
                                1, 15, 23, 26,  5, 18, 31, 10,
                                2,  8, 24, 14, 32, 27,  3,  9,
                               19, 13, 30,  6, 22, 11,  4, 25 };

static uint8_t S1_table[32] = { 14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
                                 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
                                 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
                                15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13 };
static uint8_t S2_table[32] = { 15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10, 
                                 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5, 
                                 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15, 
                                13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9 };
static uint8_t S3_table[32] = { 10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8, 
                                13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,  
                                13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
                                 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12 };
static uint8_t S4_table[32] = {  7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15, 
                                13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,  
                                10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,  
                                 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14 };
static uint8_t S5_table[32] = {  2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9, 
                                14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,  
                                 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14, 
                                11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3 };
static uint8_t S6_table[32] = { 12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11, 
                                10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,  
                                 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,  
                                 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13 };
static uint8_t S7_table[32] = {  4,  11, 2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,  
                                13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,  
                                 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,  
                                 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12 };
static uint8_t S8_table[32] = { 13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7, 
                                 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,  
                                 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8, 
                                 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11 };
static uint8_t PC_1_table[56] = { 57, 49, 41, 33, 25, 17, 9,  1, 
                                  58, 50, 42, 34, 26, 18, 10, 2, 
                                  59, 51, 43, 35, 27, 19, 11, 3, 
                                  60, 52, 44, 36, 63, 55, 47, 39,
                                  31, 23, 15, 7,  62, 54, 46, 38,
                                  30, 22, 14, 6,  61, 53, 45, 37,
                                  29, 21, 13, 5,  28, 20, 12, 4 };
static uint8_t PC_2_table[48] = { 14, 17, 11, 24, 1,  5,  3,  28,
                                  15, 6,  21, 10, 23, 19, 12, 4,
                                  26, 8,  16, 7,  27, 20, 13, 2,
                                  41, 52, 31, 37, 47, 55, 30, 40,
                                  51, 45, 33, 48, 44, 49, 39, 56,
                                  34, 53, 46, 42, 50, 36, 29, 32 };

