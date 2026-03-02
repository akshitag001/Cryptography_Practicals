#include <stdio.h>
#include <string.h>

/* ================= PERMUTATION TABLES ================= */

int IP[64] = {
58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7
};

int FP[64] = {
40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,
38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29,
36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,
34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25
};

int E[48] = {
32,1,2,3,4,5,4,5,6,7,8,9,
8,9,10,11,12,13,12,13,14,15,16,17,
16,17,18,19,20,21,20,21,22,23,24,25,
24,25,26,27,28,29,28,29,30,31,32,1
};

#Rearrange output of S box 
int P[32] = {
16,7,20,21,29,12,28,17,
1,15,23,26,5,18,31,10,
2,8,24,14,32,27,3,9,
19,13,30,6,22,11,4,25
};

#takes 64 bit key convert inot 56 by droping 8 parity bit
int PC1[56] = {
57,49,41,33,25,17,9,1,58,50,42,34,26,18,
10,2,59,51,43,35,27,19,11,3,60,52,44,36,
63,55,47,39,31,23,15,7,62,54,46,38,30,22,
14,6,61,53,45,37,29,21,13,5
};

# takes 56 bits and use only 48 
int PC2[48] = {
14,17,11,24,1,5,3,28,15,6,21,10,
23,19,12,4,26,8,16,7,27,20,13,2,
41,52,31,37,47,55,30,40,51,45,33,48,
44,49,39,56,34,53,46,42,50,36,29,32
};

#Specifies how many bits to rotate each round
int SHIFTS[16] = {
1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};

/* ================= S-BOXES ================= */

#S-boxes Each:Input: 6 bits Output: 4 bits
 
int S[8][4][16] = {
{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
 {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
 {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
 {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},

{{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
 {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
 {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
 {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},

{{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
 {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
 {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
 {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},

{{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
 {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
 {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
 {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},

{{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
 {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
 {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
 {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},

{{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
 {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
 {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
 {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},

{{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
 {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
 {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
 {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},

{{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
 {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
 {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
 {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}
};

/* ================= HELPER FUNCTIONS ================= */
# it used for IP , FP , E , P  ,PC1, PC2 
void permute(int *in, int *out, int *table, int n) {
    for(int i=0;i<n;i++)
      out[i] = in[table[i]-1];
}

void xor(int *a, int *b, int n) {
    for(int i=0;i<n;i++) 
        a[i] ^= b[i];
}

void left_shift(int *key, int shifts) {
    while(shifts--) {
        int temp = key[0];
        for(int i=0;i<27;i++) key[i]=key[i+1];
        key[27]=temp;
    }
}

void feistel(int *R, int *K, int *out) {
    int exp[48], s_out[32];
    permute(R, exp, E, 48);
    xor(exp, K, 48);

    for(int i=0;i<8;i++) {
        int row = exp[i*6]*2 + exp[i*6+5];
        int col = exp[i*6+1]*8 + exp[i*6+2]*4 + exp[i*6+3]*2 + exp[i*6+4];
        int val = S[i][row][col];
        for(int j=0;j<4;j++) s_out[i*4+j] = (val>>(3-j))&1;
    }
    permute(s_out, out, P, 32);
}
void hex_to_bits(char *hex, int *bits, int size) {
    for(int i = 0; i < size/4; i++) {
        int val;
        if(hex[i] >= '0' && hex[i] <= '9') val = hex[i] - '0';
        else val = hex[i] - 'A' + 10;

        for(int j = 0; j < 4; j++)
            bits[i*4 + j] = (val >> (3 - j)) & 1;
    }
}

void bits_to_hex(int *bits, char *hex, int size) {
    for(int i = 0; i < size/4; i++) {
        int val = 0;
        for(int j = 0; j < 4; j++)
            val = (val << 1) | bits[i*4 + j];

        hex[i] = (val < 10) ? (val + '0') : (val - 10 + 'A');
    }
    hex[size/4] = '\0';
}

/* ================= DES CORE ================= */

void generate_keys(int *key, int round_keys[16][48]) {
    int perm[56], C[28], D[28], CD[56];
    permute(key, perm, PC1, 56);
    memcpy(C, perm, 28*sizeof(int));
    memcpy(D, perm+28, 28*sizeof(int));

    for(int i=0;i<16;i++) {
        left_shift(C, SHIFTS[i]);
        left_shift(D, SHIFTS[i]);
        memcpy(CD, C, 28*sizeof(int));
        memcpy(CD+28, D, 28*sizeof(int));
        permute(CD, round_keys[i], PC2, 48);
    }
}

void des(int *input, int *output, int round_keys[16][48], int decrypt) {
    int ip[64], L[32], R[32], temp[32], f_out[32];
    permute(input, ip, IP, 64);
    memcpy(L, ip, 32*sizeof(int));
    memcpy(R, ip+32, 32*sizeof(int));

    for(int i=0;i<16;i++) {
        memcpy(temp, R, 32*sizeof(int));
        feistel(R, round_keys[decrypt?15-i:i], f_out);
        xor(L, f_out, 32);
        memcpy(R, L, 32*sizeof(int));
        memcpy(L, temp, 32*sizeof(int));
    }

    int preout[64];
    memcpy(preout, R, 32*sizeof(int));
    memcpy(preout+32, L, 32*sizeof(int));
    permute(preout, output, FP, 64);
}

/* ================= MAIN ================= */

int main() {
    char pt_hex[17], key_hex[17];
    int plaintext[64], key[64];
    int ciphertext[64], decrypted[64];
    char ct_hex[17], dec_hex[17];
    int round_keys[16][48];

    printf("Enter 16-hex-digit plaintext: ");
    scanf("%16s", pt_hex);

    printf("Enter 16-hex-digit key: ");
    scanf("%16s", key_hex);

    hex_to_bits(pt_hex, plaintext, 64);
    hex_to_bits(key_hex, key, 64);

    generate_keys(key, round_keys);

    des(plaintext, ciphertext, round_keys, 0);  // Encryption
    des(ciphertext, decrypted, round_keys, 1);  // Decryption

    bits_to_hex(ciphertext, ct_hex, 64);
    bits_to_hex(decrypted, dec_hex, 64);

    printf("\nCiphertext : %s", ct_hex);
    printf("\nDecrypted  : %s\n", dec_hex);

    return 0;

}
