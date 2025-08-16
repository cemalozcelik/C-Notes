#include <stdio.h>
#include "math_utils.h"

int main() {
    int number;

    printf("Enter a number: ");
    scanf("%d", &number);
    
    // Function calls
    if (is_prime(number)) {
        printf("%d is a prime number.\n", number);
    } else {
        printf("%d is not a prime number.\n", number);
    }
    
    if (is_perfect(number)) {
        printf("%d is a perfect number.\n", number);
    } else {
        printf("%d is not a perfect number.\n", number);
    }
    
    if (is_armstrong(number)) {
        printf("%d is an Armstrong number.\n", number);
    } else {
        printf("%d is not an Armstrong number.\n", number);
    }

    // Print the first 30 prime numbers
    print_primes(30);
    

    
    return 0;
    // to run this script gcc main.c math_utils.c -o main && ./main
}