#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt text using Caesar Cipher
void caesarEncrypt(char text[], int key) {
    int i;
    char ch;
    
    for(i = 0; text[i] != '\0'; i++) {
        ch = text[i];
        
        // Encrypt uppercase letters
        if(ch >= 'A' && ch <= 'Z') {
            ch = ch + key;
            
            if(ch > 'Z') {
                ch = ch - 'Z' + 'A' - 1;
            }
            else if(ch < 'A') {
                ch = ch + 'Z' - 'A' + 1;
            }
            
            text[i] = ch;
        }
        // Encrypt lowercase letters
        else if(ch >= 'a' && ch <= 'z') {
            ch = ch + key;
            
            if(ch > 'z') {
                ch = ch - 'z' + 'a' - 1;
            }
            else if(ch < 'a') {
                ch = ch + 'z' - 'a' + 1;
            }
            
            text[i] = ch;
        }
        // Leave non-alphabetic characters unchanged
    }
}

int main() {
    char text[500];
    int key;
    
    printf("=== Caesar Cipher Encryption ===\n\n");
    
    // Get the key from user
    printf("Enter the key (shift value): ");
    scanf("%d", &key);
    getchar(); // To consume the newline character
    
    // Normalize the key to be within 0-25
    key = key % 26;
    
    // Get the plain text from user
    printf("Enter the plain text: ");
    fgets(text, sizeof(text), stdin);
    
    // Remove trailing newline if present
    text[strcspn(text, "\n")] = '\0';
    
    printf("\nPlain Text: %s\n", text);
    
    // Encrypt the text
    caesarEncrypt(text, key);
    
    printf("Cipher Text: %s\n", text);
    printf("Key Used: %d\n", key);
    
    return 0;
}
