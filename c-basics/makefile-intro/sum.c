#include <stdio.h>

#if !defined(BIRNE_X) && !defined(LOCKED_BSE) && !defined(DOORS_10)
    #define LOCKED_BSE
#endif

#ifdef BIRNE_X
    typedef long my_int;
    #define FORMAT_STR "%ld"
    #define OS_NAME "Birne X"
    #define MAIN_TYPE int
    #define ARGC_TYPE int
    #define EXIT_CODE 0  // 0 means success

#elif defined LOCKED_BSE
    typedef int my_int;
    #define FORMAT_STR "%d"
    #define OS_NAME "Locked-BSE"
    #define MAIN_TYPE int
    #define ARGC_TYPE int
    #define EXIT_CODE 0

#elif defined DOORS_10
    typedef short my_int;
    #define FORMAT_STR "%hd"
    #define OS_NAME "Doors 10"
    // with -ffreestanding, main can be short
    #define MAIN_TYPE short
    // argc must be short here to avoid compiler warnings
    #define ARGC_TYPE short 
    #define EXIT_CODE 0

#else
    #error "Unknown OS"
#endif

/*
 * Convert a string to a number.
 * In freestanding mode, stdlib is not available.
 * ASCII math: char '0' equals 48.
 */
my_int string_to_num(char *str) {
    my_int result = 0;
    my_int i = 0; 
    
    // simple loop through the string
    while (str[i] != '\0') {
        // ASCII math: '0' turns a digit into a number ('5' - '0' = 5)
        my_int digit = (my_int)(str[i] - '0');
        
        // old value times 10 plus new digit
        result = result * 10 + digit;
        i++;
    }
    return result;
}

/*
 * main function
 * In freestanding mode the type is flexible, so short is ok for Doors.
 */
MAIN_TYPE main(ARGC_TYPE argc, char *argv[]) {
    // check arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <n1> <n2> <n3>\n", argv[0]);
        return 1; // 1 means error
    }

    // conversion using the local function
    my_int a = string_to_num(argv[1]);
    my_int b = string_to_num(argv[2]);
    my_int c = string_to_num(argv[3]);

    my_int sum = a + b + c;

    printf("Betriebssystem: %s\n", OS_NAME);
    printf("Summe: " FORMAT_STR "\n", sum);

    return EXIT_CODE;
}
