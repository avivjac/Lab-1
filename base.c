#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//errno for error handling
#include <errno.h>
 

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

//Task 3

struct fun_desc {
    char *name;
    char (*fun)(char);
};

/* Menu items.
   NOTE: last sentinel {NULL,NULL} lets us compute length without hard-coding. */
static struct fun_desc menu[] = {
    { "Get string (read a line)", my_get },
    { "Print decimal (dprt)",     dprt   },
    { "Print char+hex (cxprt)",   cxprt  },
    { "Encrypt (+1)",             encrypt},
    { "Decrypt (-1)",             decrypt},
    /* Bonus (0 pts): junk — intentionally invalid “function pointer”.
       Uncomment to observe crash/UB when selected.
       { "JUNK (invalid ptr) — expect crash", (char(*)(char))menu },
    */
    { NULL, NULL }
};

static size_t menu_length(void){
    size_t n = 0;
    while (menu[n].name != NULL) n++;
    return n;
}

static void print_menu(void){
    puts("Select operation from the following menu:");
    for (size_t i = 0; menu[i].name; i++)
        printf("%zu) %s\n", i, menu[i].name);
}

/* Safe number parser: returns -1 on error/out-of-range */
static long read_choice_or_eof(long max_index){
    char buf[128];
    fputs("Your choice: ", stdout);
    fflush(stdout);

    if (!fgets(buf, sizeof(buf), stdin)) {
        /* EOF on empty line => exit per spec */
        return -1;
    }
    /* trim leading spaces */
    char *p = buf;
    while (*p==' '||*p=='\t') p++;
    errno = 0;
    char *end = NULL;
    long val = strtol(p, &end, 10);
    if (p == end || errno != 0) return max_index + 1; /* invalid number */
    return val;
}

int main(int argc, char **argv){
    //Task 2

    // /* TODO: Test your code */
    // (void)argc; (void)argv;

    // /* Example from the spec */
    // char arr1[] = {'H','E','Y','!'};
    // int len = (int)(sizeof(arr1)/sizeof(arr1[0]));

    // char* arr2 = map(arr1, len, dprt);   /* prints decimal values */
    // /* If you want, show the original string too: */
    // /* printf("%.*s\n", len, arr1); */

    // free(arr2);

    //  int base_len = 5;
    // char arr3[5];                                /* initial buffer (unused values) */
    // char *arr4 = map(arr3, base_len, my_get);    /* read 5 bytes from stdin */
    // char *arr5 = map(arr4, base_len, dprt);      /* print decimals */
    // char *arr6 = map(arr5, base_len, cxprt);     /* print printable-or-dot + hex */

    // /* examples for encrypt/decrypt if you want to test:
    //    char *enc = map(arr2, base_len, encrypt);
    //    char *dec = map(enc,  base_len, decrypt);
    //    free(enc); free(dec);
    // */

    // free(arr4);
    // free(arr5);
    // free(arr6);

    //Task 3
    const int base_len = 5;

    /* T3b: carray — pointer to char array length 5, initialized to empty string */
    char *carray = (char*)calloc((size_t)base_len, 1); /* all zeros => empty string */
    if (!carray) {
        perror("calloc");
        return 1;
    }

    const size_t nmenu = menu_length(); /* pre-compute once (per spec) */

    for (;;) {
        print_menu();
        long choice = read_choice_or_eof((long)nmenu - 1);
        if (choice == -1) { /* EOF -> graceful exit */
            puts("\nEOF — exiting.");
            break;
        }

        if (choice < 0 || choice >= (long)nmenu) {
            puts("Not within bounds");
            free(carray);
            return 0; /* graceful exit per spec */
        }

        puts("Within bounds");

        /* Apply selected function to carray via map, then replace carray */
        char (*f)(char) = menu[choice].fun;

        char *mapped = map(carray, base_len, f);
        if (!mapped) {
            fprintf(stderr, "map() failed (out of memory?)\n");
            free(carray);
            return 1;
        }
        free(carray);
        carray = mapped;

        /* Optional: show current carray as a 5-char slice (may include NULs) */
        /* printf("carray now: '%.*s'\n", base_len, carray); */
        puts(""); /* spacing */
    }

    free(carray);
    return 0;
}
