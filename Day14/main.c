// main.c
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "utils.h"  // Test multiple inclusion guard

// Basic function-like macro with proper parentheses
#define MAX(a, b) ((a) < (b) ? (b) : (a))

// Stringification operator usage
#define DEBUG_PRINT(var) printf("DEBUG: %s = %d\n", #var, var)

// Token pasting operator usage  
#define DECLARE_VAR(type, name) type name = 0; type name##_backup = 0;

// Conditional compilation - debug levels
#define DEBUG_LEVEL 1

#if DEBUG_LEVEL > 0
    #define INFO_LOG(msg) printf("INFO: %s\n", msg)
#else
    #define INFO_LOG(msg)
#endif

#if DEBUG_LEVEL > 1
    #define DETAIL_LOG(msg) printf("DETAIL: %s\n", msg)
#else
    #define DETAIL_LOG(msg)
#endif

// Assertion macro using predefined constants
#define ASSERT(condition) \
    if (!(condition)) { \
        printf("ASSERTION FAILED: %s at %s:%d in %s\n", \
               #condition, __FILE__, __LINE__, __func__); \
        abort(); \
    }

// Predefined macros debug info
#define DEBUG_INFO() printf("=== DEBUG INFO ===\nFile: %s\nLine: %d\nFunction: %s\nDate: %s\nTime: %s\n", \
                            __FILE__, __LINE__, __func__, __DATE__, __TIME__)

// Generic swap with do-while trick for safety
#define SWAP(a, b) do { \
    int temp = a; \
    a = b; \
    b = temp; \
} while(0)

// Debug version of swap using both # and ## operators
#define SWAP_DEBUG(a, b) do { \
    printf("SWAP DEBUG: Before: %s=%d, %s=%d\n", #a, a, #b, b); \
    SWAP(a, b); \
    printf("SWAP DEBUG: After: %s=%d, %s=%d\n", #a, a, #b, b); \
} while(0)

void divide_numbers(int a, int b) {
    ASSERT(b != 0);
    printf("Result: %d\n", a / b);
}

void test_swaps() {
    DEBUG_INFO();
    
    int a = 42, b = 99;
    printf("Before swap: a=%d, b=%d\n", a, b);
    
    SWAP_DEBUG(a, b);
    
    printf("After swap: a=%d, b=%d\n", a, b);
    
    if (a > 50)
        SWAP(a, b);
    else
        printf("No second swap needed\n");
}

int main() {
    printf("Program started\n");
    printf("Header counter: %d\n", header_counter);
    
    // Test basic macros
    int x = 15, y = 23;
    printf("Max: %d\n", MAX(x, y));
    
    // Test debug printing
    DEBUG_PRINT(x);
    DEBUG_PRINT(y);
    DEBUG_PRINT(x + y);
    
    // Test variable declaration
    DECLARE_VAR(int, counter);
    counter = 42;
    counter_backup = counter;
    DEBUG_PRINT(counter);
    DEBUG_PRINT(counter_backup);
    
    // Test conditional compilation
    INFO_LOG("This is important info");
    DETAIL_LOG("This is detailed debug info");
    
    // Test circle area calculation
    printf("Circle area with radius 5: %f\n", CIRCLE_AREA(5));
    
    // Test assertion and division
    divide_numbers(10, 2);
    
    // Test swap functionality
    test_swaps();
    
    printf("Program ended\n");
    return 0;
}