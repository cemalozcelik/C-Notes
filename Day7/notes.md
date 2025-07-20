# C Programming Day 7 Notes
## Logical and Comparison Operators

## Table of Contents
1. [Logical Operators](#logical-operators)
2. [Short-Circuit Evaluation](#short-circuit-evaluation)
3. [De Morgan's Laws](#de-morgans-laws)
4. [Comparison Operators](#comparison-operators)
5. [Assignment Operators](#assignment-operators)
6. [Practical Examples](#practical-examples)

## Logical Operators

### NOT Operator (!)
```c
!1    // Result: 0 (false)
!0    // Result: 1 (true)
!(-1) // Result: 0 (false) - Any non-zero value is true
!50   // Result: 0 (false)
```

**Important:** In C, any non-zero value is considered `true`.

### Double NOT Operator (!!)
Used to convert a value to boolean:
```c
!!5   // Result: 1 (true)
!!0   // Result: 0 (false)
!!(-10) // Result: 1 (true)
```

### AND Operator (&&)
Returns `true` when both operands are `true`:
```c
int a = 5, b = 10, c = 15;
a && b    // Result: 1 (true)
a && c    // Result: 1 (true)
0 && b    // Result: 0 (false)
```

### OR Operator (||)
Returns `true` when at least one operand is `true`:
```c
a || b    // Result: 1 (true)
0 || b    // Result: 1 (true)
0 || 0    // Result: 0 (false)
```

### Operator Precedence
```c
a && b || c     // Evaluated as (a && b) || c
a || b && c     // Evaluated as a || (b && c)
```

## Short-Circuit Evaluation

C logical operators use "short-circuit" logic:

### Short-Circuit with AND Operator (&&)
```c
int x = 0, y = 10;
int result = x && ++y;  // ++y is not executed because x is false
// Result: result = 0, y = 10 (unchanged)
```

### Short-Circuit with OR Operator (||)
```c
int x = 0, y = 10;
int result = x || ++y;  // ++y is executed because x is false
// Result: result = 1, y = 11 (incremented)
```

### Practical Use - Null Pointer Check
```c
int *ptr = NULL;
int value = 42;

// Wrong usage (Segmentation Fault risk):
// if (*ptr > 0 && ptr != NULL)  // *ptr is checked first!

// Correct usage:
if (ptr != NULL && *ptr > 0) {  // NULL check first
    *ptr = value;  // Safe
} else {
    printf("Pointer is NULL, skipping assignment.\n");
}
```

## De Morgan's Laws

### First Law: !(A && B) == !A || !B
```c
int p = 1, q = 0;
!(p && q) == (!p || !q)  // Both sides yield the same result
```

### Second Law: !(A || B) == !A && !B
```c
int p = 1, q = 0;
!(p || q) == (!p && !q)  // Both sides yield the same result
```

### Practical Example
```c
int age = 20, salary = 5000;

// Normal check:
if (age < 18 || salary < 3000) {
    printf("You are not eligible for the loan.\n");
} else {
    printf("You are eligible for the loan.\n");
}

// Using De Morgan's law:
if (!(age >= 18 && salary >= 3000)) {
    printf("You are not eligible for the loan (using De Morgan's law).\n");
} else {
    printf("You are eligible for the loan (using De Morgan's law).\n");
}
```

## Comparison Operators

### Basic Comparison Operators
```c
int a = 10, b = -20;

a == b   // Equal? (0 - false)
a != b   // Not equal? (1 - true)
a < b    // Less than? (0 - false)
a > b    // Greater than? (1 - true)
a <= b   // Less than or equal? (0 - false)
a >= b   // Greater than or equal? (1 - true)
```

### Other Operations Using Only < Operator
```c
// Equality check: a == b
!(a < b) && !(b < a)  // If a is neither less nor greater than b, they're equal

// Inequality check: a != b
(a < b) || (b < a)    // a is either less than or greater than b
```

### Finding Maximum (Using Only < Operator)
```c
int x = 5, y = 10, z = 7;

int max_xy = !(x < y) ? x : y;      // If x >= y then x, else y
int max_xyz = !(max_xy < z) ? max_xy : z;
// Result: 10
```

## Assignment Operators

### Simple Assignment
```c
int x = 10;
printf("(x = 5) returns: %d\n", x = 5);  // Assignment operation returns the value
// Output: 5
```

### Multiple Assignment
```c
int a, b, c, d, e;
a = b = c = d = e = 42;  // Right-to-left evaluation
// All variables become 42
```

### Multiple Assignment with Expressions
```c
int f, g, h;
f = (g = 5) + (h = 10);  // g = 5, h = 10, f = 15
```

### Arithmetic Assignment Operators
```c
int i = 10;
i += 5;  // i = i + 5  → i = 15
i -= 3;  // i = i - 3  → i = 12
i *= 2;  // i = i * 2  → i = 24
i /= 4;  // i = i / 4  → i = 6
```

### Type Conversion with Assignment
```c
double j = 3.14;
int z = j;  // Implicit type conversion: double → int
// z = 3 (decimal part is lost)
```


### Finding Middle Value (Using Reverse Logic)
```c
int get_mid(int x, int y, int z) {
    // If x is neither the largest nor the smallest
    if (!(x > y && x > z || x < y && x < z))
        return x;
    // If y is neither the largest nor the smallest
    else if (!(y > x && y > z || y < x && y < z))
        return y;
    // z is the only remaining option
    else
        return z;
}
```

### Safe Pointer Usage
```c
if (ptr != NULL && *ptr > threshold) {
    // NULL check first, then value check
    process_value(*ptr);
}
```

### Loan Eligibility Check
```c
int age = 25, salary = 4000;
if (age >= 18 && salary >= 3000) {
    printf("Loan approved.\n");
} else {
    printf("Loan rejected.\n");
}
```

### Bitwise vs Logical Operations
```c
int x1 = 10, x2 = 20;

// Logical AND
if (x1 && x2) {  // Both non-zero, so true
    printf("Logical AND: true\n");
}

// Bitwise AND
if (x1 & x2) {   // 10 & 20 in binary
    printf("Bitwise AND: true\n");
} else {
    printf("Bitwise AND: false\n");
}

/*
10 = 0000 1010
20 = 0001 0100
--------------
     0000 0000  = 0 (false)
*/

int x1 = 12, x2 = 5;

/*
12 = 0000 1100
 5 = 0000 0101
--------------
     0000 0100 = 4 (true)
*/
```

### XOR Implementation Without XOR Operator
```c
// Exclusive OR using logical operators
int x1 = 5, x2 = 0;
printf("XOR of %d and %d = %d\n", x1, x2, !!x1 != !!x2);
// One must be 0, the other must be 1 for XOR to be true
```

### Common Logic Mistakes
```c
int x = 10;

// WRONG: This is ALWAYS true!
if (x != 5 || x != 13) {
    // This will always execute because x cannot be both 5 AND 13 simultaneously
}

// CORRECT: 
if (x != 5 && x != 13) {
    // This executes only when x is neither 5 nor 13
}
```

### Assignment as Expression Value
```c
int x = 10;
printf("x = %d\n", x);
printf("Value of assignment (x = 3): %d\n", x = 3);
printf("x after assignment: %d\n", x);

// While loop with assignment in condition
int ch;
printf("Enter text: ");
while ((ch = getchar()) != '\n') {
    printf("Character: %c, ASCII: %d\n", ch, ch);
}
```

### Time Calculation Example
```c
void normalize_time() {
    int day, hour, min, sec;
    
    printf("Enter time (days hours minutes seconds): ");
    scanf("%d%d%d%d", &day, &hour, &min, &sec);
    
    // Normalize seconds to minutes
    min += sec / 60;
    sec %= 60;
    
    // Normalize minutes to hours  
    hour += min / 60;
    min %= 60;
    
    // Normalize hours to days
    day += hour / 24;
    hour %= 24;
    
    printf("Normalized time: %d days %d hours %d minutes %d seconds\n", 
           day, hour, min, sec);
}
```

### Assignment Operator Precedence and Associativity
```c
int a, b, c, d, e;
a = b = c = d = e = 1;  
// Equivalent to: a = (b = (c = (d = (e = 1))));
// Right-to-left associativity (precedence level 14)
```

### L-Value and R-Value Concepts
```c
int x = 10;

x = 5;      // Valid: x is an L-value
// 5 = x;   // INVALID: 5 is not an L-value
// +x = 45; // INVALID: +x is not an L-value  
// x+3 = 10;// INVALID: x+3 is not an L-value
```

### Safe Equality Comparison Technique
```c
int x = 5;

// Recommended style to avoid assignment mistakes:
if (5 == x) {  // If you accidentally write 5 = x, compiler error
    printf("x equals 5\n");
}

// Instead of:
if (x == 5) {  // If you accidentally write x = 5, no compiler error
    printf("x equals 5\n");
}
```

## Notes

1. **Short-Circuit Evaluation**: Used in logical operators to prevent unnecessary computations.

2. **Bitwise vs Logical**: Don't confuse `&` (bitwise) with `&&` (logical), or `|` (bitwise) with `||` (logical).

3. **De Morgan's Laws**: Used to simplify complex logical expressions and avoid common logic mistakes.

4. **Assignment Returns Value**: Assignment operations return the assigned value, enabling chained assignments and while-loop patterns.

5. **L-Value Requirement**: Left side of assignment must be a modifiable L-value expression.

6. **Optimization Warning**: Don't try to optimize code manually - "early optimization is evil". Let the compiler handle optimizations.

7. **Boolean Context**: In C, any non-zero value is considered true, and zero is considered false.

8. **Defensive Programming**: Use techniques like `5 == x` instead of `x == 5` to prevent accidental assignments.

## Truth Tables

### Logical AND (&&)
| A | B | A && B |
|---|---|--------|
| 0 | 0 |   0    |
| 0 | 1 |   0    |
| 1 | 0 |   0    |
| 1 | 1 |   1    |

### Logical OR (||)
| A | B | A \|\| B |
|---|---|----------|
| 0 | 0 |    0     |
| 0 | 1 |    1     |
| 1 | 0 |    1     |
| 1 | 1 |    1     |

### Logical NOT (!)
| A | !A |
|---|----|
| 0 | 1  |
| 1 | 0  |