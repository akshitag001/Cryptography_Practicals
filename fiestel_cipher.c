#include <stdio.h>

#define ull unsigned long long
#define ul  unsigned long
#define PP  (((ull)1 << 32) - 1)


ul F(ul r, ul k)
{
    return (r ^ k);
}

int main()
{
    ull p, c;        // plaintext, ciphertext
    ul l0, r0;       // initial halves
    ul l1, r1;       // after one round
    ul k;            // key

    printf("Enter plaintext (hex, without 0x): ");
    scanf("%llx", &p);

    printf("Enter key (hex): ");
    scanf("%lx", &k);

    
    l0 = p >> 32;
   
    r0 = p & PP;
   

  
  
    l1 = r0;
    r1 = l0 ^ F(r0, k);
    printf("l1: 0x%llX\n", l1);
    printf("r1: 0x%llX\n", r1);

    c = 0;
    c = c|l1;
    c = (c << 32) | r1;

    printf("Ciphertext: 0x%llX\n", c);
    
    
    l1 = c >> 32;
    r1 = c & PP;

    
    r0 = l1;
    l0 = r1 ^ F(l1, k);
     printf("l0: 0x%llX\n", l0);
     printf("r0: 0x%llX\n", r0);

    
    p = 0;
    p = p|l0;
    p = (p << 32) | r0;

    printf("Recovered Plaintext: 0x%llX\n", p);

    return 0;
}
