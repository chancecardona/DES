# Data Encryption Standard
This is my version of DES implemented from https://crypto-textbook.com/download/Understanding_Cryptography_Chptr_3---DES.pdf
This version should stress readability first and foremost, with optimizations
coming at a later time.

## Delta Swap
Delta swap is an efficient bit permutation method available here https://reflectionsonsecurity.wordpress.com/2014/05/11/efficient-bit-permutation-using-delta-swaps/ . 
This implementation used on the website ultimately shifts the bit according to the delta in the left direction, so I have listed the original and the corrected
version (using the delta defined to be positive in my code).
Masks used are explained here:
- Swap 1:  
  Original: 
  - 0x0055005500550055  
  - 00000000 10101010 00000000 10101010 00000000 10101010 00000000 10101010
  Used: 
  - 0xAA00AA00AA00AA00
  - 10101010 00000000 10101010 00000000 10101010 00000000 10101010 00000000
  selects every other bit skipping a row (it then swaps with a delta of 9, 
  which for an 8x8 matrix for IP is 1 row down +1 right.)
- Swap 2:  
  Original: 
  - 0x0000333300003333  
  - 00000000 00000000 00110011 00110011 00000000 00000000 00110011 00110011  
  Used:     
  - 0xCCCC0000CCCC0000
  - 11001100 11001100 00000000 00000000 11001100 11001100 00000000 00000000  
  selects alternate 4x4 groups of squares and swaps with the square in the
  quadrant with a delta of 18.
- Swap 3:
  Original: 
  - 0x000000000F0F0F0F
  - 00000000 00000000 00000000 00000000 00001111 00001111 00001111 00001111  
  Used: 
  - 0xF0F0F0F000000000
  - 11110000 11110000 11110000 11110000 00000000 00000000 00000000 00000000
  selects upper left quadrant (with delta 36 (1/2 + 1/8 of total length), 
  swaps it with the bottom right.
- Swap 4:
  Original: 
  - 0x00000000FF00FF00  
  - 00000000 00000000 00000000 00000000 11111111 00000000 11111111 00000000  
  Used: 
  - 0x00FF00FF00000000
  - 00000000 11111111 00000000 11111111 00000000 00000000 00000000 00000000
  selects 2nd and 5th rows, with delta 24 swaps them.
- Swap 5:
  Original:
  - 0x000000FF000000FF
  - 00000000 00000000 00000000 11111111 00000000 00000000 00000000 11111111
  Used:  
  - 0xFF000000FF000000
  - 11111111 00000000 00000000 00000000 11111111 00000000 00000000 00000000
  selects 1st and 5th rows, with delta 24 swaps them.  
This utilizes 30 bit operations total. Alternatives include bfly tables.

## Debugging
Useful for debugging: http://styere.xyz/JS-DES.html just edit form to not be readonly.

## TODO:
- Utilize structures of P, E, PC-1, and PC-2 tables for more efficient bit ops.
