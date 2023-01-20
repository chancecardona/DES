#include <stdio.h>
#include <stdint.h>
#include "des.h"

int main(int argc, const char * argv[]){
    // Get Key (file or string) 
    // Get Plaintext
   
    //uint64_t plaintext =   0x9474B8E8C73BCA7D;
    uint64_t plaintext =   0x0000000000000000;
    uint64_t key = 0x0000000000000000;
    uint64_t ciphertext; 

    // Call DES_crypt for each 64 bit chunk
    ciphertext = DES_encrypt(plaintext, key); 
    // Print Ciphertext
    // Plain: 0x9474B8E8C73BCA7D Expect 0x6eb6aaea4261f4b8
    // Plain: 0x0000000000000000 Expect 0x8ca64de9c1b123a7
    printf("Ciphertext: %016llx\n.", ciphertext);
}

