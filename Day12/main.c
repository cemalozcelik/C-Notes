#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Recursive factorial function
int factorial(int x) {
    return x < 2 ? 1 : x * factorial(x - 1);
}

// Iterative power function (commented in original)
int power(int base, int exp) {
    int result = 1;
    while (exp--)
        result *= base;
    return result;
}

int main() {
    
    // Example 1: The "goes-to" operator
    printf("=== Goes-to operator demo ===\n");
    int n = 5;
    while (n --> 0) {  // n-- > 0
        printf("Countdown: %d\n", n + 1);
    }
    
    // Example 2: Power function demo
    printf("\n=== Power function demo ===\n");
    printf("Enter base and exponent: ");
    int a, b;
    (void)scanf("%d%d", &a, &b);  // void cast to suppress warning
    printf("Result: %d^%d = %d\n", a, b, power(a, b));
    
    // Example 3: Number statistics with break
    printf("\n=== Number statistics (press 'q' to quit) ===\n");
    int c;
    int ival;
    int cnt = 0;
    int sum = 0;
    int max, min;
    
    while (1) {
        printf("Continue (c) - Quit (q): ");
        while ((c = _getch()) != 'c' && c != 'q')
            ;  // wait for valid input
        
        printf("%c\n", c);
        
        if (c == 'q')
            break;
        
        // Generate random number instead of scanf for speed
        ival = (rand() % 2 ? 1 : -1) * (rand() % 1000);
        
        if (cnt == 0)
            max = min = ival;
        else if (ival > max)
            max = ival;
        else if (ival < min)
            min = ival;
        
        printf("Generated number: %d\n", ival);
        cnt++;
        sum += ival;
    }
    
    if (cnt != 0) {
        printf("\nStatistics:\n");
        printf("Total numbers: %d\n", cnt);
        printf("Average: %.2f\n", (double)sum / cnt);
        printf("Min: %d\n", min);
        printf("Max: %d\n", max);
    } else {
        printf("No numbers were processed.\n");
    }
    
    // Example 4: Do-while input validation
    printf("\n=== Input validation with do-while ===\n");
    int x;
    do {
        printf("Enter a number between 0 and 100: ");
        scanf("%d", &x);
        if (x < 0 || x > 100)
            printf("Invalid! Try again.\n");
    } while (x < 0 || x > 100);
    
    printf("You entered: %d\n", x);
    
    // Example 5: Factorial demonstration
    printf("\n=== Factorial calculations ===\n");
    for (int i = 0; i < 13; i++) {
        printf("factorial(%d) = %d\n", i, factorial(i));
    }
    
    // Example 6: Pi approximation using Leibniz formula
    printf("\n=== Pi approximation ===\n");
    int terms;
    double pi_sum = 0;
    
    printf("How many terms for pi calculation? ");
    scanf("%d", &terms);
    
    for (int i = 0; i < terms; i++) {
        if (i % 2 == 0)
            pi_sum += 1.0 / (2 * i + 1);    // positive terms
        else
            pi_sum -= 1.0 / (2 * i + 1);    // negative terms
    }
    
    printf("Pi approximation with %d terms: %.12f\n", terms, 4.0 * pi_sum);
    printf("Actual pi value: 3.141592653590\n");
    printf("Error: %.12f\n", 3.141592653590 - 4.0 * pi_sum);
    
    // Example 7: For loop variations
    printf("\n=== For loop variations ===\n");
    
    // Standard for loop
    printf("Standard for loop: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    // For loop with comma operator
    printf("For loop with multiple variables: ");
    for (int i = 0, j = 10; i < 5; i++, j--) {
        printf("(%d,%d) ", i, j);
    }
    printf("\n");
    
    // Infinite for loop (commented for safety)
    /*
    printf("Infinite for loop (press Ctrl+C to stop):\n");
    for (;;) {
        printf("Running...\n");
        // Add break condition or it will run forever!
    }
    */
    
    return 0;
}