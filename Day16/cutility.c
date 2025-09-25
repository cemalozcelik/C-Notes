#include "cutility.h"
#include <stdio.h>
#include <Windows.h>

// Count number of digits in an integer
int ndigit(int val) {
    int digit_count = 0;
    
    if (val == 0) {
        return 1;
    }
    
    // Handle negative numbers
    if (val < 0) {
        val = -val;
    }
    
    while (val) {
        ++digit_count;
        val /= 10;
    }
    
    return digit_count;
}

// Check if a number is prime
int isprime(int val) {
    if (val == 0 || val == 1) {
        return 0;
    }
    
    if (val % 2 == 0) {
        return val == 2;
    }
    
    if (val % 3 == 0) {
        return val == 3;
    }
    
    if (val % 5 == 0) {
        return val == 5;
    }
    
    // Check odd divisors starting from 7
    for (int i = 7; i * i <= val; i += 2) {
        if (val % i == 0) {
            return 0;
        }
    }
    
    return 1;
}

// Sleep for specified milliseconds
void sleep_ms(int milliseconds) {
    Sleep(milliseconds);
}

// Print a separator line
void putline(void) {
    printf("\n-----------------------------------------\n");
}

// Clear input buffer to handle leftover characters
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        ; // discard characters
    }
}