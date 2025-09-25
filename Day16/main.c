#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "cutility.h"

// Prime number finder in range
void prime_finder_demo() {
    int low, high;
    int prime_count = 0;
    
    printf("Enter range values (min, max): ");
    (void)scanf("%d%d", &low, &high);
    
    printf("Prime numbers between %d and %d:\n", low, high);
    
    for (int i = low; i <= high; ++i) {
        if (isprime(i)) {
            if (prime_count && prime_count % 15 == 0) {
                putline();
            }
            printf("%d ", i);
            ++prime_count;
            sleep_ms(50); // small delay for cool effect
        }
    }
    
    printf("\n%d prime numbers found\n", prime_count);
}

// Type conversion demonstrations
void type_conversion_demo() {
    printf("=== Type Conversion Examples ===\n");
    
    // Signed/unsigned comparison
    printf("\n1. Signed/Unsigned comparison:\n");
    int x = -1;
    unsigned int y = 2;
    printf("int x = -1, unsigned int y = 2\n");
    printf("x < y ? %s\n", (x < y) ? "true" : "false");
    printf("(x gets converted to huge unsigned value)\n");
    
    // Character overflow
    printf("\n2. Character overflow:\n");
    int i = 987;
    char c = (char)i; // explicit cast to show intent
    printf("int i = 987\n");
    printf("char c = (char)i;\n");
    printf("c value: %d (data loss occurred)\n", c);
    
    // Character comparison issue
    printf("\n3. Character comparison:\n");
    char ch = 178;
    printf("char ch = 178\n");
    printf("ch == 178 ? %s\n", (ch == 178) ? "true" : "false");
    printf("ch value: %d (became negative)\n", ch);
    printf("ch == (char)178 ? %s (correct way)\n", (ch == (char)178) ? "true" : "false");
    
    // Integer promotion
    printf("\n4. Integer promotion:\n");
    char c1 = 5, c2 = 10;
    printf("char c1 = 5, c2 = 10\n");
    printf("sizeof(c1 + c2) = %zu (promoted to int)\n", sizeof(c1 + c2));
    printf("sizeof(char) = %zu\n", sizeof(char));
    
    // Double vs integer division
    printf("\n5. Division types:\n");
    printf("10 / 3 = %d (integer division)\n", 10 / 3);
    printf("10 / 3.0 = %.2f (double division)\n", 10 / 3.0);
}

// Utility function demonstrations
void utility_demo() {
    printf("=== Utility Functions Demo ===\n");
    
    int number = 12345;
    printf("Number: %d\n", number);
    printf("Digit count: %d\n", ndigit(number));
    printf("Is prime? %s\n", isprime(number) ? "Yes" : "No");
    
    // Test leap year macro
    int year = 2024;
    printf("Year %d is leap? %s\n", year, isleap(year) ? "Yes" : "No");
    
    putline();
    printf("Testing negative number digit count:\n");
    printf("ndigit(-456) = %d\n", ndigit(-456));
}

// Overflow behavior demonstration
void overflow_demo() {
    printf("=== Overflow Behavior Demo ===\n");
    
    // Unsigned overflow (well-defined)
    printf("\n1. Unsigned overflow (wraps around):\n");
    unsigned int max_uint = 4294967295U; // UINT_MAX for 32-bit
    printf("max_uint = %u\n", max_uint);
    printf("max_uint + 1 = %u (wraps to 0)\n", max_uint + 1);
    printf("max_uint + 2 = %u\n", max_uint + 2);
    
    // Note about signed overflow
    printf("\n2. Signed integer overflow:\n");
    printf("Signed overflow is UNDEFINED BEHAVIOR!\n");
    printf("Never rely on it - results are unpredictable\n");
    
    // Safe arithmetic with promotion
    printf("\n3. Safe arithmetic:\n");
    int a = 1000;
    printf("int a = 1000\n");
    printf("a * 20L = %ld (promoted to long)\n", a * 20L);
}

int main() {
    printf("=== C Programming Day 16 Examples ===\n\n");
    
    int choice;
    
    do {
        printf("\nSelect demo:\n");
        printf("1. Prime number finder\n");
        printf("2. Type conversion examples\n"); 
        printf("3. Utility functions\n");
        printf("4. Overflow behavior\n");
        printf("0. Exit\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            clear_input_buffer();
            printf("Invalid input!\n");
            continue;
        }
        
        switch (choice) {
            case 1:
                prime_finder_demo();
                break;
            case 2:
                type_conversion_demo();
                break;
            case 3:
                utility_demo();
                break;
            case 4:
                overflow_demo();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
        
        if (choice != 0) {
            printf("\nPress Enter to continue...");
            clear_input_buffer();
            getchar();
        }
        
    } while (choice != 0);
    
    return 0;
}

// Compilation command:
// gcc -o main main.c cutility.c
