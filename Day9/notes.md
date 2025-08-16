# C Programming Day 9 

## Table of Contents
1. [Input Buffer Management](#input-buffer-management)
2. [Leap Year Function](#leap-year-function)
3. [Common If-Else Mistakes](#common-if-else-mistakes)
4. [Else-If Ladder vs Multiple If Statements](#else-if-ladder-vs-multiple-if-statements)
5. [Input Functions Comparison](#input-functions-comparison)
6. [Buffer Sharing Between scanf and getchar](#buffer-sharing-between-scanf-and-getchar)
7. [Character Processing and ASCII](#character-processing-and-ascii)
8. [Large Number Operations](#large-number-operations)
9. [Character Test Functions](#character-test-functions)
10. [Programming Best Practices](#programming-best-practices)
11. [Practical Examples](#practical-examples)

---

## Input Buffer Management

### The Problem
When using `scanf()` with format specifiers like `%d`, leftover characters remain in the input buffer, causing issues with subsequent input operations.

### Solution: clear_input_buffer()
```c
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != 'EOF')
        ; // Empty loop body - just consuming characters
}
```

**How it works:**
- Continuously reads characters from the input buffer
- Stops when it encounters newline (`\n`) or end-of-file (`EOF`)
- Effectively "cleans" the buffer for next input operation

**When to use:**
- After `scanf()` operations
- Before expecting new user input
- When input format is mixed (numbers and characters)

---

## Leap Year Function

### Mathematical Rules
A year is a leap year if:
1. Divisible by 4, AND
2. NOT divisible by 100, OR divisible by 400

### Implementation
```c
int isleap(int y) {
    return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
}
```

**Alternative compact version:**
```c
int isleap(int y) {
    return y % 4 && (y % 100 || y % 400);
}
```

**Test Cases:**
- 2024: Leap year (divisible by 4, not by 100)
- 1900: Not leap year (divisible by 4 and 100, but not 400)
- 2000: Leap year (divisible by 4, 100, and 400)

---

## Common If-Else Mistakes

### 1. Assignment vs Comparison
```c
// WRONG - Assignment operator
if (x = 0) {
    // This assigns 0 to x, then checks if 0 is true (always false)
}

// CORRECT - Comparison operator
if (x == 0) {
    // This compares x with 0
}
```

### 2. Yoda Conditions (Defensive Programming)
```c
// Preferred style - prevents accidental assignment
if (5 == x) {
    // If you accidentally write if(5 = x), compiler will error
}

// Traditional style - more readable but error-prone
if (x == 5) {
    // Risk of writing if(x = 5) by mistake
}
```

### 3. Logical Operator Confusion
```c
// WRONG - This is always true!
if (5 < x < 10) {
    // Evaluated as: (5 < x) < 10
    // (5 < x) returns 0 or 1, both are < 10
}

// CORRECT
if (x > 5 && x < 10) {
    // Properly checks if x is between 5 and 10
}
```

### 4. Bitwise vs Logical Operators
```c
// WRONG - Bitwise operators
if (exp1 & exp2)  // Single &
if (exp1 | exp2)  // Single |

// CORRECT - Logical operators
if (exp1 && exp2) // Double &&
if (exp1 || exp2) // Double ||
```

### 5. Dangling Else Problem
```c
// Confusing - which if does the else belong to?
if (x > 10)
    if (y > 15)
        ++m;
else            // This belongs to the inner if!
    --z;

// Clear with braces
if (x > 10) {
    if (y > 15) {
        ++m;
    } else {
        --z;
    }
}
```

### 6. Common Logic Errors
```c
// WRONG - Always true!
if (x != 10 || x != 23) {
    // x cannot be both 10 and 23 simultaneously
}

// CORRECT
if (x != 10 && x != 23) {
    // x is neither 10 nor 23
}
```

---

## Else-If Ladder vs Multiple If Statements

### Inefficient: Multiple If Statements
```c
// ALL conditions are checked, even if first one is true
if (x == 13) foo();
if (x == 15) func();
if (x == 25) func2();
if (x == 47) func3();
```

### Efficient: Else-If Ladder
```c
// Only necessary conditions are checked
if (x == 13) {
    foo();
} else if (x == 15) {
    func();
} else if (x == 25) {
    func2();
} else if (x == 47) {
    func3();
} else {
    // Default case
    func4();
}
```

### Benefits of Else-If:
1. **Performance**: Stops checking once a condition is met
2. **Readability**: Shows mutual exclusivity clearly
3. **Maintenance**: Easier to modify logic
4. **Compiler optimization**: Better optimization opportunities

---

## Input Functions Comparison

### getchar() - Standard Function
```c
int c = getchar();
```
**Characteristics:**
- Line-buffered (waits for Enter)
- Echo (shows typed characters)
- Standard C function
- Returns int (not char!) to handle EOF

### _getch() - Windows Specific
```c
int c = _getch();
```
**Characteristics:**
- NOT line-buffered (immediate response)
- NO echo (typed characters not shown)
- Non-standard function
- Useful for menu systems, games

### _getche() - Windows Specific
```c
int c = _getche();
```
**Characteristics:**
- NOT line-buffered (immediate response)
- WITH echo (shows typed characters)
- Non-standard function
- Combines benefits of both above

### Summary Table
| Function | Line-Buffered | Echo | Standard |
|----------|---------------|------|----------|
| getchar() | Yes | Yes | Yes |
| _getch() | No | No | No |
| _getche() | No | Yes | No |

---

## Buffer Sharing Between scanf and getchar

### The Problem
```c
int x, y;
printf("Enter first number: ");
scanf("%d", &x);           // User types: 123abc

printf("Enter second number: ");
scanf("%d", &y);           // Tries to read "abc", fails!
```

### The Solution
```c
int x, y;
printf("Enter first number: ");
scanf("%d", &x);
clear_input_buffer();      // Clean the buffer!

printf("Enter second number: ");
scanf("%d", &y);           // Now works correctly
```

### Why This Happens
- `scanf()` and `getchar()` share the same input buffer
- `scanf("%d", &x)` reads numbers but leaves non-numeric characters
- These leftover characters affect subsequent input operations

---

## Character Processing and ASCII

### ASCII Character Codes
- '0' = 48, '1' = 49, ..., '9' = 57
- 'A' = 65, 'B' = 66, ..., 'Z' = 90
- 'a' = 97, 'b' = 98, ..., 'z' = 122

### Character to Digit Conversion
```c
char ch = '5';
int digit = ch - '0';  // 53 - 48 = 5
```

### Random Character Generation
```c
// Random uppercase letter
putchar(rand() % 26 + 'A');

// Random digit
putchar(rand() % 10 + '0');

// Random lowercase letter
putchar(rand() % 26 + 'a');
```

---

## Large Number Operations

### Problem: Integer Overflow
When numbers are too large for `int` or `long`, we can process them as strings.

### Solution: Digit Sum for Divisibility by 3
```c
int c, sum = 0;
printf("Enter a very large number: ");

while ((c = getchar()) != '\n') {
    if (c >= '0' && c <= '9') {  // Validate digit
        sum += c - '0';          // Convert and add
    }
}

if (sum % 3 == 0) {
    printf("Number is divisible by 3\n");
} else {
    printf("Number is not divisible by 3\n");
}
```

### Mathematical Principle
A number is divisible by 3 if and only if the sum of its digits is divisible by 3.

Examples:
- 123: 1+2+3 = 6, 6%3 = 0 → divisible
- 1234: 1+2+3+4 = 10, 10%3 = 1 → not divisible

---

## Character Test Functions

### Standard Library Functions (ctype.h)
```c
#include <ctype.h>

isupper(ch)   // Uppercase letter? (A-Z)
islower(ch)   // Lowercase letter? (a-z)
isalpha(ch)   // Letter? (A-Z, a-z)
isdigit(ch)   // Digit? (0-9)
isalnum(ch)   // Alphanumeric? (letters or digits)
isxdigit(ch)  // Hex digit? (0-9, A-F, a-f)
ispunct(ch)   // Punctuation? (!, @, #, etc.)
isspace(ch)   // Whitespace? (space, tab, newline, etc.)
isblank(ch)   // Blank? (space, tab only)
isprint(ch)   // Printable? (has visual representation)
isgraph(ch)   // Graphic? (printable except space)
iscntrl(ch)   // Control character? (ASCII 0-31, 127)
```

### Return Values
- **0**: False (condition not met)
- **Non-zero**: True (condition met)

### Usage Example
```c
int ch = getchar();
if (isdigit(ch)) {
    printf("You entered a digit: %c\n", ch);
} else if (isalpha(ch)) {
    printf("You entered a letter: %c\n", ch);
} else {
    printf("You entered something else: %c\n", ch);
}
```

---

## Programming Best Practices

### 1. Redundant Else
Sometimes `else` is unnecessary when using `return`:

```c
// Style 1: With else
int getabs(int x) {
    if (x >= 0) {
        return x;
    } else {
        return -x;
    }
}

// Style 2: Without else (Redundant Else)
int getabs(int x) {
    if (x >= 0)
        return x;
    return -x;  // This line only executes if x < 0
}
```

### 2. Sequence Points
`if` statements create sequence points, guaranteeing order of operations:

```c
if (++x > 10) {
    // x is guaranteed to be incremented before comparison
    // and before entering this block
}
```

### 3. Test Functions Design
Test functions should return meaningful boolean values:

```c
int iseven(int x) {
    return x % 2 == 0;  // Returns 1 for even, 0 for odd
}

int isprime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}
```

---

## Practical Examples

### 1. Manual Integer Input
```c
int readInteger() {
    int result = 0, c;
    printf("Enter a number: ");
    
    while ((c = getchar()) != '\n') {
        if (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
        }
    }
    return result;
}
```

### 2. ASCII Table Display
```c
void printASCII() {
    printf("Printable ASCII characters:\n");
    for (int i = 33; i < 127; i++) {
        printf("%3d: %c  ", i, i);
        if ((i - 32) % 8 == 0) printf("\n");  // New line every 8 chars
    }
}
```

### 3. Character Classification
```c
void classifyCharacter(int ch) {
    printf("Character '%c' (ASCII %d) is:\n", ch, ch);
    
    if (isupper(ch)) printf("- Uppercase letter\n");
    if (islower(ch)) printf("- Lowercase letter\n");
    if (isdigit(ch)) printf("- Digit\n");
    if (ispunct(ch)) printf("- Punctuation\n");
    if (isspace(ch)) printf("- Whitespace\n");
    if (iscntrl(ch)) printf("- Control character\n");
}
```

### 4. Simple Menu System
```c
void showMenu() {
    int choice;
    
    do {
        printf("\n=== MENU ===\n");
        printf("1. Option A\n");
        printf("2. Option B\n");
        printf("3. Exit\n");
        printf("Choice: ");
        
        choice = _getch() - '0';  // Immediate response
        printf("%d\n", choice);   // Show selected number
        
        switch (choice) {
            case 1:
                printf("You selected Option A\n");
                break;
            case 2:
                printf("You selected Option B\n");
                break;
            case 3:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);
}
```

### 5. Input Validation Loop
```c
int getValidInteger(int min, int max) {
    int value, result;
    
    do {
        printf("Enter a number between %d and %d: ", min, max);
        result = scanf("%d", &value);
        
        if (result != 1) {
            printf("Invalid input! Please enter a number.\n");
            clear_input_buffer();
        } else if (value < min || value > max) {
            printf("Number out of range!\n");
        }
    } while (result != 1 || value < min || value > max);
    
    return value;
}
```