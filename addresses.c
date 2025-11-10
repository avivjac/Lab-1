#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int addr5; 
int addr6;

int foo()
{
    return -1;
}

void point_at(void *p);
void foo1();
char g = 'g';
void foo2();

int secondary(int x)
{
    int addr2;
    int addr3;
    char *yos = "ree";
    int *addr4 = (int *)(malloc(50));
	int iarray[3];
    float farray[3];
    double darray[3];
    char carray[3]; 
	int iarray2[] = {1,2,3};
    char carray2[] = {'a','b','c'};
    int* iarray2Ptr;
    char* carray2Ptr; 
    
	printf("- &addr2: %p\n", &addr2); //stack
    printf("- &addr3: %p\n", &addr3); //stack
    printf("- foo: %p\n", &foo); //code
    printf("- &addr5: %p\n", &addr5); //data segment
	printf("Print distances:\n");
    point_at(&addr5);

    printf("Print more addresses:\n");
    printf("- &addr6: %p\n", &addr6);
    printf("- yos: %p\n", yos);
    printf("- gg: %p\n", &g);
    printf("- addr4: %p\n", addr4);
    printf("- &addr4: %p\n", &addr4);

    printf("- &foo1: %p\n", &foo1);
    printf("- &foo1: %p\n", &foo2);
    
    printf("Print another distance:\n");
    printf("- &foo2 - &foo1: %ld\n", (long) (&foo2 - &foo1));

    printf("Arrays Mem Layout (T1b):\n");

    /* task 1 b here */
    int iarray3[2];
    float farray3[2];
    double darray3[2];
    char carray3[2];

    // Fill a bit so nothing is "unused"
    iarray[0] = 10; iarray[1] = 20;
    farray[0] = 1.5f; farray[1] = 2.5f;
    darray[0] = 3.5;  darray[1] = 4.5;
    carray[0] = 'x';  carray[1] = 'y';

    printf("  sizeof(int)=%zu sizeof(float)=%zu sizeof(double)=%zu sizeof(char)=%zu\n",
           sizeof(int), sizeof(float), sizeof(double), sizeof(char));

    // Print the POINTER VALUES (not the contents)
    printf("  iarray      = %p\n", (void*)iarray);
    printf("  iarray + 1  = %p  (adds sizeof(int))\n", (void*)(iarray + 1));

    printf("  farray      = %p\n", (void*)farray);
    printf("  farray + 1  = %p  (adds sizeof(float))\n", (void*)(farray + 1));

    printf("  darray      = %p\n", (void*)darray);
    printf("  darray + 1  = %p  (adds sizeof(double))\n", (void*)(darray + 1));

    printf("  carray      = %p\n", (void*)carray);
    printf("  carray + 1  = %p  (adds sizeof(char)==1)\n", (void*)(carray + 1));

    puts("  Observation: pointer + 1 advances by the ELEMENT size (sizeof(T)),");
    puts("               not by 1 byte (except for char). That's the array layout.");
    
    printf("Pointers and arrays (T1d): ");

    /* task 1 d here */
    int  *iarrayPtr = iarray;   // points to iarray[0]
    char *carrayPtr = carray;   // points to carray[0]

     // Print all values using the POINTERS (not the array names)
    printf("  iarray via iarrayPtr: ");
    for (int i = 0; i < 2; i++) {
        printf("%d ", *(iarrayPtr + i));
    }
    printf("\n");

    printf("  carray via carrayPtr: ");
    for (int i = 0; i < 2; i++) {
        printf("%c ", *(carrayPtr + i));
    }
    printf("\n");

    // Now use the second arrays you already defined (length 3):
    //   iarray2[] = {1,2,3};  carray2[] = {'a','b','c'};
    iarray2Ptr = iarray2;   // points to iarray2[0]
    carray2Ptr = carray2;   // points to carray2[0]

    printf("  iarray2 via iarray2Ptr: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", *(iarray2Ptr + i));
    }
    printf("\n");

    printf("  carray2 via carray2Ptr: ");
    for (int i = 0; i < 3; i++) {
        printf("%c ", *(carray2Ptr + i));
    }
    printf("\n");

    // Uninitialized pointer demo: DO NOT DEREFERENCE!
    int *p;  // intentionally uninitialized
    printf("  uninitialized pointer p (address value only): %p\n", (void*)p);
    // NOTE: p has an indeterminate garbage value; dereferencing would be UB/likely crash.
}

int main(int argc, char **argv)
{ 

    printf("Print function argument addresses:\n");

    printf("- &argc %p\n", &argc); //stack
    printf("- argv %p\n", argv); //stack
    printf("- &argv %p\n", &argv); //stack
	
	secondary(0);
    
    printf("Command line arg addresses (T1e):\n");
    /* task 1 e here */

    printf("argv (char**):        %p  (pointer to the argv array)\n", (void*)argv);
    printf("&argv (char***):      %p  (address of argv itself - on stack)\n", (void*)&argv);
    printf("&argc (int*):         %p  (address of argc - on stack)\n", (void*)&argc);

    for (int i = 0; i < argc; i++) {
        printf("&argv[%d] (slot):     %p  (stack slot holding a char*)\n",
               i, (void*)&argv[i]);
        printf("argv[%d] ->           %p  (pointer to C-string)\n",
               i, (void*)argv[i]);
        printf("argv[%d] contents:    \"%s\"\n", i, argv[i]);
    }

    // Show the terminating NULL and its slot
    printf("&argv[%d] (NULL slot): %p\n", argc, (void*)&argv[argc]);
    printf("argv[%d] value:        %p (must be NULL)\n", argc, (void*)argv[argc]);
    
    return 0;
}

void point_at(void *p)
{
    int local;
    static int addr0 = 2;
    static int addr1;

    long dist1 = (size_t)&addr6 - (size_t)p;
    long dist2 = (size_t)&local - (size_t)p;
    long dist3 = (size_t)&foo - (size_t)p;

    printf("- dist1: (size_t)&addr6 - (size_t)p: %ld\n", dist1);
    printf("- dist2: (size_t)&local - (size_t)p: %ld\n", dist2);
    printf("- dist3: (size_t)&foo - (size_t)p:  %ld\n", dist3);
    
    printf("Check long type mem size (T1a):\n");
    /* part of task 1 a here */
    printf("- sizeof(long)   = %zu bytes\n", sizeof(long));
    printf("- sizeof(void*)  = %zu bytes\n", sizeof(void*));
    if (sizeof(long) < sizeof(void*)) {
        puts("  → long is smaller than a pointer here; prefer ptrdiff_t/uintptr_t for address math.");
    } else {
        puts("  → On this 32-bit build (-m32), long is pointer-sized; OK for address differences.");
    }


    printf("- addr0: %p\n", &addr0);
    printf("- addr1: %p\n", &addr1);
}

void foo1()
{
    printf("foo1\n");
}

void foo2()
{
    printf("foo2\n");
}