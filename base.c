#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//Task 2
char* map(char *array, int array_length, char (*f) (char)){
    if (!array || array_length < 0 || !f) return NULL;

    char* mapped_array = (char*)(malloc(array_length*sizeof(char)));
    
    /* TODO: Complete during task 2.a */

    if (!mapped_array) return NULL;

    for (int i = 0; i < array_length; i++) {
        mapped_array[i] = f(array[i]);
    }

    return mapped_array;
}

//T2b
/* Ignores c, reads and returns a character from stdin using fgetc. */
char my_get(char c){
    unsigned char uc = (unsigned char)c;
    char ch = fgetc(stdin);
    return ch;
}

/* If c is a number between 0x20 and 0x7E, cprt prints the character of ASCII value c, otherwise, the dot ('.') character. This is followed by a space character, and then the value of c in a hexadecimal. Finally, a new line character is printed. After printing, cprt returns the value of c unchanged. */
char cxprt(char c) {
    unsigned char uc = (unsigned char)c;
    if (uc >= 0x20 && uc <= 0x7E) printf("%c ", (char)uc);
    else                          printf(". ");
    printf("%02x\n", uc);
    return c;  /* unchanged */
}

/* Gets a char c and returns its encrypted form by adding 1 to its value. If c is not between 0x1F and 0x7E it is returned unchanged */
char encrypt(char c) {
    unsigned char uc = (unsigned char)c;
    if (uc > 0x1F && uc < 0x7F) return (char)(uc + 1);
    return c;

}
/* Gets a char c and returns its decrypted form by reducing 1 from its value. If c is not between 0x21 and 0x7F it is returned unchanged */
char decrypt(char c) {
    unsigned char uc = (unsigned char)c;
    if (uc > 0x20 && uc < 0x80) return (char)(uc - 1);
    return c;
}

/* dprt prints the value of c in a decimal representation followed by a new line, and returns c unchanged. */
char dprt(char c) {
    printf("%u\n", (unsigned)(unsigned char)c);
    return c;
}

int main(int argc, char **argv){
    //Task 2

    // /* TODO: Test your code */
    (void)argc; (void)argv;

    // char arr1[] = {'H','E','Y','!'};
    // int len = (int)(sizeof(arr1)/sizeof(arr1[0]));

    // char* arr2 = map(arr1, len, dprt);   /* prints decimal values */
    // printf("%.*s\n", len, arr1);

    // free(arr2);

    int base_len = 5;
    char arr3[5];                                /* initial buffer (unused values) */
    char *arr4 = map(arr3, base_len, my_get);    /* read 5 bytes from stdin */
    char *arr5 = map(arr4, base_len, dprt);      /* print decimals */
    char *arr6 = map(arr5, base_len, cxprt);     /* print printable-or-dot + hex */

    free(arr4);
    free(arr5);
    free(arr6);

    return 0;
}
