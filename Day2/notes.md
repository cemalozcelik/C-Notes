# Day 2 - Functions in C

## What is a Function?
A function is a reusable block of code that performs a specific task. It takes inputs (parameters), processes them, and optionally returns a result.

## Function Anatomy
```c
return_type function_name(parameter_list) {
    // function body
    return value; // optional for void functions
}
```

**Example:**
```c
int sum(int a, int b) {
    return a + b;
}
```

## Function Declaration vs Definition

### Declaration (Prototype)
Tells the compiler "this function exists" - usually placed before main()
```c
int sum(int a, int b);  // Declaration only
```

### Definition
Contains the actual implementation of the function
```c
int sum(int a, int b) {  // Definition
    return a + b;
}
```

**Why do we need prototypes?**
C compiler reads code from top to bottom. If you call a function before defining it, the compiler doesn't know what it is.

## Return Types

### Functions that return a value
```c
int getValue() {
    return 42;
}

double calculate() {
    return 3.14;
}
```

### Functions that don't return a value (void)
```c
void print_hello() {
    printf("Hello World!\n");
    // no return statement needed
}
```

## Parameters vs Arguments

### Parameters
Variables in the function definition (formal parameters)
```c
int multiply(int x, int y) {  // x and y are parameters
    return x * y;
}
```

### Arguments
Actual values passed when calling the function (actual parameters)
```c
int result = multiply(5, 3);  // 5 and 3 are arguments
```

## Pass by Value
C uses "pass by value" - the function receives a copy of the argument, not the original variable.

```c
void modify(int x) {
    x = 100;  // Only changes the local copy
}

int main() {
    int a = 5;
    modify(a);
    printf("%d\n", a);  // Still prints 5!
}
```

**Key Point:** The original variable remains unchanged because the function works with a copy.

## Scope and Lifetime

### Global Variables
- Declared outside all functions
- Accessible from anywhere in the program
- Exist for the entire program duration

### Local Variables
- Declared inside functions or blocks
- Only accessible within that function/block
- Destroyed when function/block ends

```c
int global_var = 10;  // Global scope

void test() {
    int local_var = 20;  // Local scope
    global_var++;        // Can access global variable
}

int main() {
    printf("%d\n", global_var);  // OK - can access global
    // printf("%d\n", local_var);  // ERROR - cannot access local
}
```

### Variable Shadowing
When a local variable has the same name as a global variable, the local one "shadows" (hides) the global one.

```c
int x = 5;  // Global

void func() {
    int x = 10;  // Local - shadows global x
    printf("%d\n", x);  // Prints 10, not 5
}
```

## Recursive Functions
A function that calls itself. Must have:
1. Base case (stopping condition)
2. Recursive case (function calls itself)

```c
int factorial(int n) {
    if (n <= 1) {
        return 1;        // Base case
    }
    return n * factorial(n - 1);  // Recursive case
}
```

## Control Flow in Functions

### Switch Statement
Alternative to multiple if-else statements
```c
void demonstrate_switch(int value) {
    switch (value) {
        case 1:
            printf("One\n");
            break;  // Important: prevents fall-through
        case 2:
            printf("Two\n");
            break;
        default:
            printf("Other\n");
    }
}
```

### Conditional (Ternary) Operator
Shorthand for simple if-else statements
```c
int max(int a, int b) {
    return (a > b) ? a : b;  // If a > b, return a, else return b
}
```

## Function Examples from Code

### Basic Mathematical Functions
```c
int sum(int a, int b) {
    return a + b;  // Addition
}

int abs_value(int x) {
    return (x < 0) ? -x : x;  // Absolute value using ternary
}
```

### Utility Functions
```c
int ndigit(int n) {
    n = abs_value(n);  // Handle negative numbers
    int count = 0;
    if (n == 0) return 1;  // Special case for zero
    
    while (n != 0) {
        n /= 10;  // Remove last digit
        count++;
    }
    return count;
}
```

### Boolean Functions
Functions that return 1 (true) or 0 (false)
```c
int is_even(int n) {
    return (n % 2 == 0) ? 1 : 0;
}

int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}
```

## Key Concepts

1. **Function prototypes** are necessary when calling functions before defining them
2. **Pass by value** means functions work with copies, not original variables
3. **Global variables** can be accessed and modified from any function
4. **Local variables** are only accessible within their scope
5. **Recursive functions** must have a base case to avoid infinite recursion
6. **void functions** don't return values, other functions must return appropriate types
7. **Parameters** are in function definition, **arguments** are in function calls
