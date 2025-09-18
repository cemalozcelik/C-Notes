#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#define DEBUG_MODE 1
#define PLATFORM_WINDOWS 1
#define FEATURE_ADVANCED_MATH 1

#define SQUARE(x) ((x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define IS_EVEN(n) ((n) % 2 == 0)
#define SWAP(a, b) do { int temp = (a); (a) = (b); (b) = temp; } while(0)

#ifdef PLATFORM_LINUX
    #define CLEAR_SCREEN() system("clear")
#elif defined(PLATFORM_WINDOWS)
    #define CLEAR_SCREEN() system("cls")
#else
    #define CLEAR_SCREEN() printf("\n--- SCREEN CLEAR ---\n")
#endif

#ifdef FEATURE_ADVANCED_MATH
    #define POWER(base, exp) ({ \
        int result = 1; \
        int _exp = (exp); \
        int _base = (base); \
        for (int i = 0; i < _exp; i++) \
            result *= _base; \
        result; \
    })
    
    #define FACTORIAL(n) ({ \
        int result = 1; \
        int _n = (n); \
        for (int i = 1; i <= _n; i++) \
            result *= i; \
        result; \
    })
#endif

#ifdef DEBUG_MODE
    #define DEBUG_PRINT(fmt, ...) printf("[DEBUG] " fmt, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...)
#endif

extern void increment(void);
extern void decrement(void);
extern int get_counter(void);
extern void reset_counter(void);

int main(void) {
    printf("=== Day 13: Static Functions and Macros Demo ===\n\n");
    
    printf("--- Counter Module Test ---\n");
    increment();
    increment();
    printf("Counter after 2 increments: %d\n", get_counter());
    decrement();
    printf("Counter after 1 decrement: %d\n", get_counter());
    reset_counter();
    printf("Counter after reset: %d\n", get_counter());
    printf("\n");
    
    printf("--- Basic Macro Tests ---\n");
    int x = 5, y = 10;
    printf("Initial values: x = %d, y = %d\n", x, y);
    printf("SQUARE(x+1) = %d\n", SQUARE(x+1));
    printf("100/SQUARE(x) = %d\n", 100/SQUARE(x));
    
    int a = 5, b = 10;
    printf("Before MAX(a++, b): a = %d, b = %d\n", a, b);
    int max_result = MAX(a++, b);
    printf("After MAX(a++, b): a = %d, b = %d, result = %d\n", a, b, max_result);
    printf("\n");
    
    printf("--- SWAP Test ---\n");
    printf("Before SWAP: x = %d, y = %d\n", x, y);
    SWAP(x, y);
    printf("After SWAP: x = %d, y = %d\n", x, y);
    printf("\n");
    
    printf("--- IS_EVEN Test ---\n");
    int numbers[] = {42, 33, 0, 1, 100};
    for (int i = 0; i < 5; i++) {
        printf("%d is %s\n", numbers[i], IS_EVEN(numbers[i]) ? "even" : "odd");
    }
    printf("\n");
    
    printf("--- Platform Demo ---\n");
    printf("Clearing screen in 2 seconds...\n");
    #ifdef _WIN32
        Sleep(2000);
    #else
        sleep(2);
    #endif
    CLEAR_SCREEN();
    printf("Screen cleared!\n\n");
    
    #ifdef FEATURE_ADVANCED_MATH
        printf("--- Advanced Math ---\n");
        int base = 2, exp = 8;
        printf("POWER(%d, %d) = %d\n", base, exp, POWER(base, exp));
        int n = 5;
        printf("FACTORIAL(%d) = %d\n", n, FACTORIAL(n));
        printf("\n");
    #endif
    
    printf("--- Debug Test ---\n");
    DEBUG_PRINT("Debug message: x=%d, y=%d\n", x, y);
    
    printf("\n=== All tests completed! ===\n");
    return 0;
}