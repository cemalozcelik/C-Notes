#include <stdio.h>
#include "math_utils.h"

// Prime number check
int is_prime(int number) {
    if (number <= 1) return 0;
    if (number == 2) return 1;
    if (number % 2 == 0) return 0;
    
    for (int i = 3; i * i <= number; i += 2) {
        if (number % i == 0) return 0;
    }
    return 1;
}

// Perfect number check (sum of divisors excluding itself equals the number)
int is_perfect(int number) {
    if (number <= 1) return 0;

    int sum = 1; // 1 is a divisor of every number
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            sum += i;
            if (i * i != number) { // If not a perfect square, add the counterpart divisor
                sum += number / i;
            }
        }
    }
    return sum == number;
}

// Armstrong number check (sum of digits raised to the power of the number of digits)
int is_armstrong(int number) {
    int original = number;
    int digits = 0;
    int sum = 0;
    int temp = number;

    // Find the number of digits
    while (temp != 0) {
        digits++;
        temp /= 10;
    }

    // Armstrong number check
    temp = number;
    while (temp != 0) {
        int digit = temp % 10;
        int power = 1;
        for (int i = 0; i < digits; i++) {
            power *= digit;
        }
        sum += power;
        temp /= 10;
    }
    
    return sum == original;
}

// Print prime numbers up to a specified limit
void print_primes(int limit) {
    printf("Prime numbers (1-%d): ", limit);
    for (int i = 2; i <= limit; i++) {
        if (is_prime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}
