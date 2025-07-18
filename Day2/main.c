#include <stdio.h>

// Function Declarations 
int sum(int a, int b);
int max(int a, int b);
int abs_value(int x);
int ndigit(int n);
void print_hello();
void print_banner();  // Added missing declaration
void demonstrate_pass_by_value(int x);
void demonstrate_switch(int value);
int is_prime(int n);
int is_even(int n);
int factorial(int n);

int global_var = 10; // Global variable

int main() {
    // Print banner
    print_banner();
    
    // Basic function calls
    int a = 5, b = 10;
    printf("Sum of %d and %d is %d\n", a, b, sum(a, b));
    printf("Max of %d and %d is %d\n", a, b, max(a, b));
    printf("Absolute value of -%d is %d\n", a, abs_value(-a));
    
    // Digit counting
    int number = -12345;
    printf("Number of digits in %d is %d\n", number, ndigit(number));
    
    // Even/odd check
    printf("%d is %s\n", a, is_even(a) ? "even" : "odd");
    printf("%d is %s\n", b, is_even(b) ? "even" : "odd");
    
    // Pass by value demonstration
    printf("\nPass by Value Demo:\n");
    printf("Before function call: a = %d\n", a);
    demonstrate_pass_by_value(a);
    printf("After function call: a = %d\n", a);
    
    // Recursive function
    printf("\nFactorial of 5 is %d\n", factorial(5));
    
    // Global variable access
    printf("Global variable: %d\n", global_var);
    {
        global_var += 5; // Modify global variable on scope entry 
        printf("Modified global variable: %d\n", global_var);   
    }
    global_var -= 5; // Reset global variable after scope exit
    printf("Global variable after scope exit: %d\n", global_var); // Should be back to original value

    // Switch-case demonstration
    printf("\nSwitch-case demonstration:\n");
    demonstrate_switch(1);
    demonstrate_switch(2);
    demonstrate_switch(3);
    demonstrate_switch(4); // Default case

    // Prime number check
    int prime_check = 29;
    printf("\nIs %d a prime number? %s\n", prime_check, is_prime(prime_check) ? "Yes" : "No");
    prime_check = 30;
    printf("Is %d a prime number? %s\n", prime_check, is_prime(prime_check) ? "Yes" : "No");
    
    // Print "Hello, World!"
    printf("\n");
    print_hello();

    // Control statements
    int x = 10;
    if (x > 5) {
        printf("x is greater than 5\n");
    } else {
        printf("x is 5 or less\n");
    }
    return 0;
}

// Function Definitions

// Function to print banner
void print_banner() {
    printf("================================\n");
    printf("          DAY 2                 \n");
    printf("================================\n");
}

// Function to calculate the sum of two integers
int sum(int a, int b) {
    return a + b;
}

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b; // Returns the larger of the two integers using the ternary operator
}

// Function to return the absolute value of an integer
int abs_value(int x) {
    return (x < 0) ? -x : x; // Returns the absolute value using the ternary operator
}

// Function to count the number of digits in an integer
int ndigit(int n) {
    n = abs_value(n);  // Handle negative numbers
    int count = 0;
    if (n == 0) return 1; // Special case for 0
    while (n != 0) {
        n /= 10; // Remove the last digit
        count++; // Increment the count
    }
    return count; // Returns the count of digits
}

// Function to print "Hello, World!"
void print_hello() {
    printf("Hello, World!\n");
}

// Function to demonstrate pass by value
void demonstrate_pass_by_value(int x) {
    x += 5; // Modifies the local copy of x
    printf("Inside function, x = %d\n", x);
}

// Function to demonstrate switch-case statement
void demonstrate_switch(int value) {    
    switch (value) {
        case 1:
            printf("Value is 1\n");
            break;
        case 2:
            printf("Value is 2\n");
            break;
        case 3:
            printf("Value is 3\n");
            break;
        default:
            printf("Value is something else\n");
    }
}

// Function to check if a number is prime
int is_prime(int n) {   
    if (n <= 1) return 0; // 0 and 1 are not prime numbers
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0; // Not a prime number
    }
    return 1; // Is a prime number
}

// Function to check if a number is even
int is_even(int n) {    
    return (n % 2 == 0) ? 1 : 0; // Returns 1 if even, 0 if odd
}

// Function to calculate the factorial of a number
int factorial(int n) {  
    if (n <= 1) return 1; // Base case for factorial
    return n * factorial(n - 1); // Recursive case
}

/*
================================
          DAY 2
================================
Sum of 5 and 10 is 15
Max of 5 and 10 is 10
Absolute value of -5 is 5
Number of digits in -12345 is 5
5 is odd
10 is even

Pass by Value Demo:
Before function call: a = 5
Inside function, x = 10
After function call: a = 5

Factorial of 5 is 120
Global variable: 10
Modified global variable: 15
Global variable after scope exit: 10

Switch-case demonstration:
Value is 1
Value is 2
Value is 3
Value is something else

Is 29 a prime number? Yes
Is 30 a prime number? No

Hello, World!
x is greater than 5
*/