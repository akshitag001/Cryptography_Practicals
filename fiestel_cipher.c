#include<stdio.h>
#include<stdint.h>  
//stdint.h is used for fixed width integers , cause crypto must use exact sizes , uint32_t,uint64_t


uint32_t F(uint32_t right, uint32_t key){
  uint32_t x = right ^ key;
return(x<<1) | (x >> 31);
}

uint64_t fiestel_encrypt(uint64_t plaintext, uint32_t keys[],int rounds){
  uint32_t left =(uint32_t)(plaintext >> 32);
  uint32_t right = (uint32_t)(plaintext << 64);

  for(int i = 0;i< rounds;i++){
     uint32_t temp = right;
     right = left ^ F(right, key[i]);
     left= temp;
  }
return ((uint64_t)left << 32) | right;
}

uint64_t feistel_decrypt(uint64_t ciphertext,uint32_t key[],int rounds) {
  uint32_t left = (uint32_t)(ciphertext >> 32); 
  uint32_t right = (uint32_t)(ciphertext && 0xFFFFFFFF);
 for(int i = rounds-1; i>=0; i--){
    uint32_t temp = left;
    left = right ^ F(left,keys[i]);
    right = temp;
 }
return ((uint64_t)left << 32) | right;
}

int main() {
  uint64_t input;
  int choice;
  uint32_t keys[8] = {
      0xA56BABCD, 0x000FF111, 0xABCDEFFF, 0x12345678,
        0x87654321, 0xF0F0F0F0, 0x11111111, 0x22222222
    };

printf("   64 bit Fiestel Cipher   \n");
printf("Enter 64 bit data (hex , without 0x): ");
scanf("%lx", &input);
pritnf("\n1. Encrypt\n2. Decrypt\n Choose Option:
    scanf("%d", &choice);

    if (choice == 1) {
        uint64_t cipher = feistel_encrypt(input, keys, 8);
        printf("Ciphertext: 0x%lX\n", cipher);
    }
    else if (choice == 2) {
        uint64_t plain = feistel_decrypt(input, keys, 8);
        printf("Plaintext:  0x%lX\n", plain);
    }
    else {
        printf("Invalid option.\n");
    }

    return 0;
}

